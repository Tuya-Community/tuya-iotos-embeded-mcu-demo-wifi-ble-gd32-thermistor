#include "gd32e23x.h"
#include "systick.h"
#include "adc.h"
#include "protocol.h"
#include "mcu_api.h"
#include "delay.h"

uint16_t ad_value[2];

/*!
    \brief      configure the different system clocks
    \param[in]  none
    \param[out] none
    \retval     none
*/
void rcu_config(void)
{
    /* enable GPIOA clock */
    rcu_periph_clock_enable(RCU_GPIOA);
	 /* config ADC clock */
    rcu_adc_clock_config(RCU_ADCCK_APB2_DIV6);// ADC时钟为 72/6 = 12MHz
	 /* enable DMA clock */
    rcu_periph_clock_enable(RCU_DMA);
    /* enable ADC clock */
    rcu_periph_clock_enable(RCU_ADC);
	  /* enable timer0 clock */
    rcu_periph_clock_enable(RCU_TIMER0);   
}

/*!
    \brief      configure the GPIO peripheral
    \param[in]  none
    \param[out] none
    \retval     none
*/
void gpio_config(void)
{
    /* config the GPIO as analog mode */
    gpio_mode_set(ADC_GPIO_PORT, GPIO_MODE_ANALOG, GPIO_PUPD_NONE, ADC_GPIO_PIN);/* ADC输入PA1 */
}

/*!
    \brief      configure the DMA peripheral
    \param[in]  none
    \param[out] none
    \retval     none
*/
void dma_config(void)
{
    dma_parameter_struct dma_init_struct;
    /* initialize DMA channel0 */
    dma_deinit(DMA_CH0);
    dma_init_struct.direction    = DMA_PERIPHERAL_TO_MEMORY;
    dma_init_struct.memory_addr  = (uint32_t)ad_value;
    dma_init_struct.memory_inc   = DMA_MEMORY_INCREASE_ENABLE;
    dma_init_struct.memory_width = DMA_MEMORY_WIDTH_16BIT;
    dma_init_struct.number       = 2;
    dma_init_struct.periph_addr  = (uint32_t)&(ADC_RDATA);
    dma_init_struct.periph_inc   = DMA_PERIPH_INCREASE_DISABLE;
    dma_init_struct.periph_width = DMA_PERIPHERAL_WIDTH_16BIT;
    dma_init_struct.priority     = DMA_PRIORITY_ULTRA_HIGH;
    dma_init(DMA_CH0, &dma_init_struct);
    
    /* configure DMA mode */
    dma_circulation_enable(DMA_CH0);
    dma_memory_to_memory_disable(DMA_CH0);
    
    /* enable DMA channel0 */
    dma_channel_enable(DMA_CH0);
}
/*!
    \brief      configure the TIMER peripheral
    \param[in]  none
    \param[out] none
    \retval     none
*/
void timer_config(void)
{
    timer_oc_parameter_struct timer_ocintpara;
    timer_parameter_struct timer_initpara;
    timer_deinit(TIMER0);

    /* TIMER0 configuration */
    timer_initpara.prescaler         = 5;// 72/6 = 12MHz
    timer_initpara.alignedmode       = TIMER_COUNTER_EDGE;
    timer_initpara.counterdirection  = TIMER_COUNTER_UP;
    timer_initpara.period            = 399;// 12MHz/400 = 30KHz
    timer_initpara.clockdivision     = TIMER_CKDIV_DIV1;
    timer_initpara.repetitioncounter = 0;
    timer_init(TIMER0, &timer_initpara);

    /* CH0 configuration in PWM mode1 */
    timer_ocintpara.ocpolarity  = TIMER_OC_POLARITY_LOW;
    timer_ocintpara.outputstate = TIMER_CCX_ENABLE;
    timer_channel_output_config(TIMER0, TIMER_CH_0, &timer_ocintpara);

    timer_channel_output_pulse_value_config(TIMER0, TIMER_CH_0, 100);
    timer_channel_output_mode_config(TIMER0, TIMER_CH_0, TIMER_OC_MODE_PWM1);
    timer_channel_output_shadow_config(TIMER0, TIMER_CH_0, TIMER_OC_SHADOW_DISABLE);

    /* auto-reload preload enable */
    timer_auto_reload_shadow_enable(TIMER0);
    timer_primary_output_config(TIMER0, ENABLE);
}
/*!
    \brief      configure the ADC peripheral
    \param[in]  none
    \param[out] none
    \retval     none
*/
void adc_config(void)
{   

	  dma_config();
	  timer_config();
	
	  /* ADC contineous function enable */
    adc_special_function_config(ADC_SCAN_MODE, ENABLE);
    /* ADC channel length config */
    adc_channel_length_config(ADC_REGULAR_CHANNEL, 1);

    /* ADC regular channe0 config */
    adc_regular_channel_config(0, ADC_CHANNEL_1, ADC_SAMPLETIME_55POINT5);//序号0 通道0，采样周期55.5
	  /* ADC分辨率 12B */
	   adc_resolution_config(ADC_RESOLUTION_12B);
    /* ADC external trigger enable */
    adc_external_trigger_config(ADC_REGULAR_CHANNEL, ENABLE);
    /* ADC external trigger source config */
    adc_external_trigger_source_config(ADC_REGULAR_CHANNEL, ADC_EXTTRIG_REGULAR_T0_CH0);//选择TIMER0_CH0为外部触发源
    /* ADC data alignment config */
    adc_data_alignment_config(ADC_DATAALIGN_RIGHT);
    /* enable ADC interface */
    adc_enable();
	  Delay_ms(1U);
    /* ADC calibration and reset calibration */
    adc_calibration_enable();
    /* ADC DMA function enable */
    adc_dma_mode_enable();
}

uint16_t adc_get_channel(void)
{
  uint16_t  recv_ad_val = 0;
	timer_enable(TIMER0);
	/* test on channel0 transfer complete flag */
	while( !dma_flag_get(DMA_CH0, DMA_FLAG_FTF));
	/* clear channel0 transfer complete flag */
	dma_flag_clear(DMA_CH0, DMA_FLAG_FTF);
	
	/* TIMER0 counter disable */
	timer_disable(TIMER0);
	recv_ad_val = (ad_value[0]+ad_value[1])/2;
	return recv_ad_val;
}
//数据处理
int Data_Deal()//采集到的电压值换算成温度值
{
	float voltage=0;
	int Rntc = 0;
  float Rp = 10000.0;
  float T2 = 273.15 + 25.0;
  float Bx = 3950.0;
  float Ka = 273.15;
	uint16_t  temp_var=0;
	int temp = 0;
	
	temp_var=adc_get_channel();
	voltage=(	temp_var * 3.3)/4096;
	Rntc = voltage*R/(3.3-voltage);
	temp =(int)(1/(1/T2+(log(Rntc/Rp)/Bx))-Ka+0.5);
	//printf("x:%.1f | y:%d| z:%d | h:%d\r\n",voltage,Rntc,temp,temp_var);
  mcu_dp_value_update(DPID_TEMP_CURRENT,temp); //温度上报;
  return temp;
}
