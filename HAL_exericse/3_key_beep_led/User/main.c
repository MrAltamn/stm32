#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/LED/led.h"
#include "./BSP/BEEP/beep.h"
#include "./BSP/KEY/key.h"


int main(void)
{
    uint8_t key;
    HAL_Init();                      /* 初始化HAL库 */
    sys_stm32_clock_init(336,8,2,7); /* 设置时钟 168MHz */
    delay_init(168);                    /* 延时初始化 */
    led_init();                      /* LED初始化 */
    beep_init();                     /* BEEP初始化 */
    key_init();                      /* KEY初始化 */
    
    while(1)
    {
        key = key_scan(0);
        if(key)
        {
            switch(key)
            {
                case KEY0_PRES:
                    LED0_TOGGLE();
                    break;
                case KEY1_PRES:
                    LED1_TOGGLE();
                    break;
                case KEY2_PRES:
                    LED0_TOGGLE();
                    LED1_TOGGLE();
                    break;
                case KEY_UP_PRES:
                    BEEP_TOGGLE();
                    break;
                default :
                    delay_ms(10);
                    break;
            }
        }
        else
        {
            delay_ms(10);
        }
    }
}
