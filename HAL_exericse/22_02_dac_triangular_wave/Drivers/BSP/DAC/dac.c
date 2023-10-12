#include "./BSP/DAC/dac.h"
#include "./SYSTEM/delay/delay.h"


DAC_HandleTypeDef g_dac_handle;                                                 /* DAC句柄 */

void dac_init(void)
{
    DAC_ChannelConfTypeDef dac_ch_conf;                                         /* DAC配置结构体 */
    
    g_dac_handle.Instance = DAC_DACX;                                           /* 基地址 */
    HAL_DAC_Init(&g_dac_handle);
    
    dac_ch_conf.DAC_Trigger = DAC_TRIGGER_NONE;                                 /* 自动触发 */
    dac_ch_conf.DAC_OutputBuffer = DAC_OUTPUTBUFFER_DISABLE;                    /* 不使能缓冲区 */
    HAL_DAC_ConfigChannel(&g_dac_handle, &dac_ch_conf, DAC_CHANNEL_1);
    
    HAL_DAC_Start(&g_dac_handle, DAC_CHANNEL_1);
}

void HAL_DAC_MspInit(DAC_HandleTypeDef *hdac)
{
    if(hdac->Instance == DAC)
    {
        GPIO_InitTypeDef gpio_init_struct;
        DAC_DACX_CHY_GPIO_CLK_ENABLE();
        DAC_DACX_CHY_CLK_ENABLE();
        
        gpio_init_struct.Pin = DAC_DACX_CHY_GPIO_PIN;
        gpio_init_struct.Mode = GPIO_MODE_ANALOG;
        HAL_GPIO_Init(DAC_DACX_CHY_GPIO_PORT, &gpio_init_struct);
    }
}

/*  vol : 0~3300,代表 0~3.3V  */
void dac_set_voltage(uint16_t vol)
{
    double temp = vol;
    
    temp /= 1000;
    temp = temp * 4096 / 3.3;
    if(temp >= 4096) temp = 4095; 
    HAL_DAC_SetValue(&g_dac_handle, DAC_CHANNEL_1, DAC_ALIGN_12B_R, temp);
}

/**
 * @brief       设置DAC_OUT1输出三角波
 *   @note      输出频率 ≈ 1000 / (dt * samples) Khz, 不过在dt较小的时候,比如小于5us时, 由于delay_us
 *              本身就不准了(调用函数,计算等都需要时间,延时很小的时候,这些时间会影响到延时), 频率会偏小.
 * 
 * @param       maxval : 最大值(0 < maxval < 4096), (maxval + 1)必须大于等于samples/2
 * @param       dt     : 每个采样点的延时时间(单位: us)
 * @param       samples: 采样点的个数, samples必须小于等于(maxval + 1) * 2 , 且maxval不能等于0
 * @param       n      : 输出波形个数,0~65535
 *
 * @retval      无
 */
void dac_triangular_wave(uint16_t maxval, uint16_t dt, uint16_t samples, uint16_t n)
{
    uint16_t i, j;
    float incval;           /* 递增量 */
    float Curval;           /* 当前值 */
    
    if((maxval + 1) <= samples) return ;    /* 数据不合法 */
        
    incval = (maxval + 1) / (samples / 2);  /* 计算递增量 */
    
    for(j = 0; j < n; j++)
    { 
        Curval = 0;
        HAL_DAC_SetValue(&g_dac_handle, DAC_CHANNEL_1, DAC_ALIGN_12B_R, Curval);    /* 先输出0 */
        for(i = 0; i < (samples / 2); i++)  /* 输出上升沿 */
        {
            Curval  +=  incval;             /* 新的输出值 */
            HAL_DAC_SetValue(&g_dac_handle, DAC_CHANNEL_1, DAC_ALIGN_12B_R, Curval);
            delay_us(dt);
        } 
        for(i = 0; i < (samples / 2); i++)  /* 输出下降沿 */
        {
            Curval  -=  incval;             /* 新的输出值 */
            HAL_DAC_SetValue(&g_dac_handle, DAC_CHANNEL_1, DAC_ALIGN_12B_R, Curval);
            delay_us(dt);
        }
    }
}
