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
#include "./BSP/TIMER/atim.h"

extern TIM_HandleTypeDef g_timx_pwm_chy_handler;
int main(void)
{
    uint8_t t = 0;
    
    HAL_Init();                      /* 初始化HAL库 */
    sys_stm32_clock_init(336,8,2,7); /* 设置时钟 168MHz */
    delay_init(168);                 /* 延时初始化 */
    usart_init(115200);              /* 串口初始化为115200 */
    led_init();                      /* LED初始化 */
    atim_timx_comp_pwm_init(1000 - 1, 168 - 1); /* 1Mhz的计数频率 1Khz的周期. */ 
    ATIM_TIMX_COMP_CH1_CCRX = 250 - 1; /* 通道1 相位25% */ 
    ATIM_TIMX_COMP_CH2_CCRX = 500 - 1; /* 通道2 相位50% */ 
    ATIM_TIMX_COMP_CH3_CCRX = 750 - 1; /* 通道3 相位75% */ 
    ATIM_TIMX_COMP_CH4_CCRX = 999 - 1; /* 通道4 相位99% */
    
    while(1)
    {
        t++;
        delay_ms(10);

        if (t >= 20)                     /* 控制LED0闪烁, 提示程序运行状态 */
        {
            t = 0;
            LED0_TOGGLE();
        }
    }
}
