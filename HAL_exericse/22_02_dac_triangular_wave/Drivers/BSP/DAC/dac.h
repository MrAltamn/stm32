#ifndef __DAC_H
#define __DAC_H

#include "./SYSTEM/sys/sys.h"

#define DAC_DACX_CHY_GPIO_PORT             GPIOA
#define DAC_DACX_CHY_GPIO_PIN              GPIO_PIN_4
#define DAC_DACX_CHY_GPIO_CLK_ENABLE()     do{ __HAL_RCC_GPIOA_CLK_ENABLE(); }while(0)

#define DAC_DACX                            DAC 
#define DAC_DACX_CHY_CLK_ENABLE()           do{ __HAL_RCC_DAC_CLK_ENABLE(); }while(0)          /* DAC 时钟使能 */


void dac_init(void);                                                 /* DAC初始化 */
void dac_set_voltage(uint16_t vol);                                  /* 设置电压值 */
void dac_triangular_wave(uint16_t maxval, uint16_t dt, uint16_t samples, uint16_t n);
#endif
