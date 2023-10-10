#include "./BSP/DMA/dma.h"
#include "./SYSTEM/delay/delay.h"
#include "./SYSTEM/usart/usart.h"

DMA_HandleTypeDef g_dma_handle;

void dma_init(DMA_Stream_TypeDef *dma_stream_handle, uint32_t ch)
{
    if ((uint32_t)dma_stream_handle > (uint32_t)DMA2)       /* 得到当前stream是属于DMA2还是DMA1 */
    {
        __HAL_RCC_DMA2_CLK_ENABLE();                        /* DMA2时钟使能 */
    }
    else
    {
        __HAL_RCC_DMA1_CLK_ENABLE();                        /* DMA1时钟使能 */
    }
    
    /* Tx DMA配置 */
    g_dma_handle.Instance = dma_stream_handle;                    /* 数据流选择 */
    g_dma_handle.Init.Channel = ch;                               /* DMA通道选择 */
    g_dma_handle.Init.Direction = DMA_MEMORY_TO_PERIPH;           /* 存储器到外设 */
    g_dma_handle.Init.PeriphInc = DMA_PINC_DISABLE;               /* 外设非增量模式 */
    g_dma_handle.Init.MemInc = DMA_MINC_ENABLE;                   /* 存储器增量模式 */
    g_dma_handle.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;  /* 外设数据长度:8位 */
    g_dma_handle.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;     /* 存储器数据长度:8位 */
    g_dma_handle.Init.Mode = DMA_NORMAL;                          /* 外设流控模式 */
    g_dma_handle.Init.Priority = DMA_PRIORITY_MEDIUM;             /* 中等优先级 */
    g_dma_handle.Init.FIFOMode = DMA_FIFOMODE_DISABLE;            /* 关闭FIFO模式 */
    g_dma_handle.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_FULL;    /* FIFO阈值配置 */
    g_dma_handle.Init.MemBurst = DMA_MBURST_SINGLE;               /* 存储器突发单次传输 */
    g_dma_handle.Init.PeriphBurst = DMA_PBURST_SINGLE;            /* 外设突发单次传输 */
    HAL_DMA_Init(&g_dma_handle);
    
    __HAL_LINKDMA(&g_uart1_handle, hdmatx, g_dma_handle);   /* 将DMA与USART1联系起来(发送DMA) */
}

