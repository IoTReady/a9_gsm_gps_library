# ADS1015 Module for the AiThinker A9(GSM+GPRS) and A9G(GSM+GPRS+GPS)

- The TI [ADS1015 ADC](https://www.ti.com/product/ADS1015) 12-Bit, 3.3kSPS, 4-Ch Delta-Sigma ADC is a well-suited chip for power and space-constrained sensor measurement applications.
- This library provides off-the-shelf ready to use APIs to get the ADC reading with almost no other requirements to be fulfilled.
- Just initialize I2C and call getSingleEnded with the configuration parameters for your use-case and OFF YOU GO!
- Seperate function available to get the output in millivolts, converted according to the PGA gain used in conversion. Sit back and let our functions to the job!


## ADS1015 Example

This test code shows how to configure I2C and communicate with the TI [ADS1015 ADC](https://www.ti.com/product/ADS1015) 12-Bit, 3.3kSPS, 4-Ch Delta-Sigma ADC.


## Running the GPIO example:

  > This README assumes that you have already setup the GPRS_C_SDK and CSTDK. If not, please follow the instructions [here](./README.md) before continuing.

- Copy the [library folder](./a9_gpio_lib) of this project into the [demo](https://github.com/Ai-Thinker-Open/GPRS_C_SDK/tree/master/demo) folder of your installed SDK.

- Build and flash the code as mentioned [here](./README.md).
