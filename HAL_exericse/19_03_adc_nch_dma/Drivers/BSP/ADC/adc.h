#ifndef __ADC_H
#define __ADC_H

#include "./SYSTEM/sys/sys.h"

#define ADC_ADCX_CHY_GPIO_PORT             GPIOA
#define ADC_ADCX_CHY_GPIO_PIN              GPIO_PIN_5
#define ADC_ADCX_CHY_GPIO_CLK_ENABLE()     do{ __HAL_RCC_GPIOA_CLK_ENABLE(); }while(0)

#define ADC_ADCX                            ADC1 
#define ADC_ADCX_CHY                        ADC_CHANNEL_5                                       /* ͨ��Y,  0 <= Y <= 17 */ 
#define ADC_ADCX_CHY_CLK_ENABLE()           do{ __HAL_RCC_ADC1_CLK_ENABLE(); }while(0)          /* ADC1 ʱ��ʹ�� */

#define ADC_ADCX_DMASx                      DMA2_Stream4
#define ADC_ADCX_DMASx_Chanel               DMA_CHANNEL_0       /* ADC1_DMA����Դ */
#define ADC_ADCX_DMASx_IRQn                 DMA2_Stream4_IRQn
#define ADC_ADCX_DMASx_IRQHandler           DMA2_Stream4_IRQHandler

void adc_nch_dma_init(uint32_t mar);        /* ADC DMA�ɼ���ʼ�� */
void adc_nch_dma_enable( uint16_t ndtr);    /* ʹ��һ��ADC DMA�ɼ����� */

#endif
