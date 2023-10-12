/**
 ****************************************************************************************************
 * @file        main.c
 * @author      正点原子团队(ALIENTEK)
 * @version     V1.0
 * @date        2021-10-16
 * @brief       TFTLCD 实验
 * @license     Copyright (c) 2020-2032, 广州市星翼电子科技有限公司
 ****************************************************************************************************
 * @attention
 *
 * 实验平台:正点原子 探索者 F407开发板
 * 在线视频:www.yuanzige.com
 * 技术论坛:www.openedv.com
 * 公司网址:www.alientek.com
 * 购买地址:openedv.taobao.com
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
    
    HAL_Init();                             /* 初始化HAL库 */
    sys_stm32_clock_init(336, 8, 2, 7);     /* 设置时钟,168Mhz */
    delay_init(168);                        /* 延时初始化 */
    usart_init(115200);                     /* 串口初始化为115200 */
    led_init();                             /* 初始化LED */
    lcd_init();                             /* 初始化LCD */
    adc_init();                             /* 初始化ADC */
    pwmdac_init(256 - 1, 0);                /* PWM DAC初始化, Fpwm = 84 / 256 =328.125Khz */

    lcd_show_string(30,  50, 200, 16, 16, "STM32", RED);
    lcd_show_string(30,  70, 200, 16, 16, "PWM DAC TEST", RED);
    lcd_show_string(30,  90, 200, 16, 16, "ATOM@ALIENTEK", RED);
    lcd_show_string(30, 110, 200, 16, 16, "ADC VOL:0.000V", BLUE);
    
    pwmdac_set_voltage(2400);
    
    while (1)
    {
        adcx = adc_get_result_average(ADC_ADCX_CHY, 10);    /* 得到ADC1通道5的转换结果 */
        temp = (float)adcx * (3.3 / 4096);                  /* 得到ADC电压值(adc是12bit的) */
        adcx = temp;
        lcd_show_xnum(94, 110, temp, 1, 16, 0, BLUE);       /* 显示电压值整数部分 */

        temp -= adcx;
        temp *= 1000;
        lcd_show_xnum(110, 110, temp, 3, 16, 0X80, BLUE);   /* 显示电压值的小数部分 */

        LED0_TOGGLE();  /* LED0闪烁 */
        
        delay_ms(50);
    }
}

    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
