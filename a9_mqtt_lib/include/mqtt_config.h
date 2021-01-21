#ifndef __MQTT_CONFIG_H_
#define __MQTT_CONFIG_H_


#define BROKER_HOSTNAME     "xxxxxxxxxxxxxx-ats.iot.xx-xxxxx-x.amazonaws.com"
#define BROKER_PORT         8883
#define CLIENT_ID           "AiThinker-A9G"
#define KEEP_ALIVE          60
#define CLEAN_SESSION       true
#define CLIENT_USER         NULL
#define CLIENT_PASS         NULL
#define SUBSCRIBE_TOPIC     "iotready/gprs"
#define PUBLISH_TOPIC       "iotready/gprs"
#define PUBLISH_INTERVAL    10000 //10s
#define PUBLISH_PAYLOAD     "Hello from the other side!"

#endif
