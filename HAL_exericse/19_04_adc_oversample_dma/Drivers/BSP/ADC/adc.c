#include "./BSP/ADC/adc.h"
#include "./SYSTEM/delay/delay.h"

DMA_HandleTypeDef g_dma_adc_handle;     /* 与ADC关联的DMA句柄 */
ADC_HandleTypeDef g_adc_handle;         /* ADC句柄 */
uint8_t g_adc_dma_sta = 0;              /* DMA传输状态标志, 0,未完成; 1, 已完成 */

void adc_dma_init(uint32_t mar)
{
    ADC_ChannelConfTypeDef adc_channel = {0};
    
    if ((uint32_t)ADC_ADCX_DMASx > (uint32_t)DMA2)     /* 大于DMA1_Stream7, 则为DMA2 */
    {
        __HAL_RCC_DMA2_CLK_ENABLE();                    /* DMA2时钟使能 */
    }
    else 
    {
        __HAL_RCC_DMA1_CLK_ENABLE();                    /* DMA1时钟使能 */
    }
    
    g_dma_adc_handle.Instance = ADC_ADCX_DMASx;                             /* 设置DMA数据流 */
    g_dma_adc_handle.Init.Channel = DMA_CHANNEL_0;                          /* 设置DMA通道 */
    g_dma_adc_handle.Init.Direction = DMA_PERIPH_TO_MEMORY;                 /* DIR = 1 ,  外设到存储器模式 */
    g_dma_adc_handle.Init.PeriphInc = DMA_PINC_DISABLE;                     /* 外设非增量模式 */
    g_dma_adc_handle.Init.MemInc = DMA_MINC_ENABLE;                         /* 存储器增量模式 */
    g_dma_adc_handle.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;    /* 外设数据长度:16位 */
    g_dma_adc_handle.Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;       /* 存储器数据长度:16位 */
    g_dma_adc_handle.Init.Mode = DMA_NORMAL;                                /* 外设流控模式 */
    g_dma_adc_handle.Init.Priority = DMA_PRIORITY_MEDIUM;                   /* 中等优先级 */
    HAL_DMA_Init(&g_dma_adc_handle);
    
    __HAL_LINKDMA(&g_adc_handle, DMA_Handle, g_dma_adc_handle);
    
    
    g_adc_handle.Instance = ADC_ADCX;
    g_adc_handle.Init.ClockPrescaler = ADC_CLOCKPRESCALER_PCLK_DIV4;        /* 4分频，ADCCLK = PCLK2/4 = 84/4 = 21Mhz */
    g_adc_handle.Init.Resolution = ADC_RESOLUTION_12B;                      /* 12位模式 */
    g_adc_handle.Init.DataAlign = ADC_DATAALIGN_RIGHT;                      /* 右对齐 */
    g_adc_handle.Init.ScanConvMode = DISABLE;                               /* 非扫描模式 */
    g_adc_handle.Init.ContinuousConvMode = ENABLE;                          /* 连续转换 */
    g_adc_handle.Init.NbrOfConversion = 1;                                  /* 1个转换在规则序列中 也就是只转换规则序列1 */
    g_adc_handle.Init.DiscontinuousConvMode = DISABLE;                      /* 禁止不连续采样模式 */
    g_adc_handle.Init.NbrOfDiscConversion = 0;                              /* 不连续采样通道数为0 */
    g_adc_handle.Init.ExternalTrigConv = ADC_SOFTWARE_START;                /* 软件触发 */
    g_adc_handle.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE; /* 使用软件触发 */
    g_adc_handle.Init.DMAContinuousRequests = ENABLE;                       /* DMA请求 */
    HAL_ADC_Init(&g_adc_handle);
    
   
    adc_channel.Channel = ADC_CHANNEL_5;
    adc_channel.Rank = 1;
    adc_channel.SamplingTime = ADC_SAMPLETIME_3CYCLES;
    adc_channel.Offset = 0;
    HAL_ADC_ConfigChannel(&g_adc_handle, &adc_channel);
    
    HAL_NVIC_SetPriority(ADC_ADCX_DMASx_IRQn, 2, 3);
    HAL_NVIC_EnableIRQ(ADC_ADCX_DMASx_IRQn);
    
    HAL_DMA_Start_IT(&g_dma_adc_handle, (uint32_t)&ADC1->DR, mar, 0);
    HAL_ADC_Start_DMA(&g_adc_handle, &mar, 0);
}


void HAL_ADC_MspInit(ADC_HandleTypeDef* hadc)
{
    ADC_ADCX_CHY_GPIO_CLK_ENABLE();
    ADC_ADCX_CHY_CLK_ENABLE();
    GPIO_InitTypeDef gpio_init_struct;

    gpio_init_struct.Pin = ADC_ADCX_CHY_GPIO_PIN;
    gpio_init_struct.Mode = GPIO_MODE_ANALOG;
    gpio_init_struct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(ADC_ADCX_CHY_GPIO_PORT, &gpio_init_struct);
}


void adc_dma_enable(uint16_t ndtr)
{
//    __HAL_ADC_DISABLE(&g_adc_handle);           /* 先关闭ADC */
//    
//    __HAL_DMA_DISABLE(&g_dma_adc_handle);       /* 关闭DMA传输 */
//    g_dma_adc_handle.Instance->NDTR = ndtr;     /* 重设DMA传输数据量 */
//    __HAL_DMA_ENABLE(&g_dma_adc_handle);        /* 开启DMA传输 */
//    
//    __HAL_ADC_ENABLE(&g_adc_handle);            /* 重新启动ADC */
//    ADC_ADCX->CR2 |= 1 << 30;                   /* 启动规则转换通道 */
    
    
    ADC_ADCX->CR2 &= ~(1 << 0);
    DMA2_Stream4->CR &= ~(1 << 0);
    while(DMA2_Stream4->CR & (1 << 0));
    ADC_ADCX_DMASx->NDTR = ndtr;
    DMA2_Stream4->CR |= 1 << 0;
    ADC_ADCX->CR2 |= 1 << 0;
    ADC_ADCX->CR2 |= 1 << 30;                   /* 启动规则转换通道 */
}

/**
 * @brief       ADC DMA采集中断服务函数
 * @param       无
 * @retval      无
 */
void ADC_ADCX_DMASx_IRQHandler(void)
{
    if (DMA2->HISR & (1 << 5))      /* 判断DMA数据传输完成 */
    {
        g_adc_dma_sta = 1;          /* 标记DMA传输完成 */
        DMA2->HIFCR |= 1 << 5;      /* 清除DMA2 数据流4 传输完成中断 */
    }
}


