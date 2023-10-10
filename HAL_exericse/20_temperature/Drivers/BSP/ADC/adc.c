#include "./BSP/ADC/adc.h"
#include "./SYSTEM/delay/delay.h"


ADC_HandleTypeDef g_adc_handle;   /* ADC��� */

void adc_init(void)
{
    ADC_ChannelConfTypeDef adc_channel = {0};
    
    g_adc_handle.Instance = ADC_ADCX;
    g_adc_handle.Init.ClockPrescaler = ADC_CLOCKPRESCALER_PCLK_DIV4;        /* 4��Ƶ��ADCCLK = PCLK2/4 = 84/4 = 21Mhz */
    g_adc_handle.Init.Resolution = ADC_RESOLUTION_12B;                      /* 12λģʽ */
    g_adc_handle.Init.DataAlign = ADC_DATAALIGN_RIGHT;                      /* �Ҷ��� */
    g_adc_handle.Init.ScanConvMode = DISABLE;                               /* ��ɨ��ģʽ */
    g_adc_handle.Init.ContinuousConvMode = DISABLE;                         /* �ر�����ת�� */
    g_adc_handle.Init.NbrOfConversion = 1;                                  /* 1��ת���ڹ��������� Ҳ����ֻת����������1 */
    g_adc_handle.Init.DiscontinuousConvMode = DISABLE;                      /* ��ֹ����������ģʽ */
    g_adc_handle.Init.NbrOfDiscConversion = 0;                              /* ����������ͨ����Ϊ0 */
    g_adc_handle.Init.ExternalTrigConv = ADC_SOFTWARE_START;                /* ������� */
    g_adc_handle.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE; /* ʹ��������� */
    g_adc_handle.Init.DMAContinuousRequests = DISABLE;                      /* �ر�DMA���� */
    HAL_ADC_Init(&g_adc_handle);
    
    adc_channel.Channel = ADC_ADCX_CHY;
    adc_channel.Rank = 1;
    adc_channel.SamplingTime = ADC_SAMPLETIME_480CYCLES;
    adc_channel.Offset = 0;
    HAL_ADC_ConfigChannel(&g_adc_handle, &adc_channel);
    
}

void HAL_ADC_MspInit(ADC_HandleTypeDef* hadc)
{
    ADC_ADCX_CHY_GPIO_CLK_ENABLE();
    ADC_ADCX_CHY_CLK_ENABLE();
    GPIO_InitTypeDef gpio_init_struct;
    
    gpio_init_struct.Pin = ADC_ADCX_CHY_GPIO_PIN;
    gpio_init_struct.Mode = GPIO_MODE_ANALOG;
    HAL_GPIO_Init(ADC_ADCX_CHY_GPIO_PORT, &gpio_init_struct);
}

uint32_t adc_get_result(void)
{
    HAL_ADC_Start(&g_adc_handle);
    HAL_ADC_PollForConversion(&g_adc_handle, 10);
    return (uint16_t)HAL_ADC_GetValue(&g_adc_handle);
}

void adc_temperature_init(void)
{
    adc_init();
}

short adc_get_temperature(void)
{
    uint32_t adcx;
    short result;
    double temperature;
    
    adcx = adc_get_result();
    
    temperature = adcx * (3.3 / 4096);
    temperature = (temperature - 0.76) / 0.0025 + 25;
    result = temperature *= 100;
    return result;
}
