#ifndef __ADC_H
#define __ADC_H
#include <stdint.h>
#define ADC_GPIO_PORT              GPIOA
#define ADC_GPIO_PIN               GPIO_PIN_1
#define R             10000
void rcu_config(void);
void gpio_config(void);
void dma_config(void);
void timer_config(void);
void adc_config(void);
uint16_t adc_get_channel(void);
extern int  Data_Deal(void);
#endif /* __ADC_H */
