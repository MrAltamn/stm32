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

extern TIM_HandleTypeDef g_timx_pwm_chy_handler;
int main(void)
{
    uint16_t ledrpwmval = 0;
    uint8_t dir = 1;
    
    HAL_Init();                      /* ��ʼ��HAL�� */
    sys_stm32_clock_init(336,8,2,7); /* ����ʱ�� 168MHz */
    delay_init(168);                    /* ��ʱ��ʼ�� */
    usart_init(115200);                     /* ���ڳ�ʼ��Ϊ115200 */
    led_init();                      /* LED��ʼ�� */

    gtim_timx_pwm_chy_init(500-1,84-1);

    while(1)
    {
        delay_ms(10);

        if(dir) 
        {
            ledrpwmval++;
        }else{
            ledrpwmval--;
        }
        if(ledrpwmval > 300)
        {
            dir = 0;
        }
        if(ledrpwmval == 0)
        {
            dir = 1;
        }
        
        __HAL_TIM_SET_COMPARE(&g_timx_pwm_chy_handler, GTIM_TIMX_PWM_CHY, ledrpwmval);
    }
}
