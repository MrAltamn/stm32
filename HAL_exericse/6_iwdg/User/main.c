#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/LED/led.h"
#include "./BSP/BEEP/beep.h"
#include "./BSP/KEY/key.h"
#include "./BSP/EXTI/exti.h"
#include "./BSP/IWDG/iwdg.h"

int main(void)
{
    HAL_Init();                      /* 初始化HAL库 */
    sys_stm32_clock_init(336,8,2,7); /* 设置时钟 168MHz */
    delay_init(168);                    /* 延时初始化 */
    usart_init(115200);                     /* 串口初始化为115200 */
    led_init();                      /* LED初始化 */
    //beep_init();                     /* BEEP初始化 */
    key_init();                      /* KEY初始化 */
    delay_ms(100);
    //exti_init();                     /* 外部中断初始化 */
    iwdg_init(IWDG_PRESCALER_64, 500);                     /* IWDG独立看门狗初始化 */
    LED0(0); 
    
    while(1)
    {
        if(key_scan(1) == KEY_UP_PRES)
        {
            iwdg_feed();
        }
        delay_ms(10);
    }
}
