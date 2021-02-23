# GPIO Module for the AiThinker A9(GSM+GPRS) and A9G(GSM+GPRS+GPS)

  > This README assumes that you have already setup the GPRS_C_SDK and CSTDK. If not, please follow the instructions [here](./README.md) before continuing.


## GPIO Example

This test code shows how to configure gpio and how to use gpio interrupt with the wrapper functions provided under this library.

### Functions of this test example:

 * GPIO_PIN27: Output, connected to Blue LED on the dev board. Blinks with 1 second intervals.
 * GPIO_PIN4: Input, pulled up, interrupt from falling edge
 * GPIO_PIN2: Input, state of this pin is read when the interrupt triggers on GPIO_PIN4


## Running the GPIO example:

- Copy the [library folder](./a9_gpio_lib) of this project into the [demo](https://github.com/Ai-Thinker-Open/GPRS_C_SDK/tree/master/demo) folder of your installed SDK.

- Build and flash the code as mentioned [here](./README.md).