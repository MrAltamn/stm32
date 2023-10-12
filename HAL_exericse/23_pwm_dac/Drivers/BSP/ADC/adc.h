#ifndef __ADC_H
#define __ADC_H

#include "./SYSTEM/sys/sys.h"

#define ADC_ADCX_CHY_GPIO_PORT             GPIOA
#define ADC_ADCX_CHY_GPIO_PIN              GPIO_PIN_5
#define ADC_ADCX_CHY_GPIO_CLK_ENABLE()     do{ __HAL_RCC_GPIOA_CLK_ENABLE(); }while(0)

#define ADC_ADCX                            ADC1 
#define ADC_ADCX_CHY                        ADC_CHANNEL_5                                       /* ͨ��Y,  0 <= Y <= 17 */ 
#define ADC_ADCX_CHY_CLK_ENABLE()           do{ __HAL_RCC_ADC1_CLK_ENABLE(); }while(0)          /* ADC1 ʱ��ʹ�� */

void adc_init(void);                                            /* ADC��ʼ�� */
uint32_t adc_get_result(uint32_t ch);
uint32_t adc_get_result_average(uint32_t ch, uint8_t times);
void adc_channel_set(ADC_HandleTypeDef *adc_handle, uint32_t ch, uint32_t rank, uint32_t stime);
#endif
