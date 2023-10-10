#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/LED/led.h"

int main(void)
{
    HAL_Init();                      /* ��ʼ��HAL�� */
    sys_stm32_clock_init(336,8,2,7); /* ����ʱ�� 168MHz */
    delay_init(168);                    /* ��ʱ��ʼ�� */
    led_init();                      /* LED��ʼ�� */
    
    while(1)
    {
        LED0(0);
        LED1(1);
        delay_ms(500);
        LED0(1);
        LED1(0);
        delay_ms(500);
    }
}
