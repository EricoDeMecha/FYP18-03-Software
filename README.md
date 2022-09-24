# FYP18-03

Firmware for a final year project.

## About

Developed for an STM32F407VET6 board 

![STM32F407VET board](docs/imgs/STM32F407VE-board-features.jpg)

with a 320x240 LCD(ILI9341) connected to its FSMC interface.

### Graphics

The GUI is developed using LVGL library.

### Firmware

The firmware is developed on Mbed platform. 


## Getting started 

### Requirement

A linux system(even WSL) with python and ARM toolchain and [```mbed-tools```](https://os.mbed.com/docs/mbed-os/v6.15/build-tools/mbed-cli-2.html) installed.

### Deployment

Using ```mbedcli2``` tool, run the following commands to deploy and build the project.
```bash
mbed-tools deploy .  # to deploy 
mbed-tools configure -m STM32F407VE_BLACK -t GCC_ARM # to configure
mbed-tools compile -m STM32F407VE_BLACK -t GCC_ARM # to  build
```
### Flashing

The generated binary image is located in build directory. Flash the image using the following command

```bash
st-flash <binary name>.bin 0x8000000  # requires stlink installed 
```