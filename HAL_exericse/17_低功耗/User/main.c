#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/LED/led.h"
#include "./USMART/usmart.h"
#include "./BSP/LCD/lcd.h"
#include "./BSP/RTC/rtc.h"
#include "./BSP/RNG/rng.h"
#include "./BSP/BEEP/beep.h"
#include "./BSP/KEY/key.h"
#include "./BSP/PWR/pwr.h"

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
    uint8_t t = 0;
    uint8_t key; 
    
    HAL_Init();                             /* 初始化HAL库 */
    sys_stm32_clock_init(336, 8, 2, 7);     /* 设置时钟,168Mhz */
    delay_init(168);                        /* 延时初始化 */
    usart_init(115200);                     /* 串口初始化为115200 */
    led_init();                             /* 初始化LED */
    lcd_init();                             /* 初始化LCD */
    key_init();                             /* 初始化按键 */
    pwr_pvd_init();
    pwr_wkup_key_init();                    /* 唤醒按键初始化 */
    
    lcd_show_string(30, 50, 200, 16, 16, "STM32", RED);
    lcd_show_string(30, 70, 200, 16, 16, "RTC TEST", RED);
    lcd_show_string(30, 90, 200, 16, 16, "ATOM@ALIENTEK", RED);
    lcd_show_string(30, 110, 200, 16, 16, "KEY0:Enter SLEEP MODE", RED);
    lcd_show_string(30, 130, 200, 16, 16, "KEY_UP:Exit SLEEP MODE", RED);
    
    while (1)
    {
        t++;
        key = key_scan(0);
        if(key)
        {
            switch(key)
            {
                case KEY0_PRES:
                    LED1(0);
                    printf("enter sleep mode!\r\n");
                    pwr_enter_sleep();  /* 进入睡眠模式 */
                    HAL_ResumeTick();   /* 恢复滴答时钟 */
                    printf("exit sleep mode!\r\n");
                    LED1(1);
                    break;
                case KEY1_PRES:
                    LED1(0);
                    printf("enter stop mode!\r\n");
                    pwr_enter_stop();  /* 进入睡眠模式 */
                    sys_stm32_clock_init(336, 8, 2, 7);
                    HAL_ResumeTick();   /* 恢复滴答时钟 */
                    printf("exit stop mode!\r\n");
                    LED1(1);
                    break;
                case KEY2_PRES:
                    LED1(0);
                    printf("enter stop mode!\r\n");
                    pwr_enter_standby();  /* 进入睡眠模式 */
                    printf("exit stop mode!\r\n");
                    LED1(1);
                    break;
            }
        }

        if ((t % 20) == 0)
        {
            LED0_TOGGLE();  /* 每200ms,翻转一次LED0 */
        }

        delay_ms(10);
    }
}
