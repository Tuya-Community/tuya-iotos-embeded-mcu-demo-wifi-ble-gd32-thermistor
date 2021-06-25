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
	  wifi_protocol_init();//wifiЭ���ʼ��
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
			 Connect_Wifi(); //����
		   wifi_uart_service();//wifi�������ݴ������
	     Data_Deal();//�ɼ����ĵ�ѹֵ������¶�ֵ
    }
}
