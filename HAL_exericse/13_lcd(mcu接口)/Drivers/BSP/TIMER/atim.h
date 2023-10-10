#ifndef __ATIM_H
#define __ATIM_H
#include "./SYSTEM/sys/sys.h"

/***********************************************************************************/
/* PWMģʽ */
#define ATIM_TIMX_NPWM_GPIO_PORT             GPIOC
#define ATIM_TIMX_NPWM_GPIO_PIN              GPIO_PIN_6
#define ATIM_TIMX_NPWM_CHY_GPIO_CLK_ENABLE() do{ __HAL_RCC_GPIOC_CLK_ENABLE(); }while(0)
#define ATIM_TIMX_NPWM_CHY_GPIO_AF           GPIO_AF3_TIM8

#define ATIM_TIMX_NPWM                       TIM8                                        /* TIM8 */
#define ATIM_TIMX_NPWM_CHY                   TIM_CHANNEL_1                                /* ͨ��Y,  1<= Y <=4 */
#define ATIM_TIMX_NPWM_IRQn                  TIM8_UP_TIM13_IRQn
#define ATIM_TIMX_NPWM_IRQHandler            TIM8_UP_TIM13_IRQHandler
#define ATIM_TIMX_NPWM_CHY_CCRX              TIM8->CCR1                                  /* ͨ��Y������ȽϼĴ��� */
#define ATIM_TIMX_NPWM_CHY_CLK_ENABLE()      do{ __HAL_RCC_TIM8_CLK_ENABLE(); }while(0)  /* TIM14 ʱ��ʹ�� */

void atim_timx_npwm_chy_init(uint16_t arr, uint16_t psc);
void atim_timx_npwm_chy_set(uint32_t npwm);
    

/***********************************************************************************/
/* ����Ƚ�ģʽ */
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
#define ATIM_TIMX_COMP_CH1_CCRX              ATIM_TIMX_COMP->CCR1                        /* ͨ��1������ȽϼĴ��� */
#define ATIM_TIMX_COMP_CH2_CCRX              ATIM_TIMX_COMP->CCR2                        /* ͨ��2������ȽϼĴ��� */
#define ATIM_TIMX_COMP_CH3_CCRX              ATIM_TIMX_COMP->CCR3                        /* ͨ��3������ȽϼĴ��� */
#define ATIM_TIMX_COMP_CH4_CCRX              ATIM_TIMX_COMP->CCR4                        /* ͨ��4������ȽϼĴ��� */

#define ATIM_TIMX_COMP_CLK_ENABLE()      do{ __HAL_RCC_TIM8_CLK_ENABLE(); }while(0)      /* TIM14 ʱ��ʹ�� */

void atim_timx_comp_pwm_init(uint16_t arr, uint16_t psc);


/***********************************************************************************/
/* �����������������ģʽ */
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
#define ATIM_TIMX_CPLM_CHY_CCRY               ATIM_TIMX_COMP->CCR1                        /* ͨ��Y������ȽϼĴ��� */
#define ATIM_TIMX_CPLM_CLK_ENABLE()           do{ __HAL_RCC_TIM1_CLK_ENABLE(); }while(0)      /* TIM1 ʱ��ʹ�� */

void atim_timx_cplm_pwm_init(uint16_t arr, uint16_t psc);   /* �߼���ʱ�� ������� ��ʼ������ */
void atim_timx_cplm_pwm_set(uint16_t ccr, uint8_t dtg);     /* �߼���ʱ�� ������� ��������Ƚ�ֵ & ����ʱ�� */


/***********************************************************************************/
/* PWM ����ģʽ */
#define ATIM_TIMX_PWMIN_CHY_GPIO_PORT         GPIOC
#define ATIM_TIMX_PWMIN_CHY_GPIO_PIN          GPIO_PIN_6
#define ATIM_TIMX_PWMIN_CHY_GPIO_CLK_ENABLE() do{ __HAL_RCC_GPIOC_CLK_ENABLE(); }while(0)

#define ATIM_TIMX_PWMIN_CHY_GPIO_AF           GPIO_AF3_TIM8

#define ATIM_TIMX_PWMIN                       TIM8                                            /* TIM8 */
#define ATIM_TIMX_PWMIN_CHY                   TIM_CHANNEL_1
#define ATIM_TIMX_PWMIN_IRQn                  TIM8_UP_TIM13_IRQn
#define ATIM_TIMX_PWMIN_IRQHandler            TIM8_UP_TIM13_IRQHandler
#define ATIM_TIMX_PWMIN_CHY_CLK_ENABLE()      do{ __HAL_RCC_TIM8_CLK_ENABLE(); }while(0)      /* TIM8 ʱ��ʹ�� */
#define ATIM_TIMX_PWMIN_CC_IRQn               TIM8_CC_IRQn 
#define ATIM_TIMX_PWMIN_CC_IRQHandler         TIM8_CC_IRQHandler

 /* TIM1 / TIM8 �ж����Ĳ����жϷ�����,��Ҫ��������,����TIM2~5��,����Ҫ���¶��� */
#define ATIM_TIMX_PWMIN_CC_IRQn                 TIM8_CC_IRQn
#define ATIM_TIMX_PWMIN_CC_IRQHandler           TIM8_CC_IRQHandler
void atim_timx_pwmin_chy_init(void);    /* �߼���ʱ�� PWM ���� ��ʼ������ */
void atim_timx_pwmin_chy_restart(void); /* �߼���ʱ�� ����PWM����ģʽ��� */


#endif
