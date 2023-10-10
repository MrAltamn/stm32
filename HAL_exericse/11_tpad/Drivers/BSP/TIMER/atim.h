#ifndef __ATIM_H
#define __ATIM_H
#include "./SYSTEM/sys/sys.h"

/***********************************************************************************/
/* PWM模式 */
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
    

/***********************************************************************************/
/* 输出比较模式 */
#define ATIM_TIMX_COMP_CH1_GPIO_PORT         GPIOC
#define ATIM_TIMX_COMP_CH1_GPIO_PIN          GPIO_PIN_6
#define ATIM_TIMX_COMP_CH1_GPIO_CLK_ENABLE() do{ __HAL_RCC_GPIOC_CLK_ENABLE(); }while(0)

#define ATIM_TIMX_COMP_CH2_GPIO_PORT         GPIOC
#define ATIM_TIMX_COMP_CH2_GPIO_PIN          GPIO_PIN_7
#define ATIM_TIMX_COMP_CH2_GPIO_CLK_ENABLE() do{ __HAL_RCC_GPIOC_CLK_ENABLE(); }while(0)

#define ATIM_TIMX_COMP_CH3_GPIO_PORT         GPIOC
#define ATIM_TIMX_COMP_CH3_GPIO_PIN          GPIO_PIN_8
#define ATIM_TIMX_COMP_CH3_GPIO_CLK_ENABLE() do{ __HAL_RCC_GPIOC_CLK_ENABLE(); }while(0)

#define ATIM_TIMX_COMP_CH4_GPIO_PORT         GPIOC
#define ATIM_TIMX_COMP_CH4_GPIO_PIN          GPIO_PIN_9
#define ATIM_TIMX_COMP_CH4_GPIO_CLK_ENABLE() do{ __HAL_RCC_GPIOC_CLK_ENABLE(); }while(0)

#define ATIM_TIMX_COMP_GPIO_AF               GPIO_AF3_TIM8
#define ATIM_TIMX_COMP                       TIM8                                        /* TIM8 */
#define ATIM_TIMX_COMP_CH1_CCRX              ATIM_TIMX_COMP->CCR1                        /* 通道1的输出比较寄存器 */
#define ATIM_TIMX_COMP_CH2_CCRX              ATIM_TIMX_COMP->CCR2                        /* 通道2的输出比较寄存器 */
#define ATIM_TIMX_COMP_CH3_CCRX              ATIM_TIMX_COMP->CCR3                        /* 通道3的输出比较寄存器 */
#define ATIM_TIMX_COMP_CH4_CCRX              ATIM_TIMX_COMP->CCR4                        /* 通道4的输出比较寄存器 */

#define ATIM_TIMX_COMP_CLK_ENABLE()      do{ __HAL_RCC_TIM8_CLK_ENABLE(); }while(0)      /* TIM14 时钟使能 */

void atim_timx_comp_pwm_init(uint16_t arr, uint16_t psc);


/***********************************************************************************/
/* 互补输出带死区控制模式 */
#define ATIM_TIMX_CPLM_CHY_GPIO_PORT          GPIOE
#define ATIM_TIMX_CPLM_CHY_GPIO_PIN           GPIO_PIN_9
#define ATIM_TIMX_CPLM_CHY_GPIO_CLK_ENABLE()  do{ __HAL_RCC_GPIOE_CLK_ENABLE(); }while(0)

#define ATIM_TIMX_CPLM_CHYN_GPIO_PORT         GPIOE
#define ATIM_TIMX_CPLM_CHYN_GPIO_PIN          GPIO_PIN_8
#define ATIM_TIMX_CPLM_CHYN_GPIO_CLK_ENABLE() do{ __HAL_RCC_GPIOE_CLK_ENABLE(); }while(0)

#define ATIM_TIMX_CPLM_BKIN_GPIO_PORT         GPIOE
#define ATIM_TIMX_CPLM_BKIN_GPIO_PIN          GPIO_PIN_15
#define ATIM_TIMX_CPLM_BKIN_GPIO_CLK_ENABLE() do{ __HAL_RCC_GPIOE_CLK_ENABLE(); }while(0)

#define ATIM_TIMX_CPLM_CHY_GPIO_AF            GPIO_AF1_TIM1

#define ATIM_TIMX_CPLM                        TIM1                                        /* TIM1 */
#define ATIM_TIMX_CPLM_CHY                    TIM_CHANNEL_1
#define ATIM_TIMX_CPLM_CHY_CCRY               ATIM_TIMX_COMP->CCR1                        /* 通道Y的输出比较寄存器 */
#define ATIM_TIMX_CPLM_CLK_ENABLE()           do{ __HAL_RCC_TIM1_CLK_ENABLE(); }while(0)      /* TIM1 时钟使能 */

void atim_timx_cplm_pwm_init(uint16_t arr, uint16_t psc);   /* 高级定时器 互补输出 初始化函数 */
void atim_timx_cplm_pwm_set(uint16_t ccr, uint8_t dtg);     /* 高级定时器 互补输出 设置输出比较值 & 死区时间 */


/***********************************************************************************/
/* PWM 输入模式 */
#define ATIM_TIMX_PWMIN_CHY_GPIO_PORT         GPIOC
#define ATIM_TIMX_PWMIN_CHY_GPIO_PIN          GPIO_PIN_6
#define ATIM_TIMX_PWMIN_CHY_GPIO_CLK_ENABLE() do{ __HAL_RCC_GPIOC_CLK_ENABLE(); }while(0)

#define ATIM_TIMX_PWMIN_CHY_GPIO_AF           GPIO_AF3_TIM8

#define ATIM_TIMX_PWMIN                       TIM8                                            /* TIM8 */
#define ATIM_TIMX_PWMIN_CHY                   TIM_CHANNEL_1
#define ATIM_TIMX_PWMIN_IRQn                  TIM8_UP_TIM13_IRQn
#define ATIM_TIMX_PWMIN_IRQHandler            TIM8_UP_TIM13_IRQHandler
#define ATIM_TIMX_PWMIN_CHY_CLK_ENABLE()      do{ __HAL_RCC_TIM8_CLK_ENABLE(); }while(0)      /* TIM8 时钟使能 */
#define ATIM_TIMX_PWMIN_CC_IRQn               TIM8_CC_IRQn 
#define ATIM_TIMX_PWMIN_CC_IRQHandler         TIM8_CC_IRQHandler

 /* TIM1 / TIM8 有独立的捕获中断服务函数,需要单独定义,对于TIM2~5等,则不需要以下定义 */
#define ATIM_TIMX_PWMIN_CC_IRQn                 TIM8_CC_IRQn
#define ATIM_TIMX_PWMIN_CC_IRQHandler           TIM8_CC_IRQHandler
void atim_timx_pwmin_chy_init(void);    /* 高级定时器 PWM 输入 初始化函数 */
void atim_timx_pwmin_chy_restart(void); /* 高级定时器 重启PWM输入模式检测 */


#endif
