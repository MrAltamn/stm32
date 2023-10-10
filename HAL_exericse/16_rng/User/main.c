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
    uint32_t randomnum;
    uint32_t randomnum_range;
    uint8_t key; 
    
    HAL_Init();                             /* 初始化HAL库 */
    sys_stm32_clock_init(336, 8, 2, 7);     /* 设置时钟,168Mhz */
    delay_init(168);                        /* 延时初始化 */
    usart_init(115200);                     /* 串口初始化为115200 */
    usmart_dev.init(84);                    /* 初始化USMART */
    led_init();                             /* 初始化LED */
    lcd_init();                             /* 初始化LCD */
    rtc_init();                             /* 初始化RTC */
    rng_init();
    
    lcd_show_string(30, 50, 200, 16, 16, "STM32", RED);
    lcd_show_string(30, 70, 200, 16, 16, "RTC TEST", RED);
    lcd_show_string(30, 90, 200, 16, 16, "ATOM@ALIENTEK", RED);

    lcd_show_string(30, 110, 200, 16, 16, "RNG Ready!   ", RED);
    lcd_show_string(30, 130, 200, 16, 16, "KEY0:Get Random Num", RED);
    lcd_show_string(30, 150, 200, 16, 16, "Random Num:", RED);
    lcd_show_string(30, 180, 200, 16, 16, "Random Num[10-50]:", RED);
    
    while (1)
    {
        t++;
        key = key_scan(0);
        if(key)
        {
            switch(key)
            {
                case KEY0_PRES:
                    LED1_TOGGLE();
                    randomnum = rng_get_random_num();
                    lcd_show_num(30 + 8 * 11, 150, randomnum, 10, 16, BLUE);
                    break;
                case KEY1_PRES:
                    LED1_TOGGLE();
                    randomnum_range = rng_get_random_num_range(10, 50);
                    lcd_show_num(30 + 8 * 18, 180, randomnum_range, 2, 16, BLUE);/* 显示随机数 */
                    break;
                default :
                    delay_ms(10);
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
