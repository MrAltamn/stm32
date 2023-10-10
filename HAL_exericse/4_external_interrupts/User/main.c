#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/LED/led.h"
#include "./BSP/BEEP/beep.h"
#include "./BSP/KEY/key.h"
#include "./BSP/EXTI/exti.h"

int main(void)
{
    HAL_Init();                      /* ��ʼ��HAL�� */
    sys_stm32_clock_init(336,8,2,7); /* ����ʱ�� 168MHz */
    delay_init(168);                    /* ��ʱ��ʼ�� */
    //usart_init(115200);                     /* ���ڳ�ʼ��Ϊ115200 */
    led_init();                      /* LED��ʼ�� */
    beep_init();                     /* BEEP��ʼ�� */
    key_init();                      /* KEY��ʼ�� */
    exti_init();                     /* �ⲿ�жϳ�ʼ�� */
    //LED0(0); 
    
    while(1)
    {
        delay_ms(1000);
    }
}
