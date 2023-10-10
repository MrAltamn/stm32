#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/LED/led.h"
#include "./BSP/BEEP/beep.h"
#include "./BSP/KEY/key.h"


int main(void)
{
    uint8_t key;
    HAL_Init();                      /* ��ʼ��HAL�� */
    sys_stm32_clock_init(336,8,2,7); /* ����ʱ�� 168MHz */
    delay_init(168);                    /* ��ʱ��ʼ�� */
    led_init();                      /* LED��ʼ�� */
    beep_init();                     /* BEEP��ʼ�� */
    key_init();                      /* KEY��ʼ�� */
    
    while(1)
    {
        key = key_scan(0);
        if(key)
        {
            switch(key)
            {
                case KEY0_PRES:
                    LED0_TOGGLE();
                    break;
                case KEY1_PRES:
                    LED1_TOGGLE();
                    break;
                case KEY2_PRES:
                    LED0_TOGGLE();
                    LED1_TOGGLE();
                    break;
                case KEY_UP_PRES:
                    BEEP_TOGGLE();
                    break;
                default :
                    delay_ms(10);
                    break;
            }
        }
        else
        {
            delay_ms(10);
        }
    }
}
