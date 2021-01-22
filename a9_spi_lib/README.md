# SPI Module for the AiThinker A9(GSM+GPRS) and A9G(GSM+GPRS+GPS)

  > This README assumes that you have already setup the GPRS_C_SDK and CSTDK. If not, please follow the instructions [here](./README.md) before continuing.

## SPI example

This code gives you a choice between three different modes of SPI communication. You can make this choice by uncommenting the desired mode from [these](./a9_spi_lib/src/spi_example.c#L13-L15) three macros. It is however important to note that only one of those three modes can be selected at once.

If you want to adapt this example to other use-cases, check [spi_lib.h](./a9_spi_lib/include/spi_lib.h) for comments with some implementation details against the functions available.

## Running the SPI example:

- Copy the [library folder](./a9_spi_lib) of this project into the [demo](https://github.com/Ai-Thinker-Open/GPRS_C_SDK/tree/master/demo) folder of your installed SDK.

- https://github.com/github/learn.github.com/blob/38034b3aee7f4fb7f46e94b3f9c2b3d3554291ba/README.md#L20-L23

- Build and flash the code as mentioned [here](./README.md).