#ifndef __GTIM_H
#define __GTIM_H
#include "./SYSTEM/sys/sys.h"

#define GTIM_TIMX_INT              TIM3
#define GTIM_TIMX_INT_IRQn         TIM3_IRQn
#define GTIM_TIMX_INT_IRQHandler   TIM3_IRQHandler
#define GTIM_TIMX_INT_CLK_ENABLE() do{ __HAL_RCC_TIM3_CLK_ENABLE(); }while(0)

void gtim_timx_init(uint16_t arr, uint16_t psc);


#endif
