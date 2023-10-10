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

extern TIM_HandleTypeDef g_timx_pwm_chy_handler;
extern uint16_t g_timxchy_pwmin_psc;    /* PWM����״̬ */
extern uint16_t g_timxchy_pwmin_sta;    /* PWM����״̬ */
extern uint32_t g_timxchy_pwmin_hval;   /* PWM�ĸߵ�ƽ���� */
extern uint32_t g_timxchy_pwmin_cval;   /* PWM�����ڿ�� */

int main(void)
{
    uint8_t t = 0;
    double ht, ct, f, tpsc;
    
    HAL_Init();                                 /* ��ʼ��HAL�� */
    sys_stm32_clock_init(336,8,2,7);            /* ����ʱ�� 168MHz */
    delay_init(168);                            /* ��ʱ��ʼ�� */
    usart_init(115200);                         /* ���ڳ�ʼ��Ϊ115200 */
    led_init();                                 /* LED��ʼ�� */
    
    gtim_timx_pwm_chy_init(10 - 1, 84 - 1); /* 1Mhz�ļ���Ƶ��, 100Khz PWM */
    atim_timx_pwmin_chy_init();             /* ��ʼ��PWM���벶�� */

    GTIM_TIMX_PWM_CHY_CCRX = 2;             /* �͵�ƽ���20,�ߵ�ƽ���80 */
    
    while(1)
    {
        delay_ms(10);
        t++;

        if (t >= 20)    /* ÿ200ms���һ�ν��,����˸LED0,��ʾ�������� */
        {
            if (g_timxchy_pwmin_sta)                                /* ������һ������ */
            {
                printf("\r\n");                                     /* �����,����һ�� */
                printf("PWM PSC  :%d\r\n", g_timxchy_pwmin_psc);    /* ��ӡ��Ƶϵ�� */
                printf("PWM Hight:%d\r\n", g_timxchy_pwmin_hval);   /* ��ӡ�ߵ�ƽ���� */
                printf("PWM Cycle:%d\r\n", g_timxchy_pwmin_cval);   /* ��ӡ���� */
                tpsc = ((double)g_timxchy_pwmin_psc + 1) / 168;     /* �õ�PWM����ʱ������ʱ�� */
                ht = g_timxchy_pwmin_hval * tpsc;                   /* ����ߵ�ƽʱ�� */
                ct = g_timxchy_pwmin_cval * tpsc;                   /* �������ڳ��� */
                f = (1 / ct) * 1000000;                             /* ����Ƶ�� */
                printf("PWM Hight time:%.3fus\r\n", ht);            /* ��ӡ�ߵ�ƽ������ */
                printf("PWM Cycle time:%.3fus\r\n", ct);            /* ��ӡ����ʱ�䳤�� */
                printf("PWM Frequency :%.3fHz\r\n", f);             /* ��ӡƵ�� */
                atim_timx_pwmin_chy_restart();                      /* ����PWM������ */
            }

            LED1_TOGGLE();                                          /* DS1��˸ */
            t = 0;
        }
    }
}
