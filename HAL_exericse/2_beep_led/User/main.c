#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/LED/led.h"
#include "./BSP/BEEP/beep.h"

int main(void)
{
    HAL_Init();                      /* 初始化HAL库 */
    sys_stm32_clock_init(336,8,2,7); /* 设置时钟 168MHz */
    delay_init(168);                    /* 延时初始化 */
    led_init();                      /* LED初始化 */
    beep_init();                     /* BEEP初始化 */
    while(1)
    {
        LED0(0);
        BEEP(0);
        delay_ms(500);
        LED0(1);
        BEEP(1);
        delay_ms(500);
    }
}
