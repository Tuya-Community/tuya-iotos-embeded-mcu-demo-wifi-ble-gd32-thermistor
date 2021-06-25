#include <gd32e23x.h>
#include <systick.h>
#include <stdio.h>
#include <led.h>
#include <delay.h>
#include <usart.h>
#include <wifi.h>
#include <adc.h>

uint32_t USART0_RECEIVE_Buf[100]; 
uint32_t USART1_RECEIVE_Buf[100]; 
extern void Connect_Wifi(void);

int main(void)
{
    systick_config(); 
		LED_Init();  
	  wifi_protocol_init();//wifi协议初始化
		USART0_Init();
		USART1_Init();
	/* RCU configuration */
	  rcu_config();  
   /* GPIO configuration */
    gpio_config();
   /* ADC configuration */
	  adc_config();
 while(1)
		{
			 Connect_Wifi(); //配网
		   wifi_uart_service();//wifi串口数据处理服务
	     Data_Deal();//采集到的电压值换算成温度值
    }
}
