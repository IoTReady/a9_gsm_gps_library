# Power Management Module for the AiThinker A9(GSM+GPRS) and A9G(GSM+GPRS+GPS)

### This library provides functions with better relatable names in order to provide more simplicity and homogeneity while writing code.
- power_get_battery() returns real-time battery voltage.

### Functions of this test example:

- This example demos the use of higher level APIs exposed by this library for simpler and faster coding to use the a9 device in low-power mode.

- Puts the device to low-power mode after 20 seconds of initialization

- Brings the device back to normal mode of operation 20 seconds after it stays in low-power mode.


## Running the example:

  > This README assumes that you have already setup the GPRS_C_SDK and CSTDK. If not, please follow the instructions [here](./README.md) before continuing.
 
- Copy the [library folder](./a9_power_lib) of this project into the [demo](https://github.com/Ai-Thinker-Open/GPRS_C_SDK/tree/master/demo) folder of your installed SDK.

- Build and flash the code as mentioned [here](./README.md).
