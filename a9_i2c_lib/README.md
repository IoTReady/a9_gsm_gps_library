# I2C Module for the AiThinker A9(GSM+GPRS) and A9G(GSM+GPRS+GPS)

- A simpler easier-to-use wrapper library over the Ai-Thinker GPRS_C_SDK that allows faster coding and easier use of functionalities.
- Forget about creating complex structures or allocating memory/buffers. Just call the functions with your desired parameters according to the documentation provided and you're good to go!
- A quick function to test connection with the I2C peripheral.
- Functions to read data from I2C bus as simple as just providing the I2C address and port selected on the A9!

## I2C Example Configuration:

- Change the definitions as needed for your I2C connection and setup. I2C_ACC -> I2C port to be used. I2C_ADD -> Address of the I2C slave device.

- This example tries to establish communication with the slave I2C device and prints the result accordingly.


## Running the I2C example:

  > This README assumes that you have already setup the GPRS_C_SDK and CSTDK. If not, please follow the instructions [here](./README.md) before continuing.

- Copy the [library folder](./a9_gpio_lib) of this project into the [demo](https://github.com/Ai-Thinker-Open/GPRS_C_SDK/tree/master/demo) folder of your installed SDK.

- Build and flash the code as mentioned [here](./README.md).
