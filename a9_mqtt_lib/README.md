# MQTT Module for the AiThinker A9(GSM+GPRS) and A9G(GSM+GPRS+GPS)

## Running the example for AWS IoT Core

### Setting up your environment:
- Follow the instructions [here](https://ai-thinker-open.github.io/GPRS_C_SDK_DOC/en/).

### Setting up the example for your AWS IoT:
- Copy the root folder of this project into the [demo](https://github.com/Ai-Thinker-Open/GPRS_C_SDK/tree/master/demo) folder of your installed SDK.
- Define your AWS IoT endpoint against the BROKER_HOSTNAME macro in [mqtt_config.h](https://github.com/IoTReady/a9_mqtt_lib/blob/modules/mqtt/include/mqtt_config.h) header file.
- Build and flash the code as mentioned [here](https://ai-thinker-open.github.io/GPRS_C_SDK_DOC/en/c-sdk/burn-debug.html).
