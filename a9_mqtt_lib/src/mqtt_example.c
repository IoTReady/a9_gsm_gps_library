#include "stdbool.h"
#include "stdint.h"
#include "stdio.h"
#include "string.h"

#include "api_os.h"
#include "api_debug.h"
#include "api_event.h"
#include "api_mqtt.h"
#include "api_network.h"
#include "api_socket.h"

#include "mqtt_lib.h"
#include "certs.h"

#define PDP_CONTEXT_APN       "airtelgprs.com"
#define PDP_CONTEXT_USERNAME  ""
#define PDP_CONTEXT_PASSWD    ""

#define MAIN_TASK_STACK_SIZE    (2048 * 2)
#define MAIN_TASK_PRIORITY      0
#define MAIN_TASK_NAME          "Main Test Task"

#define SECOND_TASK_STACK_SIZE    (2048 * 2)
#define SECOND_TASK_PRIORITY      1
#define SECOND_TASK_NAME          "MQTT Test Task"

static HANDLE mainTaskHandle = NULL;
static HANDLE secondTaskHandle = NULL;
// static HANDLE thirdTaskHandle = NULL;

Network_PDP_Context_t context = {
    .apn        = PDP_CONTEXT_APN,
    .userName   = PDP_CONTEXT_USERNAME,
    .userPasswd = PDP_CONTEXT_PASSWD
};

void StartTimerPublish(uint32_t interval,MQTT_Client_t* client);

bool AttachActivate()
{
    uint8_t temp[70];
    uint8_t status;
    bool ret = Network_GetAttachStatus(&status);
    if(!ret)
    {
        Trace(2,"get attach status fail");
        return false;
    }
    Trace(2,"attach status:%d",status);
    if(!status)
    {
        ret = Network_StartAttach();
        if(!ret)
        {
            Trace(2,"network attach fail");
            return false;
        }
    }
    else
    {
        ret = Network_GetActiveStatus(&status);
        if(!ret)
        {
            Trace(2,"get activate status fail");
            return false;
        }
        Trace(2,"activate status:%d",status);
        if(!status)
        {
            Network_StartActive(context);
        }
    }
    return true;
}

static void EventDispatch(API_Event_t* pEvent)
{
    switch(pEvent->id)
    {
        case API_EVENT_ID_NO_SIMCARD:
            Trace(1, "!!NO SIM CARD%d!!!!", pEvent->param1);
            break;

        case API_EVENT_ID_SYSTEM_READY:
            Trace(1, "system initialize complete");
            break;

        case API_EVENT_ID_NETWORK_REGISTER_DENIED:
            Trace(1,"network register denied");
            AttachActivate();
            break;  

        case API_EVENT_ID_NETWORK_REGISTERED_HOME:
        case API_EVENT_ID_NETWORK_REGISTERED_ROAMING:
            Trace(1, "network register success");
            AttachActivate();
            break;

        case API_EVENT_ID_NETWORK_ATTACHED:
            Trace(1, "network attach success");
            AttachActivate();
            break;

        case API_EVENT_ID_NETWORK_ACTIVATED:
            Trace(1, "network activate success..");
            OS_ReleaseSemaphore(semMqttStart);
            break;
        
        case API_EVENT_ID_NETWORK_DETACHED:
            Trace(1,"network detached");
            Network_StartDetach();
            AttachActivate();
            break;

        case API_EVENT_ID_NETWORK_ATTACH_FAILED:
            Trace(1,"network attach failed");
            Network_StartDetach();
            AttachActivate();
            break;

        case API_EVENT_ID_NETWORK_DEACTIVED:
            Trace(1,"network deactived");
            Network_StartDetach();
            AttachActivate();
            break;

        case API_EVENT_ID_NETWORK_ACTIVATE_FAILED:
            Trace(1,"network activate failed");
            Network_StartDetach();
            AttachActivate();
            break;
        
        case API_EVENT_ID_SOCKET_CONNECTED:
            Trace(1, "socket connected");
            break;
        
        case API_EVENT_ID_SOCKET_CLOSED:
            Trace(1, "socket closed");
                      
            break;

        case API_EVENT_ID_SIGNAL_QUALITY:
            Trace(1, "CSQ:%d",pEvent->param1);
            break;

        default:
            break;
    }
}

void OnMqttReceived(void* arg, const char* topic, uint32_t payloadLen)
{
    Trace(1, "MQTT received publish data request, topic:%s, payload length:%d", topic, payloadLen);
}

void OnMqttReceivedData(void* arg, const uint8_t* data, uint16_t len, MQTT_Flags_t flags)
{
    Trace(1, "MQTT recieved publish data, length:%d, data:%s", len, data);
    if(flags == MQTT_FLAG_DATA_LAST)
        Trace(1, "MQTT data is last frame");
}

void OnMqttSubscribed(void* arg, MQTT_Error_t err)
{
    if(err != MQTT_ERROR_NONE)
        Trace(1, "MQTT subscribe fail, error code:%d",err);
    else
        Trace(1, "MQTT subscribe success, topic:%s", (const char*)arg);
}

void OnMqttConnection(MQTT_Client_t *client, void *arg, MQTT_Connection_Status_t status)
{
    Trace(1,"MQTT connection status:%d",status);
    MQTT_Event_t* event = (MQTT_Event_t*)OS_Malloc(sizeof(MQTT_Event_t));
    if(!event)
    {
        Trace(1,"MQTT no memory");
        return ;
    }
    if(status == MQTT_CONNECTION_ACCEPTED)
    {
        Trace(1,"MQTT succeed connect to broker");
        //!!! DO NOT suscribe here(interrupt function), do MQTT suscribe in task, or it will not execute
        event->id = MQTT_EVENT_CONNECTED;
        event->client = client;
        OS_SendEvent(secondTaskHandle,event, OS_TIME_OUT_WAIT_FOREVER, OS_EVENT_PRI_NORMAL);
    }
    else
    {
        event->id = MQTT_EVENT_DISCONNECTED;
        event->client = client;
        OS_SendEvent(secondTaskHandle,event, OS_TIME_OUT_WAIT_FOREVER, OS_EVENT_PRI_NORMAL);
        Trace(1,"MQTT connect to broker fail,error code:%d",status);
    }
    Trace(1,"MQTT OnMqttConnection() end");
}

void OnMqttDisconnection()
{
    mqtt_ssl_initialize( CLIENT_ID, KEEP_ALIVE, CLEAN_SESSION, ca_crt, client_crt, client_key, BROKER_HOSTNAME, BROKER_PORT, OnMqttConnection);
}

void OnPublish(void* arg, MQTT_Error_t err)
{
    if(err == MQTT_ERROR_NONE)
        Trace(1,"MQTT publish success");
    else
        Trace(1,"MQTT publish error, error code:%d",err);
}

MQTT_Error_t OnTimerPublish(void* param)
{
    MQTT_Error_t err;
    MQTT_Client_t* client = (MQTT_Client_t*)param;
    if(mqttStatus != MQTT_STATUS_CONNECTED)
    {
        Trace(1,"MQTT not connected to broker! Can not publish");
        return;
    }

    Trace(1, "MQTT OnTimerPublish");

    err = publish_mqtt(client, PUBLISH_TOPIC, PUBLISH_PAYLOAD, 1, 0, 0, OnPublish, NULL);
    if(err != MQTT_ERROR_NONE)
    {
        Trace(1, "MQTT publish error, error code:%d", err);
        return err;
    }
    
    StartTimerPublish(PUBLISH_INTERVAL, client);

    return err;
}

void StartTimerPublish(uint32_t interval,MQTT_Client_t* client)
{
    OS_StartCallbackTimer(mainTaskHandle, interval, OnTimerPublish, client);
}

void SecondTaskEventDispatch(MQTT_Event_t* pEvent)
{
    switch(pEvent->id)
    {
        case MQTT_EVENT_CONNECTED:
            mqttStatus = MQTT_STATUS_CONNECTED;
            Trace(1,"MQTT connected, now subscribe topic:%s",SUBSCRIBE_TOPIC);
            MQTT_Error_t err;
            MQTT_SetInPubCallback(pEvent->client, OnMqttReceived, OnMqttReceivedData, NULL);
            err = subscribe_mqtt(pEvent->client, SUBSCRIBE_TOPIC, 0, OnMqttSubscribed, (void*)SUBSCRIBE_TOPIC);
            StartTimerPublish(PUBLISH_INTERVAL, pEvent->client);
            break;
        case MQTT_EVENT_DISCONNECTED:
            mqttStatus = MQTT_STATUS_DISCONNECTED;
            OnMqttDisconnection();
            break;
        default:
            break;
    }
}

// void ThirdTask(void *pData)
// {
//     Trace(1, "In Third Task");
//     // wait_for_network_activation();
//     OS_Sleep(20000);


//     MQTT_Client_t* client = (MQTT_Client_t*)pData;

//     while(1)
//     {
//     Trace(1, "In Third Task: WHILE");

//         MQTT_Error_t err = publish_mqtt(client, PUBLISH_TOPIC, PUBLISH_PAYLOAD, 1, 0, 0, OnPublish, NULL);
//         if(err != MQTT_ERROR_NONE)
//             Trace(1, "THIRD TASK: MQTT publish error, error code:%d", err);
//         else
//             Trace(1, "THIRD TASK: MQTT publish successful");
//         OS_Sleep(7000);
//     }
        
// }

// Task to test MQTT functions
void SecondTask(void *pData)
{
    Trace(1, "In Second Task");
    
    MQTT_Event_t* event=NULL;

    // Wait for Semaphore to indicate successful network activation
    // wait_for_network_activation();
    Trace(1, "Waiting for network activation");
    semMqttStart = OS_CreateSemaphore(0);
    OS_WaitForSemaphore(semMqttStart, OS_WAIT_FOREVER);
    OS_DeleteSemaphore(semMqttStart);

    Trace(1, "NETWORK ACTIVATED!!");

    MQTT_Client_t* client = mqtt_ssl_initialize( CLIENT_ID, KEEP_ALIVE, CLEAN_SESSION, ca_crt, client_crt, client_key, BROKER_HOSTNAME, BROKER_PORT, OnMqttConnection);

    // thirdTaskHandle = OS_CreateTask(ThirdTask,
    // client, NULL, SECOND_TASK_STACK_SIZE, SECOND_TASK_PRIORITY, 0, 0, "Publish Task");
    
    while(1)
    {
    Trace(1, "In Second Task");

        if(OS_WaitEvent(secondTaskHandle, (void**)&event, OS_TIME_OUT_WAIT_FOREVER))
        {
            SecondTaskEventDispatch(event);
            OS_Free(event);
        }
    }
}

void MainTask(void *pData)
{
    API_Event_t* event = NULL;

    secondTaskHandle = OS_CreateTask(SecondTask,
        NULL, NULL, SECOND_TASK_STACK_SIZE, SECOND_TASK_PRIORITY, 0, 0, SECOND_TASK_NAME);
    
    while(1)
    {
        Trace(1, "In MAIN Task");
        if(OS_WaitEvent(mainTaskHandle, (void**)&event, OS_TIME_OUT_WAIT_FOREVER))
        {
            EventDispatch(event);
            OS_Free(event->pParam1);
            OS_Free(event->pParam2);
            OS_Free(event);
        }
    }
}

void a9_mqtt_lib_Main(void)
{
    mainTaskHandle = OS_CreateTask(MainTask,
        NULL, NULL, MAIN_TASK_STACK_SIZE, MAIN_TASK_PRIORITY, 0, 0, MAIN_TASK_NAME);
    OS_SetUserMainHandle(&mainTaskHandle);

    OS_Sleep(5000);
    Trace(1, "mqtt_example_Main Task DONE");
}
