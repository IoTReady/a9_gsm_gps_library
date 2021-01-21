#ifndef __MQTT_LIB_H_
#define __MQTT_LIB_H_

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

#include "mqtt_config.h"


typedef enum{
    MQTT_EVENT_CONNECTED = 0,
    MQTT_EVENT_DISCONNECTED ,
    MQTT_EVENT_MAX
}MQTT_Event_ID_t;

typedef struct {
    MQTT_Event_ID_t id;
    MQTT_Client_t* client;
}MQTT_Event_t;

typedef enum{
    MQTT_STATUS_DISCONNECTED = 0,
    MQTT_STATUS_CONNECTED       ,
    MQTT_STATUS_MAX
}MQTT_Status_t;

static HANDLE semMqttStart = NULL;

static MQTT_Status_t mqttStatus;

void wait_for_network_activation();


/**
 * @brief  Initialize MQTT with SSL verification
 * 
 *
 * @param client_id             Client ID of the thing
 * @param keep_alive            Keep-alive interval in seconds
 * @param clean_session         Boolean - true or false
 * @param mqtt_ca_crt           CA root certificate 
 * @param mqtt_client_crt       Client certificate
 * @param mqtt_client_key       Private Key
 * @param broker_hostname       Complete broker hostname/IP
 * @param broker_port           Broker port
 * @param callback              Callback function
 * 
 */
MQTT_Client_t* mqtt_ssl_initialize(const char* client_id, uint16_t keep_alive, bool clean_session, const char* mqtt_ca_crt, const char* mqtt_client_crt, const char* mqtt_client_key, const char* broker_hostname, uint16_t broker_port, MQTT_Connection_Callback_t callback);

/**
 * @brief  Initialize MQTT without SSL verification
 * 
 *
 * @param client_id             Client ID of the thing
 * @param keep_alive            Keep-alive interval in seconds
 * @param clean_session         Boolean - true or false
 * @param broker_hostname       Complete broker hostname/IP
 * @param broker_port           Broker port
 * @param callback              Callback function
 * 
 */
MQTT_Client_t* mqtt_initialize(const char* client_id, uint16_t keep_alive, bool clean_session, const char* broker_hostname, uint16_t broker_port, MQTT_Connection_Callback_t callback);

/**
 * @brief  Publish to an MQTT topic
 * 
 *
 * @param client            MQTT client object
 * @param topic             MQTT topic to publish to
 * @param payload           Message payload
 * @param dup               Indicating the number of sending repeats 
 * @param qos               Quality of Service: 0,1,2
 * @param retain            Retain message
 * @param callback          Callback function
 * @param arg               Callback function
 * 
 */
MQTT_Error_t publish_mqtt(MQTT_Client_t* client, const char* topic, const void* payload, uint8_t dup, uint8_t qos, uint8_t retain, MQTT_Request_Callback_t callback, void* arg);

/**
 * @brief  Subscribe to an MQTT topic
 * 
 *
 * @param client            MQTT client object
 * @param topic             MQTT topic to publish to
 * @param qos               Quality of Service: 0, 1, 2
 * @param callback          Callback function
 * @param arg               Callback function
 * 
 */
MQTT_Error_t subscribe_mqtt(MQTT_Client_t* client, const char* topic, uint8_t qos, MQTT_Request_Callback_t callback, void* arg);

#endif

