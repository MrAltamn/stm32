#include "./BSP/DAC/dac.h"
#include "./SYSTEM/delay/delay.h"


DAC_HandleTypeDef g_dac_dma_handle;                                                 /* DAC句柄 */
DMA_HandleTypeDef g_dma_dac_handle;                                             /* 与DAC关联的DMA句柄 */

extern uint16_t g_dac_sin_buf[4096];            /* 发送数据缓冲区 */
/**
 * @brief       DAC DMA输出波形初始化函数
 *   @note      本函数支持DAC1_OUT1/2通道初始化
 *              DAC的输入时钟来自APB1, 时钟频率=42MHz=23.8ns
 *              DAC在输出buffer关闭的时候, 输出建立时间最小值: tSETTLING = 3us(F407数据手册有写)
 *              因此DAC输出的最高速度约为:333KHz, 以10个点为一个周期, 最大能输出33Khz左右的波形
 *
 * @param       outx    : 要初始化的通道. 1,通道1; 2,通道2
 * @retval      无
 */
void dac_dma_wave_init(void)
{
    DAC_ChannelConfTypeDef dac_ch_conf = {0};                               /* DAC配置结构体 */
    
    __HAL_RCC_DMA1_CLK_ENABLE();                                            /* DMA1时钟使能 */
    
    g_dac_dma_handle.Instance = DAC_DACX;                                       /* 基地址 */
    HAL_DAC_Init(&g_dac_dma_handle);
    
    g_dma_dac_handle.Instance = DAC_DACX_DMASx;                             /* 设置DMA数据流 */
    g_dma_dac_handle.Init.Channel = DMA_CHANNEL_7;                          /* 设置DMA通道 */
    g_dma_dac_handle.Init.Direction = DMA_MEMORY_TO_PERIPH;                 /* 存储器到外设模式 */
    g_dma_dac_handle.Init.PeriphInc = DMA_PINC_DISABLE;                     /* 外设非增量模式 */
    g_dma_dac_handle.Init.MemInc = DMA_MINC_ENABLE;                         /* 存储器增量模式 */
    g_dma_dac_handle.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;    /* 外设数据长度:16位 */
    g_dma_dac_handle.Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;       /* 存储器数据长度:16位 */
    g_dma_dac_handle.Init.Mode = DMA_CIRCULAR;                              /* 外设循环模式 */
    g_dma_dac_handle.Init.Priority = DMA_PRIORITY_MEDIUM;                   /* 中等优先级 */
    HAL_DMA_Init(&g_dma_dac_handle);
    
    __HAL_LINKDMA(&g_dac_dma_handle, DMA_Handle1, g_dma_dac_handle);
    
    
    dac_ch_conf.DAC_Trigger = DAC_TRIGGER_T7_TRGO;                              /* 自动触发 */
    dac_ch_conf.DAC_OutputBuffer = DAC_OUTPUTBUFFER_DISABLE;                    /* 不使能缓冲区 */
    HAL_DAC_ConfigChannel(&g_dac_dma_handle, &dac_ch_conf, DAC_CHANNEL_1);
    
//    GPIO_InitTypeDef gpio_init_struct;
//    __HAL_RCC_GPIOA_CLK_ENABLE();               /* DAC通道引脚端口时钟使能 */
//    __HAL_RCC_DAC_CLK_ENABLE();                 /* DAC外设时钟使能 */
//    __HAL_RCC_DMA1_CLK_ENABLE();                /* DMA时钟使能 */

//    gpio_init_struct.Pin = GPIO_PIN_4;          /* PA4/5 */
//    gpio_init_struct.Mode = GPIO_MODE_ANALOG;   /* 模拟 */
//    gpio_init_struct.Pull = GPIO_NOPULL;        /* 不带上下拉 */
//    HAL_GPIO_Init(GPIOA, &gpio_init_struct);    /* 初始化DAC引脚 */
//    
//    g_dac_dma_handle.Instance = DAC1;
//    HAL_DAC_Init(&g_dac_dma_handle);            /* DAC初始化 */
//    g_dma_dac_handle.Instance = DMA1_Stream5;  /* 使用的DAM1 Stream5/6 */
//    g_dma_dac_handle.Init.Channel = DMA_CHANNEL_7;
//    g_dma_dac_handle.Init.Direction = DMA_MEMORY_TO_PERIPH;                 /* 存储器到外设模式 */
//    g_dma_dac_handle.Init.PeriphInc = DMA_PINC_DISABLE;                     /* 外设地址禁止自增 */
//    g_dma_dac_handle.Init.MemInc = DMA_MINC_ENABLE;                         /* 存储器地址自增 */
//    g_dma_dac_handle.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;    /* 外设数据长度:16位 */
//    g_dma_dac_handle.Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;       /* 存储器数据长度:16位 */
//    g_dma_dac_handle.Init.Mode = DMA_CIRCULAR;                              /* 循环模式 */
//    g_dma_dac_handle.Init.Priority = DMA_PRIORITY_MEDIUM;                   /* 中等优先级 */
//    g_dma_dac_handle.Init.FIFOMode = DMA_FIFOMODE_DISABLE;                  /* 不使用FIFO */
//    HAL_DMA_Init(&g_dma_dac_handle);                                        /* 初始化DMA */

//    __HAL_LINKDMA(&g_dac_dma_handle, DMA_Handle1, g_dma_dac_handle);        /* DMA句柄与DAC句柄关联 */

//    dac_ch_conf.DAC_Trigger = DAC_TRIGGER_T7_TRGO;                          /* 采用定时器7触发 */
//    dac_ch_conf.DAC_OutputBuffer = DAC_OUTPUTBUFFER_ENABLE;                 /* 使能输出缓冲 */
//    HAL_DAC_ConfigChannel(&g_dac_dma_handle, &dac_ch_conf, DAC_CHANNEL_1);  /* DAC通道输出配置 */
    
    
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
 * @brief       DAC DMA使能波形输出
 *   @note      TIM7的输入时钟频率(f)来自APB1, f = 42 * 2 = 84Mhz.
 *              DAC触发频率 ftrgo = f / ((psc + 1) * (arr + 1))
 *              波形频率 = ftrgo / ndtr;
 * @param       ndtr        : DMA通道单次传输数据量
 * @param       arr         : TIM7的自动重装载值
 * @param       psc         : TIM7的分频系数
 * @retval      无
 */
void dac_dma_wave_enable(uint16_t ndtr, uint16_t arr, uint16_t psc)
{
    TIM_HandleTypeDef g_timx_handler = {0};
    TIM_MasterConfigTypeDef master_config = {0};
    
    GTIM_TIMX_INT_CLK_ENABLE();                                         /* TIM7时钟使能 */
    
    g_timx_handler.Instance = GTIM_TIMX_INT;                            /* 选择定时器7 */
    g_timx_handler.Init.Prescaler = psc;                                /* 分频系数 */
    g_timx_handler.Init.CounterMode = TIM_COUNTERMODE_UP;               /* 向上计数 */
    g_timx_handler.Init.Period = arr;                                   /* 重装载值 */
    g_timx_handler.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE; /* 自动重装 */
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

//    __HAL_RCC_TIM7_CLK_ENABLE();                                        /* TIM7时钟使能 */

//    tim7_handle.Instance = TIM7;                                        /* 选择定时器7 */
//    tim7_handle.Init.Prescaler = psc;                                   /* 分频系数 */
//    tim7_handle.Init.CounterMode = TIM_COUNTERMODE_UP;                  /* 向上计数 */
//    tim7_handle.Init.Period = arr;                                      /* 重装载值 */
//    tim7_handle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE; /* 自动重装 */
//    HAL_TIM_Base_Init(&tim7_handle);                                    /* 初始化定时器7 */

//    master_config.MasterOutputTrigger = TIM_TRGO_UPDATE;
//    master_config.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
//    HAL_TIMEx_MasterConfigSynchronization(&tim7_handle, &master_config);/* 配置TIM7 TRGO */
//    HAL_TIM_Base_Start(&tim7_handle);                                   /* 使能定时器7 */

//    HAL_DAC_Stop_DMA(&g_dac_dma_handle, DAC_CHANNEL_1); /* 先停止之前的传输 */
//    HAL_DAC_Start_DMA(&g_dac_dma_handle, DAC_CHANNEL_1, (uint32_t *)g_dac_sin_buf, ndtr, DAC_ALIGN_12B_R);
//}



















