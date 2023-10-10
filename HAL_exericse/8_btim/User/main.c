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


int main(void)
{
    HAL_Init();                      /* ��ʼ��HAL�� */
    sys_stm32_clock_init(336,8,2,7); /* ����ʱ�� 168MHz */
    delay_init(168);                    /* ��ʱ��ʼ�� */
    usart_init(115200);                     /* ���ڳ�ʼ��Ϊ115200 */
    led_init();                      /* LED��ʼ�� */
    beep_init();                     /* BEEP��ʼ�� */
    //key_init();                      /* KEY��ʼ�� */
    //LED0(0);
    //delay_ms(300);
    //exti_init();                     /* �ⲿ�жϳ�ʼ�� */
    //wwdg_init(0x7F, 0x5F, WWDG_PRESCALER_8);                     /* WWDG�������Ź���ʼ�� */
    
    btim_tim6_init(5000-1, 8400-1);
    //btim_tim7_init(8000-1, 8400-1);
    while(1)
    {
        LED0_TOGGLE();
        delay_ms(200);
    }
}
