#include "./BSP/PWMDAC/pwmdac.h"

TIM_HandleTypeDef g_timx_handler;


void pwmdac_init(uint16_t arr, uint16_t psc)
{
    TIM_OC_InitTypeDef g_tim9_ch2handler = {0}; /* 定时器2通道4句柄 */
    
    g_timx_handler.Instance = PWMDAC_TIMX;
    g_timx_handler.Init.Prescaler = psc;
    g_timx_handler.Init.CounterMode = TIM_COUNTERMODE_UP;
    g_timx_handler.Init.Period = arr;
    g_timx_handler.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
    HAL_TIM_Base_Init(&g_timx_handler);
    
    g_tim9_ch2handler.OCMode = TIM_OCMODE_PWM1;                                         /* CH1/2 PWM模式1 */
    g_tim9_ch2handler.Pulse = 0;                                                  /* 设置比较值,此值用来确定占空比，默认比较值为自动重装载值的一半，即占空比为50% */
    g_tim9_ch2handler.OCPolarity = TIM_OCPOLARITY_HIGH;                                 /* 输出比较极性为高 */
    HAL_TIM_PWM_ConfigChannel(&g_timx_handler, &g_tim9_ch2handler, PWMDAC_TIMX_CHY);    /* 配置TIM2通道4 */
    
    HAL_TIM_PWM_Start(&g_timx_handler, PWMDAC_TIMX_CHY);    /* 开启PWM通道4 */
}

void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim)
{
    if(htim->Instance == PWMDAC_TIMX)
    {
        PWMDAC_GPIO_CLK_ENABLE();
        PWMDAC_TIMX_CLK_ENABLE();
        GPIO_InitTypeDef gpio_init_struct;
        
        gpio_init_struct.Pin = PWMDAC_GPIO_PIN;
        gpio_init_struct.Mode = GPIO_MODE_AF_PP;
        gpio_init_struct.Pull = GPIO_PULLUP;
        gpio_init_struct.Speed = GPIO_SPEED_FREQ_LOW;
        gpio_init_struct.Alternate = PWMDAC_GPIO_AFTIMX;
        
        HAL_GPIO_Init(PWMDAC_GPIO_PORT, &gpio_init_struct);
    }
}

void pwmdac_set_voltage(uint16_t vol)
{
    float temp = vol;
    temp /= 100;
    temp = temp * 256 / 3.3;
    
    __HAL_TIM_SET_COMPARE(&g_timx_handler, PWMDAC_TIMX_CHY, temp);  /* 设置新的占空比 */
}


