#include "./BSP/TIMER/atim.h"
#include "./BSP/LED/led.h"

TIM_HandleTypeDef a_timx_npwm_chy_handler;


void atim_timx_npwm_chy_init(uint16_t arr, uint16_t psc)
{
    ATIM_TIMX_NPWM_CHY_GPIO_CLK_ENABLE();
    ATIM_TIMX_NPWM_CHY_CLK_ENABLE();
    
    GPIO_InitTypeDef gpio_init_struct;
    TIM_OC_InitTypeDef timx_npwm_chy_handler;
    
    a_timx_npwm_chy_handler.Instance = ATIM_TIMX_NPWM;
    a_timx_npwm_chy_handler.Init.Prescaler = psc;
    a_timx_npwm_chy_handler.Init.CounterMode = TIM_COUNTERMODE_UP;
    a_timx_npwm_chy_handler.Init.Period = arr;
    a_timx_npwm_chy_handler.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
    a_timx_npwm_chy_handler.Init.RepetitionCounter = 0;
    HAL_TIM_PWM_Init(&a_timx_npwm_chy_handler);
    
    gpio_init_struct.Pin = ATIM_TIMX_NPWM_GPIO_PIN;
    gpio_init_struct.Mode = GPIO_MODE_AF_PP;
    gpio_init_struct.Pull = GPIO_PULLUP;
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;
    gpio_init_struct.Alternate = ATIM_TIMX_NPWM_CHY_GPIO_AF;
    HAL_GPIO_Init(ATIM_TIMX_NPWM_GPIO_PORT, &gpio_init_struct);
    
    timx_npwm_chy_handler.OCMode = TIM_OCMODE_PWM1;
    timx_npwm_chy_handler.Pulse = arr / 2;
    timx_npwm_chy_handler.OCPolarity = TIM_OCPOLARITY_HIGH;
    HAL_TIM_PWM_ConfigChannel(&a_timx_npwm_chy_handler, &timx_npwm_chy_handler, ATIM_TIMX_NPWM_CHY);
    
    HAL_NVIC_SetPriority(ATIM_TIMX_NPWM_IRQn, 1, 3);
    HAL_NVIC_EnableIRQ(ATIM_TIMX_NPWM_IRQn);
    
    __HAL_TIM_ENABLE_IT(&a_timx_npwm_chy_handler, TIM_IT_UPDATE);
    HAL_TIM_PWM_Start(&a_timx_npwm_chy_handler, ATIM_TIMX_NPWM_CHY);
    
}

static uint32_t g_npwm_remain = 0;

void atim_timx_npwm_chy_set(uint32_t npwm)
{
    if (npwm == 0) return;
    
    g_npwm_remain = npwm;
    HAL_TIM_GenerateEvent(&a_timx_npwm_chy_handler, TIM_EVENTSOURCE_UPDATE);
    __HAL_TIM_ENABLE(&a_timx_npwm_chy_handler);
}

void ATIM_TIMX_NPWM_IRQHandler(void)
{
    uint16_t npwm = 0;
    if(__HAL_TIM_GET_FLAG(&a_timx_npwm_chy_handler, TIM_FLAG_UPDATE) != RESET)
    {
        if(g_npwm_remain >= 256)
        {
            g_npwm_remain = g_npwm_remain - 256;
            npwm = 256;
        }else if(g_npwm_remain % 256)
        {
            npwm = g_npwm_remain % 256;
            g_npwm_remain = 0;
        }
        if(npwm)
        {
            ATIM_TIMX_NPWM->RCR = npwm - 1;                                         /* 设置重复计数寄存器值为npwm-1, 即npwm个脉冲 */
            HAL_TIM_GenerateEvent(&a_timx_npwm_chy_handler, TIM_EVENTSOURCE_UPDATE); /* 产生一次更新事件,在中断里面处理脉冲输出 */
            __HAL_TIM_ENABLE(&a_timx_npwm_chy_handler);
        }
        else
        {
            ATIM_TIMX_NPWM->CR1 &= ~(1 << 0); /* 关闭定时器TIMX，使用HAL Disable会清除PWM通道信息，此处不用 */
        }
        
        __HAL_TIM_CLEAR_IT(&a_timx_npwm_chy_handler, TIM_IT_UPDATE);  /* 清除定时器溢出中断标志位 */

    }
}

