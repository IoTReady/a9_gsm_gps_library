# Ai-Thinker GPRS modules- A9/A9G Libraries using [Ai-Thinker GPRS C SDK](https://github.com/Ai-Thinker-Open/GPRS-C-SDK)

Wrapper over most used functionalities for the Ai-Thinker GPRS SoC modules A9/A9G for simpler setup and faster deployability.


## Hardware

### 1. [A9: GPRS Module](http://www.ai-thinker.com/pro_view-9.html)

![](./doc/assets/A9.png) </br>

**Datasheet of the A9 module [here](./doc/Datasheets/Ai-Thinker-A9-GPRS-Series-Module-Datasheet)**

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

### 2. [A9G: GPRS + GPS + BDS Module](http://www.ai-thinker.com/pro_view-28.html)

![](./doc/assets/A9G.png) </br>

**Datasheet of the A9G module [here](./doc/Datasheets/Ai-Thinker-A9G-GPRS-Series-Module-Datasheet.pdf)**

**Features**:
  * All the features of A9 above
  * Integrated GPS+BDS (connected to UART2 internal of module)

### 3. [A9](http://www.ai-thinker.com/pro_view-78.html)/[A9G](http://www.ai-thinker.com/pro_view-77.html) GPRS (+GPS+BDS) Development Board( pudding)

![](./doc/assets/A9G_dev.png) </br>
A9/A9G development board for easy development and debugging

**Schematics of the pudding development boards here: [A9](./doc/Schematics/a9-dev-schematic_v1.2.pdf) | [A9G](./doc/Schematics/a9g-dev-schematic_v1.2.pdf)**

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

### Features
* Provide easier-to-use and ready-to-deploy out of the box API. Integrates a wide range of features including:
  - [x] GPIO
  - [x] Power Management
  - [x] MQTT
  - [x] SPI
  - [ ] ADC
  - [ ] I2C
  - [ ] GPS
  - [ ] OTA
  - [ ] Call
  - [ ] SMS
  - [ ] SMS


## Hardware connection

### Module Debugging and Firmware Download
The download interface to the device is the HST interface. Depending upon how the power is being supplied to the board(pudding), the following connections are required in the minimum to provision firmware download into the device or to debug the logs.

| USB to TTL module | Dev Board(pudding) |
| -----------  | -----------   |
| TX           | HST_RX        |
| RX           | HST_TX        |
| GND          | GND           |

### Power Supply
The power can be connected to the lithium battery voltage (ie 3.8v ~ 4.2v) (VBAT pin), can also be connected to 5v power supply (5v input pin or USB input), it should be noted that, if using lithium battery power supply You need to press POWER KEY for about 3 seconds to power on the module. Please note that this is not required when powered through USB.


# Setting up the build environment

## Windows

### Download and install the toolchain:
* Download the toolchain [here](). 
* Decompress the downloaded file into a folder.
* Run `config_env_admin.bat` file in CSDTK to set environment variables required.

### Download the SDK:
* Download the latest released archive from [github release page](https://github.com/Ai-Thinker-Open/GPRS_C_SDK/releases) or clone directly.(need to install `git`)
    ```
    git clone https://github.com/Ai-Thinker-Open/GPRS_C_SDK.git --recursive
    ```
  > This repo has been tested on [this version](https://github.com/Ai-Thinker-Open/GPRS_C_SDK/tree/555064940173977fa51aac860c800a2d3f4e890a)
* Decompress the CSDK downloaded to GPRS_C_SDK folder into a directory, such as ~/projects/GPRS_C_SDK.

### Compile a demo app:
* Navigate into the CSDK folder，right click mouse in the blank space in the folder with shift key pressed, then `Open PowerShell window here`.
* Then you can use `./build.bat` script to build project.

    * ````./build.bat demo $PROJ````: compile demo project $PROJ
        e.g.: ````./build.bat demo gpio````
    * ````./build.bat clean $PROJ````: clear the build files of $PROJ
        e.g.: ````./build.bat clean gpio````
    * ````./build.bat clean all````: clear all build files
    * ````./build.bat demo $PROJ release````: build a release version. If the last parameter is not release, it will be defaulted to debug version. The GDB can be used to debug errors after system crashes in debug version, but release version can not, watch dog activate in release version,it will auto restart system when system crashed!
        e.g.: ````./build.bat demo gpio release````
* A `build` folder and a `hex` folder will be generated after compilation containing the build files.
* In the `hex` folder, two \*.lod files will be generated. These \*.lod files are the target file that are to be flashed into the dev board.
* The two \*.lod files will be significantly different in their sizes. The larger file should be flashed when:
    * Flashing for the first time
    * If SDK level changes have been made    
  Else, the smaller file can be flashed in order to reduce the download time significantly.


## Linux

### Download and install the toolchain:
* Install dependencies for compile tool
````
sudo apt install build-essential gcc-multilib g++-multilib libzip-dev zlib1g lib32z1 libpng12-0 libusb-0.1-4
````
* Since the official download links in the official Ai-Thinker website is dead, download the toolchain [here](https://github.com/pulkin/csdtk42-linux)
* Decompress the downloaded file to a folder, ~/software/CSDTK for example, and then execute setup.sh, the first parameter is the location of CSDTK, the second parameter is the location of your projects.
    ````
    cd ~/software
    tar -xzvf CSDTK42_Linux.tar.gz
    cd CSDTK
    ./setup.sh ./ ~/projects
    ````

### Download the SDK:
* Download the latest released archive from [github release page](https://github.com/Ai-Thinker-Open/GPRS_C_SDK/releases) or clone directly(need to install `git`)
    ```
    git clone https://github.com/Ai-Thinker-Open/GPRS_C_SDK.git --recursive
    ```
  > This repo has been tested on [this version](https://github.com/Ai-Thinker-Open/GPRS_C_SDK/tree/555064940173977fa51aac860c800a2d3f4e890a)
* Decompress the CSDK downloaded to GPRS_C_SDK folder into a directory, such as ~/projects/GPRS_C_SDK.

### Compile a demo app:
* Navigate into the CSDK folder，right click mouse in the blank space in the folder with shift key pressed, then `Open PowerShell window here`.
* Then you can use `./build.sh` script to build project.

    * ````./build.sh demo $PROJ````: compile demo project $PROJ
        e.g.: ````./build.sh demo gpio````
    * ````./build.sh clean $PROJ````: clear the build files of $PROJ
        e.g.: ````./build.sh clean gpio````
    * ````./build.sh clean all````: clear all build files
    * ````./build.sh demo $PROJ release````: build a release version, e.g.:./build.bat demo gpio release，if the last parameter is not release, it will be default to debug version. The GDB can be used to debug errors after system crashed in debug version, but release version can not, watch dog activate in release version,it will auto restart system when system crashed!
        e.g.: ````./build.sh demo gpio release````
* A `build` folder and a `hex` folder will be generated after compilation containing the build files.
* In the `hex` folder, two \*.lod files will be generated. These \*.lod files are the target file that are to be flashed into the dev board.
* The two \*.lod files will be significantly different in their sizes. The larger file should be flashed when:
    * Flashing for the first time
    * If SDK level changes have been made    
  Else, the smaller file can be flashed in order to reduce the download time significantly.


## Flash and Debug:

**Additional Steps for Linux:** (not required for Windows)
* Install dependencies
````
sudo apt install build-essential libqt4-qt3support itcl3 itk3 iwidgets4
````

* Create a link file for serial port as follows, and later you can fill in the coolwatcher's chart with 1. The `COM1` must upper-case.
````
sudo ln -s /dev/ttyUSB0 comport/COM1
````

* Then double click coolwatcher to run software

* Follow further steps as given in [Ai-Thinker GPRS SDK documentation](https://ai-thinker-open.github.io/GPRS_C_SDK_DOC/en/c-sdk/burn-debug.html).

## Project structure and developing applications

Each folder contains C library and their corresponding header files. To use the library files follow the steps below:

- Copy the lib folder of the project to be run into the [demo](https://github.com/Ai-Thinker-Open/GPRS_C_SDK/tree/master/demo) folder of your installed SDK.
- Navigate into the folder and read the README.md file of the specific example to configure the example code if needed. For example, to test the MQTT library example, the endpoint, certificates and keys have to be provided to establish a successful connection.
- Build and flash the code as mentioned above.

**Further Detailed Doumentation** here:  [GPRS C SDK DOC](https://ai-thinker-open.github.io/GPRS_C_SDK_DOC/en)

Including environment installation, burn & debug, api docs etc.


## Feedback

* [create issue on github](https://github.com/IoTReady/a9_libraries/issues/new)

* Click ★ <kbd> Star </kbd> on the right corner of this page if this repo helps you



## Participate in the development

Fork -> Modify -> Submit PR
