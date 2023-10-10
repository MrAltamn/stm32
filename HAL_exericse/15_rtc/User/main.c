#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/LED/led.h"
#include "./USMART/usmart.h"
#include "./BSP/LCD/lcd.h"
#include "./BSP/RTC/rtc.h"

void led_set(uint8_t sta)
{
    LED1(sta);
}

void test_fun(void(*ledset)(uint8_t), uint8_t sta)
{
    ledset(sta);
}

int main(void)
{
    uint8_t hour, min, sec, ampm;
    uint8_t year, month, date, week;
    uint8_t tbuf[40];
    uint8_t t = 0;
    
    HAL_Init();                             /* 初始化HAL库 */
    sys_stm32_clock_init(336, 8, 2, 7);     /* 设置时钟,168Mhz */
    delay_init(168);                        /* 延时初始化 */
    usart_init(115200);                     /* 串口初始化为115200 */
    usmart_dev.init(84);                    /* 初始化USMART */
    led_init();                             /* 初始化LED */
    lcd_init();                             /* 初始化LCD */
    rtc_init();                             /* 初始化RTC */
    rtc_set_wakeup(RTC_WAKEUPCLOCK_CK_SPRE_16BITS, 0);  /* 配置WAKE UP中断,1秒钟中断一次 */
    
    lcd_show_string(30, 50, 200, 16, 16, "STM32", RED);
    lcd_show_string(30, 70, 200, 16, 16, "RTC TEST", RED);
    lcd_show_string(30, 90, 200, 16, 16, "ATOM@ALIENTEK", RED);

    while (1)
    {
        t++;

        if ((t % 10) == 0)  /* 每100ms更新一次显示数据 */
        {
            rtc_get_time(&hour, &min, &sec, &ampm);
            sprintf((char *)tbuf, "Time:%02d:%02d:%02d", hour, min, sec);
            lcd_show_string(30, 130, 210, 16, 16, (char*)tbuf, RED);
            rtc_get_date(&year, &month, &date, &week);
            sprintf((char *)tbuf, "Date:20%02d-%02d-%02d", year, month, date);
            lcd_show_string(30, 150, 210, 16, 16, (char*)tbuf, RED);
            sprintf((char *)tbuf, "Week:%d", week);
            lcd_show_string(30, 170, 210, 16, 16, (char*)tbuf, RED);
        }

        if ((t % 20) == 0)
        {
            LED0_TOGGLE();  /* 每200ms,翻转一次LED0 */
        }

        delay_ms(10);
    }
}
