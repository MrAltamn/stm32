#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/LED/led.h"
#include "./BSP/BEEP/beep.h"

int main(void)
{
    HAL_Init();                      /* ��ʼ��HAL�� */
    sys_stm32_clock_init(336,8,2,7); /* ����ʱ�� 168MHz */
    delay_init(168);                    /* ��ʱ��ʼ�� */
    led_init();                      /* LED��ʼ�� */
    beep_init();                     /* BEEP��ʼ�� */
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
