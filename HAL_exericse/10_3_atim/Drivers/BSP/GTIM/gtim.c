#include "./BSP/GTIM/gtim.h"
#include "./BSP/LED/led.h"

TIM_HandleTypeDef g_timx_handler;

void gtim_timx_init(uint16_t arr, uint16_t psc)
{
    GTIM_TIMX_INT_CLK_ENABLE();

    g_timx_handler.Instance = GTIM_TIMX_INT;
    g_timx_handler.Init.Prescaler = psc;
    g_timx_handler.Init.CounterMode = TIM_COUNTERMODE_UP;
    g_timx_handler.Init.Period = arr;
    HAL_TIM_Base_Init(&g_timx_handler);
    
    HAL_NVIC_SetPriority(GTIM_TIMX_INT_IRQn, 1, 3);
    HAL_NVIC_EnableIRQ(GTIM_TIMX_INT_IRQn);
    
    HAL_TIM_Base_Start_IT(&g_timx_handler);
    
}

void GTIM_TIMX_INT_IRQHandler(void)
{
    if(__HAL_TIM_GET_FLAG(&g_timx_handler, TIM_FLAG_UPDATE) != RESET) 
    { 
        LED1_TOGGLE(); 
        /* 清除定时器溢出中断标志位 */ 
        __HAL_TIM_CLEAR_IT(&g_timx_handler, TIM_IT_UPDATE); 
    }
}
