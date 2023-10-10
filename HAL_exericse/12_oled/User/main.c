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
#include "./BSP/TIMER/gtim.h"
#include "./BSP/OLED/oled.h"

int main(void)
{
    uint8_t t  = 0;
    
    HAL_Init();                             /* ��ʼ��HAL�� */
    sys_stm32_clock_init(336, 8, 2, 7);     /* ����ʱ��,168Mhz */
    delay_init(168);                        /* ��ʱ��ʼ�� */
    usart_init(115200);                     /* ���ڳ�ʼ��Ϊ115200 */
    led_init();                             /* ��ʼ��LED */
    oled_init();                            /* ��ʼ��OLED */

    oled_show_string(0, 0, "ALIENTEK", 24);
    oled_show_string(0, 24, "0.96' OLED TEST", 16);
    oled_show_string(0, 52, "ASCII:", 12);
    oled_show_string(64, 52, "CODE:", 12);
    oled_refresh_gram();                    /* ������ʾ��OLED */
    t = ' ';
    while(1)
    {
        oled_show_char(36, 52, t, 12, 1);   /* ��ʾASCII�ַ� */
        oled_show_num(94, 52, t, 3, 12);    /* ��ʾASCII�ַ�����ֵ */
        oled_refresh_gram();                /* ������ʾ��OLED */
        t++;

        if (t > '~')
        {
            t = ' ';
        }

        delay_ms(500);
        LED0_TOGGLE();                      /* LED0��˸ */
    }
}
