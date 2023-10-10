#ifndef __BTIM_H
#define __BTIM_H
#include "./SYSTEM/sys/sys.h"

#define BTIM_TIM6_INT            TIM6
#define BTIM_TIM6_INT_IRQn       TIM6_DAC_IRQn
#define BTIM_TIM6_INT_IRQHandler TIM6_DAC_IRQHandler
#define BTIM_TIM6_INT_CLK_ENABLE() do{ __HAL_RCC_TIM6_CLK_ENABLE(); }while(0)

#define BTIM_TIM7_INT            TIM7
#define BTIM_TIM7_INT_IRQn       TIM7_IRQn
#define BTIM_TIM7_INT_IRQHandler TIM7_IRQHandler
#define BTIM_TIM7_INT_CLK_ENABLE() do{ __HAL_RCC_TIM7_CLK_ENABLE(); }while(0)
void btim_tim6_init(uint16_t arr, uint16_t psc);
void btim_tim7_init(uint16_t arr, uint16_t psc);

#endif

