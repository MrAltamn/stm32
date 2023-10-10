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
    uint8_t key = 0;
    uint8_t t = 0;
    GPIO_InitTypeDef gpio_init_struct;
    
    HAL_Init();                      /* 初始化HAL库 */
    sys_stm32_clock_init(336,8,2,7); /* 设置时钟 168MHz */
    delay_init(168);                    /* 延时初始化 */
    usart_init(115200);                     /* 串口初始化为115200 */
    led_init();                      /* LED初始化 */
    key_init();
    
    gpio_init_struct.Pin = LED1_GPIO_PIN;
    gpio_init_struct.Pull= GPIO_PULLUP;
    gpio_init_struct.Mode = GPIO_MODE_INPUT;
    gpio_init_struct.Speed= GPIO_SPEED_FREQ_VERY_HIGH;
    HAL_GPIO_Init(LED1_GPIO_PORT, &gpio_init_struct);
    
    atim_timx_npwm_chy_init(10000-1,8400-1);
    ATIM_TIMX_NPWM_CHY_CCRX = 5000;
    
    atim_timx_npwm_chy_set(5);
    
    while(1)
    {
        key = key_scan(0);

        if (key == KEY0_PRES)           /* KEY0按下 */
        {
            atim_timx_npwm_chy_set(5);  /* 输出5个PWM波(控制TIM8_CH1, 即PC6输出5个脉冲) */
        }

        t++;
        delay_ms(10);

        if (t > 50)                     /* 控制LED0闪烁, 提示程序运行状态 */
        {
            t = 0;
            LED0_TOGGLE();
        }
    }
}
