#include "./BSP/DAC/dac.h"
#include "./SYSTEM/delay/delay.h"


DAC_HandleTypeDef g_dac_dma_handle;                                                 /* DAC��� */
DMA_HandleTypeDef g_dma_dac_handle;                                             /* ��DAC������DMA��� */

extern uint16_t g_dac_sin_buf[4096];            /* �������ݻ����� */
/**
 * @brief       DAC DMA������γ�ʼ������
 *   @note      ������֧��DAC1_OUT1/2ͨ����ʼ��
 *              DAC������ʱ������APB1, ʱ��Ƶ��=42MHz=23.8ns
 *              DAC�����buffer�رյ�ʱ��, �������ʱ����Сֵ: tSETTLING = 3us(F407�����ֲ���д)
 *              ���DAC���������ٶ�ԼΪ:333KHz, ��10����Ϊһ������, ��������33Khz���ҵĲ���
 *
 * @param       outx    : Ҫ��ʼ����ͨ��. 1,ͨ��1; 2,ͨ��2
 * @retval      ��
 */
void dac_dma_wave_init(void)
{
    DAC_ChannelConfTypeDef dac_ch_conf = {0};                               /* DAC���ýṹ�� */
    
    __HAL_RCC_DMA1_CLK_ENABLE();                                            /* DMA1ʱ��ʹ�� */
    
    g_dac_dma_handle.Instance = DAC_DACX;                                       /* ����ַ */
    HAL_DAC_Init(&g_dac_dma_handle);
    
    g_dma_dac_handle.Instance = DAC_DACX_DMASx;                             /* ����DMA������ */
    g_dma_dac_handle.Init.Channel = DMA_CHANNEL_7;                          /* ����DMAͨ�� */
    g_dma_dac_handle.Init.Direction = DMA_MEMORY_TO_PERIPH;                 /* �洢��������ģʽ */
    g_dma_dac_handle.Init.PeriphInc = DMA_PINC_DISABLE;                     /* ���������ģʽ */
    g_dma_dac_handle.Init.MemInc = DMA_MINC_ENABLE;                         /* �洢������ģʽ */
    g_dma_dac_handle.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;    /* �������ݳ���:16λ */
    g_dma_dac_handle.Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;       /* �洢�����ݳ���:16λ */
    g_dma_dac_handle.Init.Mode = DMA_CIRCULAR;                              /* ����ѭ��ģʽ */
    g_dma_dac_handle.Init.Priority = DMA_PRIORITY_MEDIUM;                   /* �е����ȼ� */
    HAL_DMA_Init(&g_dma_dac_handle);
    
    __HAL_LINKDMA(&g_dac_dma_handle, DMA_Handle1, g_dma_dac_handle);
    
    
    dac_ch_conf.DAC_Trigger = DAC_TRIGGER_T7_TRGO;                              /* �Զ����� */
    dac_ch_conf.DAC_OutputBuffer = DAC_OUTPUTBUFFER_DISABLE;                    /* ��ʹ�ܻ����� */
    HAL_DAC_ConfigChannel(&g_dac_dma_handle, &dac_ch_conf, DAC_CHANNEL_1);
    
//    GPIO_InitTypeDef gpio_init_struct;
//    __HAL_RCC_GPIOA_CLK_ENABLE();               /* DACͨ�����Ŷ˿�ʱ��ʹ�� */
//    __HAL_RCC_DAC_CLK_ENABLE();                 /* DAC����ʱ��ʹ�� */
//    __HAL_RCC_DMA1_CLK_ENABLE();                /* DMAʱ��ʹ�� */

//    gpio_init_struct.Pin = GPIO_PIN_4;          /* PA4/5 */
//    gpio_init_struct.Mode = GPIO_MODE_ANALOG;   /* ģ�� */
//    gpio_init_struct.Pull = GPIO_NOPULL;        /* ���������� */
//    HAL_GPIO_Init(GPIOA, &gpio_init_struct);    /* ��ʼ��DAC���� */
//    
//    g_dac_dma_handle.Instance = DAC1;
//    HAL_DAC_Init(&g_dac_dma_handle);            /* DAC��ʼ�� */
//    g_dma_dac_handle.Instance = DMA1_Stream5;  /* ʹ�õ�DAM1 Stream5/6 */
//    g_dma_dac_handle.Init.Channel = DMA_CHANNEL_7;
//    g_dma_dac_handle.Init.Direction = DMA_MEMORY_TO_PERIPH;                 /* �洢��������ģʽ */
//    g_dma_dac_handle.Init.PeriphInc = DMA_PINC_DISABLE;                     /* �����ַ��ֹ���� */
//    g_dma_dac_handle.Init.MemInc = DMA_MINC_ENABLE;                         /* �洢����ַ���� */
//    g_dma_dac_handle.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;    /* �������ݳ���:16λ */
//    g_dma_dac_handle.Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;       /* �洢�����ݳ���:16λ */
//    g_dma_dac_handle.Init.Mode = DMA_CIRCULAR;                              /* ѭ��ģʽ */
//    g_dma_dac_handle.Init.Priority = DMA_PRIORITY_MEDIUM;                   /* �е����ȼ� */
//    g_dma_dac_handle.Init.FIFOMode = DMA_FIFOMODE_DISABLE;                  /* ��ʹ��FIFO */
//    HAL_DMA_Init(&g_dma_dac_handle);                                        /* ��ʼ��DMA */

//    __HAL_LINKDMA(&g_dac_dma_handle, DMA_Handle1, g_dma_dac_handle);        /* DMA�����DAC������� */

//    dac_ch_conf.DAC_Trigger = DAC_TRIGGER_T7_TRGO;                          /* ���ö�ʱ��7���� */
//    dac_ch_conf.DAC_OutputBuffer = DAC_OUTPUTBUFFER_ENABLE;                 /* ʹ��������� */
//    HAL_DAC_ConfigChannel(&g_dac_dma_handle, &dac_ch_conf, DAC_CHANNEL_1);  /* DACͨ��������� */
    
    
    HAL_DMA_Start(&g_dma_dac_handle, (uint32_t)g_dac_sin_buf, (uint32_t)&DAC->DHR12R1, 0);
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




/**
 * @brief       DAC DMAʹ�ܲ������
 *   @note      TIM7������ʱ��Ƶ��(f)����APB1, f = 42 * 2 = 84Mhz.
 *              DAC����Ƶ�� ftrgo = f / ((psc + 1) * (arr + 1))
 *              ����Ƶ�� = ftrgo / ndtr;
 * @param       ndtr        : DMAͨ�����δ���������
 * @param       arr         : TIM7���Զ���װ��ֵ
 * @param       psc         : TIM7�ķ�Ƶϵ��
 * @retval      ��
 */
void dac_dma_wave_enable(uint16_t ndtr, uint16_t arr, uint16_t psc)
{
    TIM_HandleTypeDef g_timx_handler = {0};
    TIM_MasterConfigTypeDef master_config = {0};
    
    GTIM_TIMX_INT_CLK_ENABLE();                                         /* TIM7ʱ��ʹ�� */
    
    g_timx_handler.Instance = GTIM_TIMX_INT;                            /* ѡ��ʱ��7 */
    g_timx_handler.Init.Prescaler = psc;                                /* ��Ƶϵ�� */
    g_timx_handler.Init.CounterMode = TIM_COUNTERMODE_UP;               /* ���ϼ��� */
    g_timx_handler.Init.Period = arr;                                   /* ��װ��ֵ */
    g_timx_handler.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE; /* �Զ���װ */
    HAL_TIM_Base_Init(&g_timx_handler);
    
    master_config.MasterOutputTrigger = TIM_TRGO_UPDATE;
    master_config.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    HAL_TIMEx_MasterConfigSynchronization(&g_timx_handler, &master_config);
    HAL_TIM_Base_Start(&g_timx_handler);
    
    HAL_DAC_Stop_DMA(&g_dac_dma_handle, DAC_CHANNEL_1);
    HAL_DAC_Start_DMA(&g_dac_dma_handle, DAC_CHANNEL_1, (uint32_t *)g_dac_sin_buf, ndtr, DAC_ALIGN_12B_R);
}

//void dac_dma_wave_enable(uint16_t ndtr, uint16_t arr, uint16_t psc)
//{
//    TIM_HandleTypeDef tim7_handle = {0};
//    TIM_MasterConfigTypeDef master_config = {0};

//    __HAL_RCC_TIM7_CLK_ENABLE();                                        /* TIM7ʱ��ʹ�� */

//    tim7_handle.Instance = TIM7;                                        /* ѡ��ʱ��7 */
//    tim7_handle.Init.Prescaler = psc;                                   /* ��Ƶϵ�� */
//    tim7_handle.Init.CounterMode = TIM_COUNTERMODE_UP;                  /* ���ϼ��� */
//    tim7_handle.Init.Period = arr;                                      /* ��װ��ֵ */
//    tim7_handle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE; /* �Զ���װ */
//    HAL_TIM_Base_Init(&tim7_handle);                                    /* ��ʼ����ʱ��7 */

//    master_config.MasterOutputTrigger = TIM_TRGO_UPDATE;
//    master_config.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
//    HAL_TIMEx_MasterConfigSynchronization(&tim7_handle, &master_config);/* ����TIM7 TRGO */
//    HAL_TIM_Base_Start(&tim7_handle);                                   /* ʹ�ܶ�ʱ��7 */

//    HAL_DAC_Stop_DMA(&g_dac_dma_handle, DAC_CHANNEL_1); /* ��ֹ֮ͣǰ�Ĵ��� */
//    HAL_DAC_Start_DMA(&g_dac_dma_handle, DAC_CHANNEL_1, (uint32_t *)g_dac_sin_buf, ndtr, DAC_ALIGN_12B_R);
//}



















