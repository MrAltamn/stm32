#ifndef __DAC_H
#define __DAC_H

#include "./SYSTEM/sys/sys.h"

#define DAC_DACX_CHY_GPIO_PORT             GPIOA
#define DAC_DACX_CHY_GPIO_PIN              GPIO_PIN_4
#define DAC_DACX_CHY_GPIO_CLK_ENABLE()     do{ __HAL_RCC_GPIOA_CLK_ENABLE(); }while(0)

#define DAC_DACX                            DAC 
#define DAC_DACX_CHY_CLK_ENABLE()           do{ __HAL_RCC_DAC_CLK_ENABLE(); }while(0)          /* DAC 时钟使能 */

#define DAC_DACX_DMASx                      DMA1_Stream5
#define GTIM_TIMX_INT                       TIM7
#define GTIM_TIMX_INT_CLK_ENABLE()          do{ __HAL_RCC_TIM7_CLK_ENABLE(); }while(0)

void dac_dma_wave_init(void);                                                 /* DAC初始化 */
void dac_dma_wave_enable(uint16_t ndtr, uint16_t arr, uint16_t psc);    /* DAC DMA使能波形输出 */

#endif
