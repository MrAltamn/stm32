#ifndef __GTIM_H
#define __GTIM_H
#include "./SYSTEM/sys/sys.h"

#define GTIM_TIMX_INT              TIM3
#define GTIM_TIMX_INT_IRQn         TIM3_IRQn
#define GTIM_TIMX_INT_IRQHandler   TIM3_IRQHandler
#define GTIM_TIMX_INT_CLK_ENABLE() do{ __HAL_RCC_TIM3_CLK_ENABLE(); }while(0)

void gtim_timx_init(uint16_t arr, uint16_t psc);

/***********************************************************************************/
/* PWM */
#define GTIM_TIMX_PWM_GPIO_PORT             GPIOF
#define GTIM_TIMX_PWM_GPIO_PIN              GPIO_PIN_9
#define GTIM_TIMX_PWM_CHY_GPIO_CLK_ENABLE() do{ __HAL_RCC_GPIOF_CLK_ENABLE(); }while(0)
#define GTIM_TIMX_PWM_CHY_GPIO_AF           GPIO_AF9_TIM14

#define GTIM_TIMX_PWM                       TIM14                                        /* TIM14 */
#define GTIM_TIMX_PWM_CHY                   TIM_CHANNEL_1                                /* 通道Y,  1<= Y <=4 */
#define GTIM_TIMX_PWM_CHY_CCRX              TIM14->CCR1                                  /* 通道Y的输出比较寄存器 */
#define GTIM_TIMX_PWM_CHY_CLK_ENABLE()      do{ __HAL_RCC_TIM14_CLK_ENABLE(); }while(0)  /* TIM14 时钟使能 */

void gtim_timx_pwm_chy_init(uint16_t arr, uint16_t psc);

#endif
