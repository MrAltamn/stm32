#ifndef __ADC_H
#define __ADC_H

#include "./SYSTEM/sys/sys.h"

#define ADC_ADCX_CHY_GPIO_PORT             GPIOF
#define ADC_ADCX_CHY_GPIO_PIN              GPIO_PIN_7
#define ADC_ADCX_CHY_GPIO_CLK_ENABLE()     do{ __HAL_RCC_GPIOF_CLK_ENABLE(); }while(0)

#define ADC_ADCX                            ADC3 
#define ADC_ADCX_CHY                        ADC_CHANNEL_5                                       /* 通道Y,  0 <= Y <= 17 */ 
#define ADC_ADCX_CHY_CLK_ENABLE()           do{ __HAL_RCC_ADC3_CLK_ENABLE(); }while(0)          /* ADC1 时钟使能 */

void adc_init(void);                                            /* ADC初始化 */
uint32_t adc_get_result(void);                                  /* 获得某个通道值 */
void adc_lsen_init(void);
uint8_t adc_get_lsen(void);
#endif
