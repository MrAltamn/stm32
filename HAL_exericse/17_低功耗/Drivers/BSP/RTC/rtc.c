#include "./BSP/RTC/rtc.h"
#include "./BSP/LED/led.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/BEEP/beep.h"

RTC_HandleTypeDef g_rtc_handle;

void rtc_write_bkr(uint32_t bkrx, uint32_t data)
{
    HAL_PWR_EnableBkUpAccess();     /* ȡ��������д���� */
    HAL_RTCEx_BKUPWrite(&g_rtc_handle, bkrx, data);
}

uint32_t rtc_read_bkr(uint32_t bkrx)
{
    uint32_t temp = 0;
    temp = HAL_RTCEx_BKUPRead(&g_rtc_handle, bkrx);
    return temp; /* ���ض�ȡ����ֵ */
}

HAL_StatusTypeDef rtc_set_time(uint8_t hour, uint8_t min, uint8_t sec, uint8_t ampm)
{
    RTC_TimeTypeDef rtc_time_handle;

    rtc_time_handle.Hours = hour;
    rtc_time_handle.Minutes = min;
    rtc_time_handle.Seconds = sec;
    rtc_time_handle.TimeFormat = ampm;
    rtc_time_handle.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
    rtc_time_handle.StoreOperation = RTC_STOREOPERATION_RESET;
    return HAL_RTC_SetTime(&g_rtc_handle, &rtc_time_handle, RTC_FORMAT_BIN);
}

HAL_StatusTypeDef rtc_set_date(uint8_t year, uint8_t month, uint8_t date, uint8_t week)
{
    RTC_DateTypeDef rtc_date_handle;

    rtc_date_handle.Date = date;
    rtc_date_handle.Month = month;
    rtc_date_handle.WeekDay = week;
    rtc_date_handle.Year = year;
    return HAL_RTC_SetDate(&g_rtc_handle, &rtc_date_handle, RTC_FORMAT_BIN);
}

void rtc_get_time(uint8_t *hour, uint8_t *min, uint8_t *sec, uint8_t *ampm)
{
    
    RTC_TimeTypeDef rtc_time_handle;

    HAL_RTC_GetTime(&g_rtc_handle, &rtc_time_handle, RTC_FORMAT_BIN);

    *hour = rtc_time_handle.Hours;
    *min = rtc_time_handle.Minutes;
    *sec = rtc_time_handle.Seconds;
    *ampm = rtc_time_handle.TimeFormat;
}

void rtc_get_date(uint8_t *year, uint8_t *month, uint8_t *date, uint8_t *week)
{
    RTC_DateTypeDef rtc_date_handle;

    HAL_RTC_GetDate(&g_rtc_handle, &rtc_date_handle, RTC_FORMAT_BIN);

    *year = rtc_date_handle.Year;
    *month = rtc_date_handle.Month;
    *date = rtc_date_handle.Date;
    *week = rtc_date_handle.WeekDay;
}

uint8_t rtc_init(void)
{
    uint16_t bkpflag = 0;
    
    __HAL_RCC_PWR_CLK_ENABLE(); /* ʹ�ܵ�Դʱ��PWR */
    HAL_PWR_EnableBkUpAccess(); /* ȡ����������д���� */
    
    g_rtc_handle.Instance = RTC;
    g_rtc_handle.Init.SynchPrediv = 0xFF;               /* ͬ����Ƶϵ�� 1~0x7F */
    g_rtc_handle.Init.AsynchPrediv = 0x7F;              /* �첽��Ƶϵ�� 1~0xFF */
    g_rtc_handle.Init.HourFormat = RTC_HOURFORMAT_24;   /* 24Сʱ��ʽ */
    g_rtc_handle.Init.OutPut = RTC_OUTPUT_DISABLE;
    g_rtc_handle.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
    g_rtc_handle.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
    HAL_RTC_Init(&g_rtc_handle);
    
    /* ����ǲ��ǵ�һ������ʱ�� */
    bkpflag = rtc_read_bkr(0);                /* ��ȡBKP0��ֵ */
    
    if ((bkpflag != 0x5050))     /* ֮ǰδ��ʼ����, �������� */
    {
        rtc_set_time(11, 42, 50, RTC_HOURFORMAT12_AM);   /* ����ʱ��, ����ʵ��ʱ���޸� */
        rtc_set_date(23, 9, 27, 3);                     /* �������� */
    }
    
    return 1;
}

void HAL_RTC_MspInit(RTC_HandleTypeDef* hrtc)
{
    RCC_OscInitTypeDef rcc_osc_init_handle;
    RCC_PeriphCLKInitTypeDef rcc_periphclk_init_handle;
    
    __HAL_RCC_RTC_ENABLE();     /* RTCʹ�� */
    
    /* �����ⲿ��������LSE */
    rcc_osc_init_handle.OscillatorType = RCC_OSCILLATORTYPE_LSE;        /* ѡ��Ҫ���õ����� */
    rcc_osc_init_handle.PLL.PLLState = RCC_PLL_NONE;                    /* PLL������ */
    rcc_osc_init_handle.LSEState = RCC_LSE_ON;                          /* LSE״̬:���� */
    HAL_RCC_OscConfig(&rcc_osc_init_handle);
    
    rcc_periphclk_init_handle.PeriphClockSelection = RCC_PERIPHCLK_RTC; /* ѡ��Ҫ��������RTC */
    rcc_periphclk_init_handle.RTCClockSelection = RCC_RTCCLKSOURCE_LSE; /* RTCʱ��Դѡ��LSE */
    HAL_RCCEx_PeriphCLKConfig(&rcc_periphclk_init_handle);              /* �������õ�rcc_periphclkinitstruct */
    rtc_write_bkr(0, 0x5050);
}

void rtc_set_alarma(uint8_t week, uint8_t hour, uint8_t min, uint8_t sec)
{
    RTC_AlarmTypeDef rtc_alarm_handle;
    
    rtc_alarm_handle.AlarmTime.Hours = hour;                                /* Сʱ */
    rtc_alarm_handle.AlarmTime.Minutes = min;                               /* ���� */
    rtc_alarm_handle.AlarmTime.Seconds = sec;                               /* �� */
    rtc_alarm_handle.AlarmTime.SubSeconds = 0;
    rtc_alarm_handle.AlarmTime.TimeFormat = RTC_HOURFORMAT12_AM;
    
    rtc_alarm_handle.AlarmMask = RTC_ALARMMASK_NONE;
    rtc_alarm_handle.AlarmSubSecondMask = RTC_ALARMSUBSECONDMASK_NONE;
    rtc_alarm_handle.AlarmDateWeekDaySel = RTC_ALARMDATEWEEKDAYSEL_WEEKDAY; /* ������ */
    rtc_alarm_handle.AlarmDateWeekDay = week;                               /* ���� */
    rtc_alarm_handle.Alarm = RTC_ALARM_A;                                   /* ����A */
    HAL_RTC_SetAlarm_IT(&g_rtc_handle, &rtc_alarm_handle, RTC_FORMAT_BIN);
    
    HAL_NVIC_SetPriority(RTC_Alarm_IRQn, 1, 2);   /* ��ռ���ȼ�1,�����ȼ�2 */
    HAL_NVIC_EnableIRQ(RTC_Alarm_IRQn);
}

void RTC_Alarm_IRQHandler(void)
{
    HAL_RTC_AlarmIRQHandler(&g_rtc_handle);
}

void HAL_RTC_AlarmAEventCallback(RTC_HandleTypeDef *hrtc)
{
    printf("ALARM A!\r\n");
    LED1_TOGGLE();
}

void rtc_set_wakeup(uint8_t wksel, uint16_t cnt)
{ 
    __HAL_RTC_WAKEUPTIMER_CLEAR_FLAG(&g_rtc_handle, RTC_FLAG_WUTF);  /* ���RTC WAKE UP�ı�־ */

    HAL_RTCEx_SetWakeUpTimer_IT(&g_rtc_handle, cnt, wksel);          /* ������װ��ֵ��ʱ�� */

    HAL_NVIC_SetPriority(RTC_WKUP_IRQn, 2, 2);                       /* ��ռ���ȼ�2, �����ȼ�2 */
    HAL_NVIC_EnableIRQ(RTC_WKUP_IRQn);
}

void RTC_WKUP_IRQHandler(void)
{
    HAL_RTCEx_WakeUpTimerIRQHandler(&g_rtc_handle); 
}

void HAL_RTCEx_WakeUpTimerEventCallback(RTC_HandleTypeDef *hrtc)
{
    LED1_TOGGLE();
}

