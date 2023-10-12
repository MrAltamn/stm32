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
