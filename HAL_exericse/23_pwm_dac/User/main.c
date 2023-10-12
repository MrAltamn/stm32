/**
 ****************************************************************************************************
 * @file        main.c
 * @author      ����ԭ���Ŷ�(ALIENTEK)
 * @version     V1.0
 * @date        2021-10-16
 * @brief       TFTLCD ʵ��
 * @license     Copyright (c) 2020-2032, ������������ӿƼ����޹�˾
 ****************************************************************************************************
 * @attention
 *
 * ʵ��ƽ̨:����ԭ�� ̽���� F407������
 * ������Ƶ:www.yuanzige.com
 * ������̳:www.openedv.com
 * ��˾��ַ:www.alientek.com
 * �����ַ:openedv.taobao.com
 *
 ****************************************************************************************************
 */

#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/LED/led.h"
#include "./BSP/LCD/lcd.h"
#include "./BSP/ADC/adc.h"
#include "./BSP/DAC/dac.h"
#include "./BSP/PWMDAC/pwmdac.h"

extern TIM_HandleTypeDef g_timx_handler;

int main(void)
{
    uint16_t adcx;
    float temp;
    
    HAL_Init();                             /* ��ʼ��HAL�� */
    sys_stm32_clock_init(336, 8, 2, 7);     /* ����ʱ��,168Mhz */
    delay_init(168);                        /* ��ʱ��ʼ�� */
    usart_init(115200);                     /* ���ڳ�ʼ��Ϊ115200 */
    led_init();                             /* ��ʼ��LED */
    lcd_init();                             /* ��ʼ��LCD */
    adc_init();                             /* ��ʼ��ADC */
    pwmdac_init(256 - 1, 0);                /* PWM DAC��ʼ��, Fpwm = 84 / 256 =328.125Khz */

    lcd_show_string(30,  50, 200, 16, 16, "STM32", RED);
    lcd_show_string(30,  70, 200, 16, 16, "PWM DAC TEST", RED);
    lcd_show_string(30,  90, 200, 16, 16, "ATOM@ALIENTEK", RED);
    lcd_show_string(30, 110, 200, 16, 16, "ADC VOL:0.000V", BLUE);
    
    pwmdac_set_voltage(2400);
    
    while (1)
    {
        adcx = adc_get_result_average(ADC_ADCX_CHY, 10);    /* �õ�ADC1ͨ��5��ת����� */
        temp = (float)adcx * (3.3 / 4096);                  /* �õ�ADC��ѹֵ(adc��12bit��) */
        adcx = temp;
        lcd_show_xnum(94, 110, temp, 1, 16, 0, BLUE);       /* ��ʾ��ѹֵ�������� */

        temp -= adcx;
        temp *= 1000;
        lcd_show_xnum(110, 110, temp, 3, 16, 0X80, BLUE);   /* ��ʾ��ѹֵ��С������ */

        LED0_TOGGLE();  /* LED0��˸ */
        
        delay_ms(50);
    }
}

    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
