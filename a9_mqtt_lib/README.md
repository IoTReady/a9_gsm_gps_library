# MQTT Module for the AiThinker A9(GSM+GPRS) and A9G(GSM+GPRS+GPS)

  > This README assumes that you have already setup the GPRS_C_SDK and CSTDK. If not, please follow the instructions [here](./README.md) before continuing.


### Functions of this test example:

This example demos the use of higher level APIs exposed by this library for simpler and faster coding to use MQTT pubsub features with SSL verification.

- Publish to a predefined topic in predefined intervals.(10 seconds by default)

- Subscribe to a predefined topic.

> To verify both the above features with one device, use the same topic for publish and subscribe.

## Setting up and running the example for your AWS IoT:

- Please note that you will need an active SIM card inserted into the dev board in order to test this example successfully.

- Copy the [library folder](./a9_mqtt_lib) of this project into the [demo](https://github.com/Ai-Thinker-Open/GPRS_C_SDK/tree/master/demo) folder of your installed SDK.

- Define your AWS IoT endpoint against the BROKER_HOSTNAME macro in [mqtt_config.h](./a9_mqtt_lib/include/mqtt_config.h) header file.

- Paste the following into the [certs.h](./a9_mqtt_lib/include/certs.h) file for SSL verification:
    * Root CA certificate
    * Client certificate
    * Client private key

- Build and flash the code as mentioned [here](./README.md).
