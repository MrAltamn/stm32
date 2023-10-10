#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/LED/led.h"
#include "./BSP/BEEP/beep.h"
#include "./BSP/KEY/key.h"
#include "./BSP/EXTI/exti.h"
#include "./BSP/IWDG/iwdg.h"
#include "./BSP/WWDG/wwdg.h"
#include "./BSP/BTIM/btim.h"
#include "./BSP/TIMER/gtim.h"

extern uint8_t  g_timxchy_cap_sta;              /* 输入捕获状态 */
extern uint16_t g_timxchy_cap_val;              /* 输入捕获值 */

int main(void)
{
    uint32_t temp = 0; 
    uint8_t t = 0;
    
    HAL_Init();                      /* 初始化HAL库 */
    sys_stm32_clock_init(336,8,2,7); /* 设置时钟 168MHz */
    delay_init(168);                    /* 延时初始化 */
    usart_init(115200);                     /* 串口初始化为115200 */
    led_init();                      /* LED初始化 */
    key_init();
    gtim_timx_cap_chy_init(0xFFFF,84-1);

    while(1)
    {
        if(g_timxchy_cap_sta & 0x80)
        {
            temp = g_timxchy_cap_sta & 0x3F;
            temp *= 0xFFFF;                     /* 溢出时间总和 */
            temp += g_timxchy_cap_val;          /* 得到总的高电平时间 */
            printf("HIGH:%d us\r\n", temp);     /* 打印总的高电平时间 */
            g_timxchy_cap_sta = 0;              /* 开启下一次捕获 */
        }
        t++;
        if(t > 20)
        {
            t = 0;
            LED0_TOGGLE();
        }
        delay_ms(10);
    }
}
