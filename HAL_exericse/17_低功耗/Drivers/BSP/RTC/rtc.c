#include "./BSP/RTC/rtc.h"
#include "./BSP/LED/led.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/BEEP/beep.h"

RTC_HandleTypeDef g_rtc_handle;

void rtc_write_bkr(uint32_t bkrx, uint32_t data)
{
    HAL_PWR_EnableBkUpAccess();     /* 取消备份区写保护 */
    HAL_RTCEx_BKUPWrite(&g_rtc_handle, bkrx, data);
}

uint32_t rtc_read_bkr(uint32_t bkrx)
{
    uint32_t temp = 0;
    temp = HAL_RTCEx_BKUPRead(&g_rtc_handle, bkrx);
    return temp; /* 返回读取到的值 */
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
    
    __HAL_RCC_PWR_CLK_ENABLE(); /* 使能电源时钟PWR */
    HAL_PWR_EnableBkUpAccess(); /* 取消备份区域写保护 */
    
    g_rtc_handle.Instance = RTC;
    g_rtc_handle.Init.SynchPrediv = 0xFF;               /* 同步分频系数 1~0x7F */
    g_rtc_handle.Init.AsynchPrediv = 0x7F;              /* 异步分频系数 1~0xFF */
    g_rtc_handle.Init.HourFormat = RTC_HOURFORMAT_24;   /* 24小时格式 */
    g_rtc_handle.Init.OutPut = RTC_OUTPUT_DISABLE;
    g_rtc_handle.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
    g_rtc_handle.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
    HAL_RTC_Init(&g_rtc_handle);
    
    /* 检查是不是第一次配置时钟 */
    bkpflag = rtc_read_bkr(0);                /* 读取BKP0的值 */
    
    if ((bkpflag != 0x5050))     /* 之前未初始化过, 重新配置 */
    {
        rtc_set_time(11, 42, 50, RTC_HOURFORMAT12_AM);   /* 设置时间, 根据实际时间修改 */
        rtc_set_date(23, 9, 27, 3);                     /* 设置日期 */
    }
    
    return 1;
}

void HAL_RTC_MspInit(RTC_HandleTypeDef* hrtc)
{
    RCC_OscInitTypeDef rcc_osc_init_handle;
    RCC_PeriphCLKInitTypeDef rcc_periphclk_init_handle;
    
    __HAL_RCC_RTC_ENABLE();     /* RTC使能 */
    
    /* 开启外部低速振荡器LSE */
    rcc_osc_init_handle.OscillatorType = RCC_OSCILLATORTYPE_LSE;        /* 选择要配置的振荡器 */
    rcc_osc_init_handle.PLL.PLLState = RCC_PLL_NONE;                    /* PLL不配置 */
    rcc_osc_init_handle.LSEState = RCC_LSE_ON;                          /* LSE状态:开启 */
    HAL_RCC_OscConfig(&rcc_osc_init_handle);
    
    rcc_periphclk_init_handle.PeriphClockSelection = RCC_PERIPHCLK_RTC; /* 选择要配置外设RTC */
    rcc_periphclk_init_handle.RTCClockSelection = RCC_RTCCLKSOURCE_LSE; /* RTC时钟源选择LSE */
    HAL_RCCEx_PeriphCLKConfig(&rcc_periphclk_init_handle);              /* 配置设置的rcc_periphclkinitstruct */
    rtc_write_bkr(0, 0x5050);
}

void rtc_set_alarma(uint8_t week, uint8_t hour, uint8_t min, uint8_t sec)
{
    RTC_AlarmTypeDef rtc_alarm_handle;
    
    rtc_alarm_handle.AlarmTime.Hours = hour;                                /* 小时 */
    rtc_alarm_handle.AlarmTime.Minutes = min;                               /* 分钟 */
    rtc_alarm_handle.AlarmTime.Seconds = sec;                               /* 秒 */
    rtc_alarm_handle.AlarmTime.SubSeconds = 0;
    rtc_alarm_handle.AlarmTime.TimeFormat = RTC_HOURFORMAT12_AM;
    
    rtc_alarm_handle.AlarmMask = RTC_ALARMMASK_NONE;
    rtc_alarm_handle.AlarmSubSecondMask = RTC_ALARMSUBSECONDMASK_NONE;
    rtc_alarm_handle.AlarmDateWeekDaySel = RTC_ALARMDATEWEEKDAYSEL_WEEKDAY; /* 按星期 */
    rtc_alarm_handle.AlarmDateWeekDay = week;                               /* 星期 */
    rtc_alarm_handle.Alarm = RTC_ALARM_A;                                   /* 闹钟A */
    HAL_RTC_SetAlarm_IT(&g_rtc_handle, &rtc_alarm_handle, RTC_FORMAT_BIN);
    
    HAL_NVIC_SetPriority(RTC_Alarm_IRQn, 1, 2);   /* 抢占优先级1,子优先级2 */
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
    __HAL_RTC_WAKEUPTIMER_CLEAR_FLAG(&g_rtc_handle, RTC_FLAG_WUTF);  /* 清除RTC WAKE UP的标志 */

    HAL_RTCEx_SetWakeUpTimer_IT(&g_rtc_handle, cnt, wksel);          /* 设置重装载值和时钟 */

    HAL_NVIC_SetPriority(RTC_WKUP_IRQn, 2, 2);                       /* 抢占优先级2, 子优先级2 */
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

