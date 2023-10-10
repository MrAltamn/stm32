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
    uint32_t curcnt = 0;
    uint32_t oldcnt = 0;
    uint8_t key = 0;
    uint8_t t = 0;
    
    HAL_Init();                      /* 初始化HAL库 */
    sys_stm32_clock_init(336,8,2,7); /* 设置时钟 168MHz */
    delay_init(168);                 /* 延时初始化 */
    usart_init(115200);              /* 串口初始化为115200 */
    led_init();                      /* LED初始化 */
    key_init();
    gtim_timx_cnt_chy_init(0);
    gtim_timx_cnt_chy_restart();

    while(1)
    {
        key = key_scan(0);
        if(key == KEY0_PRES)
        {
            printf("key0 press \r\n");
            gtim_timx_cnt_chy_restart();
        }
        
        curcnt = gtim_timx_cnt_chy_get_count();
        
        if(curcnt != oldcnt)
        {
            oldcnt = curcnt;
            printf("CNT: %d\r\n", curcnt);
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
