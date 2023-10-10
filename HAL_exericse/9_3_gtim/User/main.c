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

extern uint8_t  g_timxchy_cap_sta;              /* ���벶��״̬ */
extern uint16_t g_timxchy_cap_val;              /* ���벶��ֵ */

int main(void)
{
    uint32_t temp = 0; 
    uint8_t t = 0;
    
    HAL_Init();                      /* ��ʼ��HAL�� */
    sys_stm32_clock_init(336,8,2,7); /* ����ʱ�� 168MHz */
    delay_init(168);                    /* ��ʱ��ʼ�� */
    usart_init(115200);                     /* ���ڳ�ʼ��Ϊ115200 */
    led_init();                      /* LED��ʼ�� */
    key_init();
    gtim_timx_cap_chy_init(0xFFFF,84-1);

    while(1)
    {
        if(g_timxchy_cap_sta & 0x80)
        {
            temp = g_timxchy_cap_sta & 0x3F;
            temp *= 0xFFFF;                     /* ���ʱ���ܺ� */
            temp += g_timxchy_cap_val;          /* �õ��ܵĸߵ�ƽʱ�� */
            printf("HIGH:%d us\r\n", temp);     /* ��ӡ�ܵĸߵ�ƽʱ�� */
            g_timxchy_cap_sta = 0;              /* ������һ�β��� */
        }
        t++;
        if(t > 20)
        {
            t = 0;
            LED0_TOGGLE();
        }
        delay_ms(10);
    }
}
