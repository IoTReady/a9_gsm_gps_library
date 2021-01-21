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


static MQTT_Status_t mqttStatus = MQTT_STATUS_DISCONNECTED;

void StartTimerPublish(uint32_t interval,MQTT_Client_t* client);


// Use OS_ReleaseSemaphore(semMqttStart) on the right callback to release this blocking function
void wait_for_network_activation()
{
    Trace(1,"Waiting for network activation");
    semMqttStart = OS_CreateSemaphore(0);
    OS_WaitForSemaphore(semMqttStart, OS_WAIT_FOREVER);
    OS_DeleteSemaphore(semMqttStart);
    Trace(1,"Unblocking since network activated");
}

MQTT_Client_t* mqtt_ssl_initialize(const char* client_id, uint16_t keep_alive, bool clean_session, const char* mqtt_ca_crt, const char* mqtt_client_crt, const char* mqtt_client_key, const char* broker_hostname, uint16_t broker_port, MQTT_Connection_Callback_t callback)
{

    Trace(1, "Initializing MQTT");
    MQTT_Client_t* client = MQTT_ClientNew();
    MQTT_Connect_Info_t ci;
    MQTT_Error_t err;
    memset(&ci, 0, sizeof(MQTT_Connect_Info_t));
    ci.client_id = client_id;
    ci.client_user = CLIENT_USER;
    ci.client_pass = CLIENT_PASS;
    ci.keep_alive = keep_alive;
    ci.clean_session = clean_session;
    ci.use_ssl = true;
    ci.ssl_verify_mode = MQTT_SSL_VERIFY_MODE_REQUIRED;
    ci.ca_cert = mqtt_ca_crt;
    ci.ca_crl = NULL;
    ci.client_cert = mqtt_client_crt;
    ci.client_key  = mqtt_client_key;
    ci.client_key_passwd = NULL;
    ci.broker_hostname = broker_hostname;
    ci.ssl_min_version   = MQTT_SSL_VERSION_SSLv3;
    ci.ssl_max_version   = MQTT_SSL_VERSION_TLSv1_2;
    ci.entropy_custom    = "GPRS_A9";

    err = MQTT_Connect(client, broker_hostname, broker_port, callback, NULL, &ci);
    if(err != MQTT_ERROR_NONE)
        Trace(1, "MQTT connect fail,error code:%d", err);

    return client;
    
}

MQTT_Client_t* mqtt_initialize(const char* client_id, uint16_t keep_alive, bool clean_session, const char* broker_hostname, uint16_t broker_port, MQTT_Connection_Callback_t callback)
{

    Trace(1,"start mqtt test");
    MQTT_Client_t* client = MQTT_ClientNew();
    MQTT_Connect_Info_t ci;
    MQTT_Error_t err;
    memset(&ci, 0, sizeof(MQTT_Connect_Info_t));
    ci.client_id = client_id;
    ci.client_user = CLIENT_USER;
    ci.client_pass = CLIENT_PASS;
    ci.keep_alive = keep_alive;
    ci.clean_session = clean_session;
    ci.use_ssl = false;

    err = MQTT_Connect(client, broker_hostname, broker_port, callback, NULL, &ci);
    if(err != MQTT_ERROR_NONE)
        Trace(1, "MQTT connect fail,error code:%d", err);

    return client;
    
}

MQTT_Error_t publish_mqtt(MQTT_Client_t* client, const char* topic, const void* payload, uint8_t dup, uint8_t qos, uint8_t retain, MQTT_Request_Callback_t callback, void* arg)
{
    MQTT_Error_t err;
    Trace(1,"In publish_mqtt!");
    err = MQTT_Publish(client, topic, payload, strlen(payload), dup, qos, retain, callback, arg);
    if(err != MQTT_ERROR_NONE)
        Trace(1, "MQTT publish error, error code:%d", err);
    
    return err;
}

MQTT_Error_t subscribe_mqtt(MQTT_Client_t* client, const char* topic, uint8_t qos, MQTT_Request_Callback_t callback, void* arg)
{
    MQTT_Error_t err;
    Trace(1,"In subscribe_mqtt!");
    err = MQTT_Subscribe(client, topic, qos, callback, arg);
    if(err != MQTT_ERROR_NONE)
        Trace(1,"MQTT subscribe error, error code:%d",err);

    return err;
}