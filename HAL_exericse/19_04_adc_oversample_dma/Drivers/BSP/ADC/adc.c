#include "./BSP/ADC/adc.h"
#include "./SYSTEM/delay/delay.h"

DMA_HandleTypeDef g_dma_adc_handle;     /* ��ADC������DMA��� */
ADC_HandleTypeDef g_adc_handle;         /* ADC��� */
uint8_t g_adc_dma_sta = 0;              /* DMA����״̬��־, 0,δ���; 1, ����� */

void adc_dma_init(uint32_t mar)
{
    ADC_ChannelConfTypeDef adc_channel = {0};
    
    if ((uint32_t)ADC_ADCX_DMASx > (uint32_t)DMA2)     /* ����DMA1_Stream7, ��ΪDMA2 */
    {
        __HAL_RCC_DMA2_CLK_ENABLE();                    /* DMA2ʱ��ʹ�� */
    }
    else 
    {
        __HAL_RCC_DMA1_CLK_ENABLE();                    /* DMA1ʱ��ʹ�� */
    }
    
    g_dma_adc_handle.Instance = ADC_ADCX_DMASx;                             /* ����DMA������ */
    g_dma_adc_handle.Init.Channel = DMA_CHANNEL_0;                          /* ����DMAͨ�� */
    g_dma_adc_handle.Init.Direction = DMA_PERIPH_TO_MEMORY;                 /* DIR = 1 ,  ���赽�洢��ģʽ */
    g_dma_adc_handle.Init.PeriphInc = DMA_PINC_DISABLE;                     /* ���������ģʽ */
    g_dma_adc_handle.Init.MemInc = DMA_MINC_ENABLE;                         /* �洢������ģʽ */
    g_dma_adc_handle.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;    /* �������ݳ���:16λ */
    g_dma_adc_handle.Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;       /* �洢�����ݳ���:16λ */
    g_dma_adc_handle.Init.Mode = DMA_NORMAL;                                /* ��������ģʽ */
    g_dma_adc_handle.Init.Priority = DMA_PRIORITY_MEDIUM;                   /* �е����ȼ� */
    HAL_DMA_Init(&g_dma_adc_handle);
    
    __HAL_LINKDMA(&g_adc_handle, DMA_Handle, g_dma_adc_handle);
    
    
    g_adc_handle.Instance = ADC_ADCX;
    g_adc_handle.Init.ClockPrescaler = ADC_CLOCKPRESCALER_PCLK_DIV4;        /* 4��Ƶ��ADCCLK = PCLK2/4 = 84/4 = 21Mhz */
    g_adc_handle.Init.Resolution = ADC_RESOLUTION_12B;                      /* 12λģʽ */
    g_adc_handle.Init.DataAlign = ADC_DATAALIGN_RIGHT;                      /* �Ҷ��� */
    g_adc_handle.Init.ScanConvMode = DISABLE;                               /* ��ɨ��ģʽ */
    g_adc_handle.Init.ContinuousConvMode = ENABLE;                          /* ����ת�� */
    g_adc_handle.Init.NbrOfConversion = 1;                                  /* 1��ת���ڹ��������� Ҳ����ֻת����������1 */
    g_adc_handle.Init.DiscontinuousConvMode = DISABLE;                      /* ��ֹ����������ģʽ */
    g_adc_handle.Init.NbrOfDiscConversion = 0;                              /* ����������ͨ����Ϊ0 */
    g_adc_handle.Init.ExternalTrigConv = ADC_SOFTWARE_START;                /* ������� */
    g_adc_handle.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE; /* ʹ��������� */
    g_adc_handle.Init.DMAContinuousRequests = ENABLE;                       /* DMA���� */
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
//    __HAL_ADC_DISABLE(&g_adc_handle);           /* �ȹر�ADC */
//    
//    __HAL_DMA_DISABLE(&g_dma_adc_handle);       /* �ر�DMA���� */
//    g_dma_adc_handle.Instance->NDTR = ndtr;     /* ����DMA���������� */
//    __HAL_DMA_ENABLE(&g_dma_adc_handle);        /* ����DMA���� */
//    
//    __HAL_ADC_ENABLE(&g_adc_handle);            /* ��������ADC */
//    ADC_ADCX->CR2 |= 1 << 30;                   /* ��������ת��ͨ�� */
    
    
    ADC_ADCX->CR2 &= ~(1 << 0);
    DMA2_Stream4->CR &= ~(1 << 0);
    while(DMA2_Stream4->CR & (1 << 0));
    ADC_ADCX_DMASx->NDTR = ndtr;
    DMA2_Stream4->CR |= 1 << 0;
    ADC_ADCX->CR2 |= 1 << 0;
    ADC_ADCX->CR2 |= 1 << 30;                   /* ��������ת��ͨ�� */
}

/**
 * @brief       ADC DMA�ɼ��жϷ�����
 * @param       ��
 * @retval      ��
 */
void ADC_ADCX_DMASx_IRQHandler(void)
{
    if (DMA2->HISR & (1 << 5))      /* �ж�DMA���ݴ������ */
    {
        g_adc_dma_sta = 1;          /* ���DMA������� */
        DMA2->HIFCR |= 1 << 5;      /* ���DMA2 ������4 ��������ж� */
    }
}


