#ifndef __ADC_H
#define __ADC_H

#include "./SYSTEM/sys/sys.h"

#define ADC_ADCX_CHY_GPIO_PORT             GPIOF
#define ADC_ADCX_CHY_GPIO_PIN              GPIO_PIN_7
#define ADC_ADCX_CHY_GPIO_CLK_ENABLE()     do{ __HAL_RCC_GPIOF_CLK_ENABLE(); }while(0)

#define ADC_ADCX                            ADC3 
#define ADC_ADCX_CHY                        ADC_CHANNEL_5                                       /* ͨ��Y,  0 <= Y <= 17 */ 
#define ADC_ADCX_CHY_CLK_ENABLE()           do{ __HAL_RCC_ADC3_CLK_ENABLE(); }while(0)          /* ADC1 ʱ��ʹ�� */

void adc_init(void);                                            /* ADC��ʼ�� */
uint32_t adc_get_result(void);                                  /* ���ĳ��ͨ��ֵ */
void adc_lsen_init(void);
uint8_t adc_get_lsen(void);
#endif
