# Tuya IoTOS Embedded Wi-Fi & Bluetooth LE Thermistor

[English](./README.md) | [中文](./README_zh.md)

## Overview

In this demo, we will show you how to develop with the MCU SDK to enable a NTC thermistor to connect to the Tuya IoT Cloud with the Tuya Smart app.

Feature:

+ Collect temperature




## Get started

### Compile and flash
+ Download Tuya IoTOS embedded code.

+ Run `Project.uvprojx`.

+ Click **Compile** on the software to download the code.


### File introduction

```
├── Application
│   ├── main.c
│   ├── gd32e23x_it.c
│   ├── systick.c
│   ├── gd32e23x_it.h
│   ├── systick.h
│   ├── gd32e23x_libopt.h
├── GD32E23x_Firmware_Library
│   ├── CMSIS
        ├── Include
           │   ├──gd32e23x.h
           │   ├──system_gd32e23x.h
        ├── Source
           │   ├──startup_gd32e23x.s
           │   ├──system_gd32e23x.h        
│   ├── GD32E23x_standard_peripheral
        ├── Include
        ├── Source
├──User
│   ├── adc.c
│   ├── adc.h
│   ├── connect_wifi.c
│   ├── delay.c
│   ├── delay.h
│   ├── led.c
│   ├── led.h
│   ├── usart.c
│   ├── usart.h
└── MCU_SDK
    ├── mcu_api.c
    ├── mcu_api.h
    ├── protocol.c
    ├── protocol.h
    ├── system.c
    ├── system.h
    └── wifi.h

```



### Demo entry

Entry file: `main.c`

Main function: `main()`

+ Initialize and configure the GPIO, USART, DMA, ADC, and timer of the MCU as well as the NTC thermistor. All events are polled and determined in `while(1)`.




### Data point (DP)

+ Process DP data: `mcu_dp_value_update()`

| Function name | unsigned char mcu_dp_value_update(unsigned char dpid,unsigned long value) |
| ------ | ------------------------------------------------------------ |
| dpid | DP ID |
| value | DP data |
| Return | SUCCESS: DP data reporting succeeded. ERROR: DP data reporting failed. |



### Pin configuration

| NTC | UASRT0 | UASRT1 |
| :------: | :------: | :-----: |
| PA1 ADC1 | PA9 TXD | PA2 TXD |
|          | PA10 RXD | PA3 RXD |

## Reference

[Tuya Project Hub](https://developer.tuya.com/demo)



## Technical Support

You can get support from Tuya with the following methods:

- [Tuya IoT Developer Platform](https://developer.tuya.com/en/)
- [Help Center](https://support.tuya.com/en/help)
- [Service & Support](https://service.console.tuya.com)[](https://service.console.tuya.com/)
