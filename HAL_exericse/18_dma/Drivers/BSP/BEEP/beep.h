#ifndef _BEEP_H
#define _BEEP_H

#include "./SYSTEM/sys/sys.h"

/* 引脚定义 */
#define BEEP_GPIO_PORT      GPIOF
#define BEEP_GPIO_PIN       GPIO_PIN_8

/* PF口使能 */
#define BEEP_GPIO_CLK_ENABLE() do{ __HAL_RCC_GPIOF_CLK_ENABLE(); }while(0)

/* 蜂鸣器控制 1-响，0-听*/
#define BEEP(x) do{ x ? \
                    HAL_GPIO_WritePin(BEEP_GPIO_PORT, BEEP_GPIO_PIN, GPIO_PIN_SET) : \
                    HAL_GPIO_WritePin(BEEP_GPIO_PORT, BEEP_GPIO_PIN, GPIO_PIN_RESET); \
                  }while(0) 

/* 蜂鸣器翻转 */
#define BEEP_TOGGLE() do{ HAL_GPIO_TogglePin(BEEP_GPIO_PORT, BEEP_GPIO_PIN ); }while(0)

/* 声明蜂鸣器初始化函数 */
void beep_init(void);
#endif
