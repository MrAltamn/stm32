#include "./BSP/LED/led.h"
#include "./BSP/TIMER/gtim.h"

TIM_HandleTypeDef g_timx_handler;
TIM_HandleTypeDef g_timx_pwm_chy_handler;
TIM_OC_InitTypeDef timx_pwm_chy_handler;

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

void gtim_timx_pwm_chy_init(uint16_t arr, uint16_t psc)
{
    g_timx_pwm_chy_handler.Instance = GTIM_TIMX_PWM;
    g_timx_pwm_chy_handler.Init.Prescaler = psc;
    g_timx_pwm_chy_handler.Init.CounterMode = TIM_COUNTERMODE_UP;
    g_timx_pwm_chy_handler.Init.Period = arr;
    HAL_TIM_PWM_Init(&g_timx_pwm_chy_handler);
    
    timx_pwm_chy_handler.OCMode = TIM_OCMODE_PWM1;
    timx_pwm_chy_handler.Pulse = arr / 2;
    timx_pwm_chy_handler.OCPolarity = TIM_OCPOLARITY_LOW;
    HAL_TIM_PWM_ConfigChannel(&g_timx_pwm_chy_handler, &timx_pwm_chy_handler, GTIM_TIMX_PWM_CHY);
    HAL_TIM_PWM_Start(&g_timx_pwm_chy_handler, GTIM_TIMX_PWM_CHY);
}

void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim)
{
    if(htim->Instance == GTIM_TIMX_PWM)
    {
        GTIM_TIMX_PWM_CHY_GPIO_CLK_ENABLE();
        GTIM_TIMX_PWM_CHY_CLK_ENABLE();
        GPIO_InitTypeDef gpio_init_struct;
        
        gpio_init_struct.Pin = GTIM_TIMX_PWM_GPIO_PIN;
        gpio_init_struct.Mode = GPIO_MODE_AF_PP;
        gpio_init_struct.Pull = GPIO_PULLUP;
        gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;
        gpio_init_struct.Alternate = GTIM_TIMX_PWM_CHY_GPIO_AF;
        
        HAL_GPIO_Init(GTIM_TIMX_PWM_GPIO_PORT, &gpio_init_struct);
    }
}

