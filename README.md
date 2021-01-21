# Ai-Thinker GPRS modules- A9/A9G Libraries using [Ai-Thinker GPRS C SDK](https://github.com/Ai-Thinker-Open/GPRS-C-SDK)

Wrapper over most used functionalities for the Ai-Thinker GPRS SoC modules A9/A9G for simpler setup and faster deployability.


## Hardware

### 1. A9: GPRS Module

![](./doc/assets/A9.png) </br>

**Source the A9 module [here](http://www.ai-thinker.com/pro_view-9.html)**

**Features**:
  * RDA 32 bit RISC core, frequency up to 312MHz, with 4k instruction cache, 4k data cache
  * Up to 29 GPIOs (with two download pins)
  * Calendar (Real Time Clock) with alarm
  * 1 USB1.1 device interface
  * 2 UART interface with flow control (+1 download/debug serial port)
  * 2 SPI interface
  * 3 I <sup>2</sup> C interface
  * 1 SDMMC controller (interface)
  * 2 ADC interface, 10 bits
  * 32Mb (4MB) SPI NOR Flash
  * 32Mb (4MB) DDR PSRAM
  * 8kHz, 13Bits/sample ADC mic
  * 48kHz, 16bits/sample DAC Audio
  * Power Management Unit: Lithium battery charge management, integrated DC-DC and LDOs, variable IO voltage
  * 18.8 x 19.2 mm SMD package
  * Quad-band GSM/GPRS (800/900/1800 / 1900MHz)
  * calls
  * SMS service

### 2. A9G: GPRS + GPS + BDS Module

![](./doc/assets/A9G.png) </br>

**Source the A9G module [here](http://www.ai-thinker.com/pro_view-28.html)**

**Features**:
  * All the features of A9 above
  * Integrated GPS+BDS (connected to UART2 internal of module)

### 3. A9/A9G GPRS (+GPS+BDS) Development Board( pudding)

![](./doc/assets/A9G_dev.png) </br>
A9/A9G development board for easy development and debugging

**Source the pudding development boards here: [A9](http://www.ai-thinker.com/pro_view-78.html) | [A9G](http://www.ai-thinker.com/pro_view-77.html)**

**Features**:
  * 1 A9G module (the board be the same that with A9 and A9G, for the A9 and A9G in the same package, the same pin )
  * 29 GPIOs with 2.45mm spacing (with 2 download debug pins (`HST_TX`,` HST_RX`)
  * One SIM card slot (Nano Card <Micro Card <Standard Card)
  * 1 TF card slot
  * 1 GPRS interface with IPEX 1 generation package
  * 1 GPS interface with IPEX 1 generation package
  * 1 micro USB interface
  * 5v-4.2V DC-DC, it can be 5v power supply or 3.8 ~ 4.2V power supply
  * ~~1 accelerometer chip(LIS3DHx)~~(not soldered by default)
  * 1 power key, and a reset button
  * 2 LED
  * 1 microphone </br>
![](./doc/assets/pudding_pin.png) </br>

> Or you can use other RDA8955 chip related module or board

### 4. USB to Serial Module

![](./doc/assets/USB-UART.png) </br>
It should be noted that the USB interface on the development board is not a USB serial port function, but USB1.1 function,
Therefore, in order to download or debug, you need at least one USB to serial port module to connect board's `HST_TX` and` HST_RX` pin

### 5. Power Supply
* board can be light up with 5V(with DC-DC on dev-board) or 4.2V(`VBAT`) power, and ensure supply enough current(Peak current 2A)
* if use lithium battery connected to `VBAT`, you must press <kbd>power-key</kbd> for a while to power up the module, or just pull down the `power-key` pin.
* if `VUSB` connected with 5V(`VBAT` must supply with power ), the module will automaticly power up no matter `power-key` poll down or not.

## SDK

### SDK Features

* Provide easier-to-use and ready-to-deploy out of the box API. Integrates a wide range of features including:
  - [x] GPIO
  - [x] Power Management
  - [x] MQTT
  - [x] SPI

### Get the SDK

* Download the latest released archive from [github release page](https://github.com/Ai-Thinker-Open/GPRS_C_SDK/releases).
  > This repo has been tested on [this version](https://github.com/Ai-Thinker-Open/GPRS_C_SDK/tree/555064940173977fa51aac860c800a2d3f4e890a)

* Or clone directly(need to install `git`)
```
git clone https://github.com/Ai-Thinker-Open/GPRS_C_SDK.git
```

### Develop applications using the SDK

Examples refer to the [demo](https://github.com/Ai-Thinker-Open/GPRS_C_SDK/tree/master/demo) folder

**Doumentation** here:  [GPRS C SDK DOC](https://ai-thinker-open.github.io/GPRS_C_SDK_DOC/en)

Including environment installation, burn & debug, api docs etc.


## Feedback

* [create issue on github](https://github.com/IoTReady/a9_libraries/issues/new)

* Click ★ <kbd> Star </kbd> on the right conner of this page if this repo helps you



## Participate in the development

fork -> modify -> submit PR