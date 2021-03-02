# MQTT Module for the AiThinker A9(GSM+GPRS) and A9G(GSM+GPRS+GPS)

### This library provides higher level wrapper APIs around the functions provided by the Ai-Thinker SDK.
- The APIs provide easy to use functions that accept parameters for custom use-cases.
- Single functions to initialize, subscribe and publish to MQTT brokers.
- No need to handle complex structures. Just provide suitable parameters and you're good to go!
- Supports SSL and non-SSL mqtt initializations. 

### Functions of this test example:

This example demos the use of higher level APIs exposed by this library for simpler and faster coding to use MQTT pubsub features with SSL verification.

- Publish to a predefined topic in predefined intervals.(10 seconds by default)

- Subscribe to a predefined topic.

> To verify both the above features with one device, use the same topic for publish and subscribe.

## Setting up and running the example for your AWS IoT:

  > This README assumes that you have already setup the GPRS_C_SDK and CSTDK. If not, please follow the instructions [here](./README.md) before continuing.

- Please note that you will need an active SIM card inserted into the dev board in order to test this example successfully.

- Copy the [library folder](./a9_mqtt_lib) of this project into the [demo](https://github.com/Ai-Thinker-Open/GPRS_C_SDK/tree/master/demo) folder of your installed SDK.

- Define your AWS IoT endpoint against the BROKER_HOSTNAME macro in [mqtt_config.h](./a9_mqtt_lib/include/mqtt_config.h) header file.

- Enter the publish and subscribe topics under SUBSCRIBE_TOPIC and PUBLISH_TOPIC respectively. To test the example without access to the AWS IoT console, keep the subscribe topic the same as publish topic. This allows the device to subscribe to its own publish messages.

- Paste the following into the [certs.h](./a9_mqtt_lib/include/certs.h) file for SSL verification:
    * Root CA certificate
    * Client certificate
    * Client private key

- Build and flash the code as mentioned [here](./README.md).
