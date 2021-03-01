# I2C Module for the AiThinker A9(GSM+GPRS) and A9G(GSM+GPRS+GPS)

  > This README assumes that you have already setup the GPRS_C_SDK and CSTDK. If not, please follow the instructions [here](./README.md) before continuing.


## I2C Example Customization:

- Change the definitions as needed for your I2C connection and setup. I2C_ACC -> I2C port to be used. I2C_ADD -> Address of the I2C slave device.

- This example tries to establish communication with the slave I2C device and prints the result accordingly.


## Running the I2C example:

- Copy the [library folder](./a9_gpio_lib) of this project into the [demo](https://github.com/Ai-Thinker-Open/GPRS_C_SDK/tree/master/demo) folder of your installed SDK.

- Build and flash the code as mentioned [here](./README.md).
