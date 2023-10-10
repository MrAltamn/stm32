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
    HAL_Init();                      /* ��ʼ��HAL�� */
    sys_stm32_clock_init(336,8,2,7); /* ����ʱ�� 168MHz */
    delay_init(168);                    /* ��ʱ��ʼ�� */
    usart_init(115200);                     /* ���ڳ�ʼ��Ϊ115200 */
    led_init();                      /* LED��ʼ�� */
    //beep_init();                     /* BEEP��ʼ�� */
    key_init();                      /* KEY��ʼ�� */
    delay_ms(100);
    //exti_init();                     /* �ⲿ�жϳ�ʼ�� */
    iwdg_init(IWDG_PRESCALER_64, 500);                     /* IWDG�������Ź���ʼ�� */
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
