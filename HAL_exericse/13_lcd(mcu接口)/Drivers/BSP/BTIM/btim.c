#include "./BSP/BTIM/btim.h"
#include "./BSP/LED/led.h"
#include "./BSP/BEEP/beep.h"
TIM_HandleTypeDef tim_handler;

void btim_tim6_init(uint16_t arr, uint16_t psc)
{
    tim_handler.Instance = BTIM_TIM6_INT;
    tim_handler.Init.Prescaler = psc;
    tim_handler.Init.CounterMode = TIM_COUNTERMODE_UP;
    tim_handler.Init.Period = arr;
    HAL_TIM_Base_Init(&tim_handler);
    
    HAL_TIM_Base_Start_IT(&tim_handler);
    
}

void btim_tim7_init(uint16_t arr, uint16_t psc)
{
    tim_handler.Instance = BTIM_TIM7_INT;
    tim_handler.Init.Prescaler = psc;
    tim_handler.Init.CounterMode = TIM_COUNTERMODE_UP;
    tim_handler.Init.Period = arr;
    HAL_TIM_Base_Init(&tim_handler);

    //HAL_TIM_Base_Start_IT(&tim_handler);
    
}

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == BTIM_TIM6_INT)
    {
        BTIM_TIM6_INT_CLK_ENABLE();
        
        HAL_NVIC_SetPriority(BTIM_TIM6_INT_IRQn, 1, 3);
        HAL_NVIC_EnableIRQ(BTIM_TIM6_INT_IRQn);
    }
    if (htim->Instance == BTIM_TIM7_INT)
    {
        BTIM_TIM7_INT_CLK_ENABLE();
        
        HAL_NVIC_SetPriority(BTIM_TIM7_INT_IRQn, 1, 2);
        HAL_NVIC_EnableIRQ(BTIM_TIM7_INT_IRQn);
    }
}

void BTIM_TIM6_INT_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&tim_handler);
}
void BTIM_TIM7_INT_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&tim_handler);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == BTIM_TIM6_INT)
    {
        LED1_TOGGLE();
    }
    if (htim->Instance == BTIM_TIM7_INT)
    {
        BEEP_TOGGLE();
    }
}
