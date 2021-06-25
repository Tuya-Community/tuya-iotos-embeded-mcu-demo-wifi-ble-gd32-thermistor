#include "gd32e23x.h"
#include "wifi.h"
#include "delay.h"

/*
    \brief      main function
    \param[in]  none
    \param[out] none
    \retval     none
*/
     
#define WIFI_KEY_LED_GPIO_Port  GPIOB
#define WIFI_KEY_Pin   GPIO_PIN_8
#define WIFI_LED_Pin   GPIO_PIN_9
void Connect_Wifi(void)
{
	
        if (RESET == gpio_input_bit_get(WIFI_KEY_LED_GPIO_Port,WIFI_KEY_Pin))
				  {
						Delay_ms(10);
						if (RESET == gpio_input_bit_get(WIFI_KEY_LED_GPIO_Port,WIFI_KEY_Pin))
							{
										mcu_set_wifi_mode(0);
									  printf("begin connect wifi\r\n");
							}
          }
        switch(mcu_get_wifi_work_state())
        {
						 case SMART_CONFIG_STATE:       
									 printf("smart config\r\n");
									 gpio_bit_toggle( WIFI_KEY_LED_GPIO_Port, WIFI_LED_Pin);
									 Delay_ms(250);
							break;
							case AP_STATE:        
									 printf("AP config\r\n");
									 gpio_bit_toggle(WIFI_KEY_LED_GPIO_Port, WIFI_LED_Pin);
									 Delay_ms(500);
							break;
							case WIFI_NOT_CONNECTED: 
									 printf("connect wifi\r\n");
									 gpio_bit_set(WIFI_KEY_LED_GPIO_Port,WIFI_LED_Pin);
							break;
							case WIFI_CONNECTED:
									 printf("connect success\r\n");
									 gpio_bit_reset(WIFI_KEY_LED_GPIO_Port,WIFI_LED_Pin);
							case WIFI_CONN_CLOUD:
									 gpio_bit_reset(WIFI_KEY_LED_GPIO_Port,WIFI_LED_Pin);
							break;
							default:
									 gpio_bit_set(WIFI_KEY_LED_GPIO_Port,WIFI_LED_Pin);
							     printf ("connect fail\r\n");
							break;
							
        }
}