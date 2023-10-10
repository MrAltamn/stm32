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
#define GTIM_TIMX_PWM_CHY                   TIM_CHANNEL_1                                /* ͨ��Y,  1<= Y <=4 */
#define GTIM_TIMX_PWM_CHY_CCRX              TIM14->CCR1                                  /* ͨ��Y������ȽϼĴ��� */
#define GTIM_TIMX_PWM_CHY_CLK_ENABLE()      do{ __HAL_RCC_TIM14_CLK_ENABLE(); }while(0)  /* TIM14 ʱ��ʹ�� */
void gtim_timx_pwm_chy_init(uint16_t arr, uint16_t psc);
/***********************************************************************************/
/* Input */
#define GTIM_TIMX_CAP_CHY_GPIO_PORT         GPIOA
#define GTIM_TIMX_CAP_CHY_GPIO_PIN          GPIO_PIN_0
#define GTIM_TIMX_CAP_CHY_GPIO_CLK_ENABLE() do{ __HAL_RCC_GPIOA_CLK_ENABLE(); }while(0)
#define GTIM_TIMX_CAP_CHY_GPIO_AF           GPIO_AF2_TIM5

#define GTIM_TIMX_CAP                       TIM5                                        /* TIM5 */
#define GTIM_TIMX_CAP_IRQn                  TIM5_IRQn
#define GTIM_TIMX_CAP_IRQHandler            TIM5_IRQHandler
#define GTIM_TIMX_CAP_CHY                   TIM_CHANNEL_1                                /* ͨ��Y,  1<= Y <=4 */
#define GTIM_TIMX_CAP_CHY_CCRX              TIM5->CCR1                                  /* ͨ��Y������ȽϼĴ��� */
#define GTIM_TIMX_CAP_CHY_CLK_ENABLE()      do{ __HAL_RCC_TIM5_CLK_ENABLE(); }while(0)  /* TIM5 ʱ��ʹ�� */

void gtim_timx_cap_chy_init(uint32_t arr, uint16_t psc);

#endif
