# Tuya IoTOS Embedded Mcu Demo Wifi Ble GD32_THERMISTOR

[English](./README.md) | [中文](./README_zh.md)

## 简介 

本Demo通过涂鸦智能云平台、涂鸦智能APP、NTC和IoTOS Embeded MCU SDK实现一款温度采集。

已实现功能包括：

+ 温度采集




## 快速上手 

### 编译与烧录
+ 下载[Tuya IoTOS Embeded MCU sdk](https://registry.code.tuya-inc.top/hardware_developer/tuya-iotos-embeded-mcu-demo-4g-vending-machine/tree/master) 

+ 执行Project.uvprojx文件

+ 点击软件中的编译，并完成下载


### 文件介绍 

```
├── Application
│   ├── main.c
│   ├── gd32e23x_it.c
│   ├── systick.c
│   ├── gd32e23x_it.h
│   ├── systick.h
│   ├── gd32e23x_libopt.h
├── GD32E23x_Firmware_Library
│   ├── CMSIS
        ├── Include
           │   ├──gd32e23x.h
           │   ├──system_gd32e23x.h
        ├── Source
           │   ├──startup_gd32e23x.s
           │   ├──system_gd32e23x.h        
│   ├── GD32E23x_standard_peripheral
        ├── Include
        ├── Source
├──User
│   ├── adc.c
│   ├── adc.h
│   ├── connect_wifi.c
│   ├── delay.c
│   ├── delay.h
│   ├── led.c
│   ├── led.h
│   ├── usart.c
│   ├── usart.h
└── MCU_SDK
    ├── mcu_api.c
    ├── mcu_api.h
    ├── protocol.c
    ├── protocol.h
    ├── system.c
    ├── system.h
    └── wifi.h
    
```



### Demo入口

入口文件：main.c

重要函数：main()

+ 对mcu的GPIO，USART，DMA，ADC，TIMER，NTC传感器等进行初始化配置，所有事件在while(1)中轮询判断。




### DP点相关

+ 上报dp点处理: mcu_dp_value_update()

| 函数名 | unsigned char mcu_dp_value_update(unsigned char dpid,unsigned long value) |
| ------ | ------------------------------------------------------------ |
| dpid   | DP的ID号                                                     |
| value  | DP数据                                                       |
| Return | SUCCESS: 成功  ERROR: 失败                                   |



### I/O 列表 

|   NTC    |  UASRT0  | UASRT1  |
| :------: | :------: | :-----: |
| PA1 ADC1 | PA9 TXD  | PA2 TXD |
|          | PA10 RXD | PA3 RXD |

## 相关文档

涂鸦Demo中心：https://developer.tuya.com/cn/demo/



## 技术支持

您可以通过以下方法获得涂鸦的支持:

- 开发者中心：https://developer.tuya.com/cn/
- 帮助中心: https://support.tuya.com/en/help
- 技术支持工单中心: [https://service.console.tuya.com](https://service.console.tuya.com/) 