#ifndef _EXTI_H
#define _EXTI_H
#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/delay/delay.h"

/* 引脚定义 / 中断号 / 中断服务函数 */
#define KEY0_INT_GPIO_PORT              GPIOE
#define KEY0_INT_GPIO_PIN               GPIO_PIN_4
#define KEY0_INT_GPIO_CLK_ENABLE()      do{ __HAL_RCC_GPIOE_CLK_ENABLE(); }while(0)   /* PE口时钟使能 */
#define KEY0_INT_IRQn                   EXTI4_IRQn
#define KEY0_INT_IRQHandler             EXTI4_IRQHandler

#define KEY1_INT_GPIO_PORT              GPIOE
#define KEY1_INT_GPIO_PIN               GPIO_PIN_3
#define KEY1_INT_GPIO_CLK_ENABLE()      do{ __HAL_RCC_GPIOE_CLK_ENABLE(); }while(0)   /* PE口时钟使能 */
#define KEY1_INT_IRQn                   EXTI3_IRQn
#define KEY1_INT_IRQHandler             EXTI3_IRQHandler

#define KEY2_INT_GPIO_PORT              GPIOE
#define KEY2_INT_GPIO_PIN               GPIO_PIN_2
#define KEY2_INT_GPIO_CLK_ENABLE()      do{ __HAL_RCC_GPIOE_CLK_ENABLE(); }while(0)   /* PE口时钟使能 */
#define KEY2_INT_IRQn                   EXTI2_IRQn
#define KEY2_INT_IRQHandler             EXTI2_IRQHandler

#define KEY_UP_INT_GPIO_PORT            GPIOA
#define KEY_UP_INT_GPIO_PIN             GPIO_PIN_0
#define KEY_UP_INT_GPIO_CLK_ENABLE()    do{ __HAL_RCC_GPIOA_CLK_ENABLE(); }while(0)   /* PE口时钟使能 */
#define KEY_UP_INT_IRQn                 EXTI0_IRQn
#define KEY_UP_INT_IRQHandler           EXTI0_IRQHandler

void exti_init(void);  /* 外部中断初始化 */
#endif
