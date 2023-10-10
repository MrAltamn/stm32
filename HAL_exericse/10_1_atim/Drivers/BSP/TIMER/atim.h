#ifndef __ATIM_H
#define __ATIM_H
#include "./SYSTEM/sys/sys.h"

/***********************************************************************************/
/* PWM */
#define ATIM_TIMX_NPWM_GPIO_PORT             GPIOC
#define ATIM_TIMX_NPWM_GPIO_PIN              GPIO_PIN_6
#define ATIM_TIMX_NPWM_CHY_GPIO_CLK_ENABLE() do{ __HAL_RCC_GPIOC_CLK_ENABLE(); }while(0)
#define ATIM_TIMX_NPWM_CHY_GPIO_AF           GPIO_AF3_TIM8

#define ATIM_TIMX_NPWM                       TIM8                                        /* TIM8 */
#define ATIM_TIMX_NPWM_CHY                   TIM_CHANNEL_1                                /* 通道Y,  1<= Y <=4 */
#define ATIM_TIMX_NPWM_IRQn                  TIM8_UP_TIM13_IRQn
#define ATIM_TIMX_NPWM_IRQHandler            TIM8_UP_TIM13_IRQHandler
#define ATIM_TIMX_NPWM_CHY_CCRX              TIM8->CCR1                                  /* 通道Y的输出比较寄存器 */
#define ATIM_TIMX_NPWM_CHY_CLK_ENABLE()      do{ __HAL_RCC_TIM8_CLK_ENABLE(); }while(0)  /* TIM14 时钟使能 */

void atim_timx_npwm_chy_init(uint16_t arr, uint16_t psc);
void atim_timx_npwm_chy_set(uint32_t npwm);
    
#endif
