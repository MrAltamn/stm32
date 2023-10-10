#include "./BSP/PWR/pwr.h"
#include "./BSP/LED/led.h"
#include "./BSP/LCD/lcd.h"
#include "./BSP/RTC/rtc.h"
#include "./BSP/BEEP/beep.h"
#include "./SYSTEM/sys/sys.h"
void pwr_pvd_init(void)
{
    PWR_PVDTypeDef pvd_init_struct;
    
    __HAL_RCC_PWR_CLK_ENABLE();                                     /* 使能电源时钟 */
    
    pvd_init_struct.PVDLevel = PWR_PVDLEVEL_7;
    pvd_init_struct.Mode = PWR_PVD_MODE_IT_RISING_FALLING;
    HAL_PWR_ConfigPVD(&pvd_init_struct);                        /* 配置PVD */
        
    HAL_PWR_EnablePVD();                                            /* 使能PVD监测 */
    
    HAL_NVIC_SetPriority(PVD_IRQn, 2, 2);            /* 抢占优先级2，子优先级2 */
    HAL_NVIC_EnableIRQ(PVD_IRQn); 
}

void PVD_IRQHandler(void)
{
    HAL_PWR_PVD_IRQHandler();
}

void HAL_PWR_PVDCallback(void)
{
    if(__HAL_PWR_GET_FLAG(PWR_FLAG_PVDO))
    {
        LED1(0);
        lcd_show_string(30, 130, 200, 16, 16, "PVD Low Voltage!", RED);
    }
    else{
        lcd_show_string(30, 130, 200, 16, 16, "PVD Voltage OK! ", BLUE);/* LCD显示电压正常 */
        LED1(1);    /* 灭掉绿灯 */
    }
}



/* 初始化WKUP引脚为中断触发源 */
void pwr_wkup_key_init(void)
{
    GPIO_InitTypeDef gpio_init_struct;
    
    PWR_WKUP_GPIO_CLK_ENABLE();     /* WKUP时钟使能 */
    
    gpio_init_struct.Pin = PWR_WKUP_GPIO_PIN;
    gpio_init_struct.Mode = GPIO_MODE_IT_RISING;
    gpio_init_struct.Pull = GPIO_PULLDOWN;
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(PWR_WKUP_GPIO_PORT, &gpio_init_struct);     /* WK_UP引脚初始化 */
    
    HAL_NVIC_SetPriority(PWR_WKUP_INT_IRQn, 2, 2);            /* 抢占优先级2，子优先级2 */
    HAL_NVIC_EnableIRQ(PWR_WKUP_INT_IRQn); 
}

void PWR_WKUP_INT_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(PWR_WKUP_GPIO_PIN);
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if (GPIO_Pin == PWR_WKUP_GPIO_PIN)
    {
        /* HAL_GPIO_EXTI_IRQHandler()函数已经为我们清除了中断标志位，所以我们进了回调函数可以不做任何事 */
        BEEP_TOGGLE();
    }
}

/* 进入睡眠模式 */
void pwr_enter_sleep(void)
{
    HAL_SuspendTick();  /* 暂停滴答时钟，防止通过滴答时钟中断唤醒 */
    
    HAL_PWR_EnterSLEEPMode(PWR_MAINREGULATOR_ON, PWR_SLEEPENTRY_WFI); /* 执行WFI指令, 进入待机模式 */
}
    
/* 进入停止模式 */
void pwr_enter_stop(void)
{
    __HAL_RCC_PWR_CLK_ENABLE();
    HAL_SuspendTick();  /* 暂停滴答时钟，防止通过滴答时钟中断唤醒 */
    HAL_PWR_EnterSTOPMode(PWR_LOWPOWERREGULATOR_ON, PWR_SLEEPENTRY_WFI);
}

/* 进入待机模式 */
void pwr_enter_standby(void)
{
    __HAL_RCC_PWR_CLK_ENABLE();         /* 使能PWR时钟 */
    __HAL_RCC_BACKUPRESET_FORCE();      /* 复位备份区域 */
    HAL_PWR_EnableBkUpAccess();         /* 后备区域访问使能 */
    
    __HAL_PWR_CLEAR_FLAG(PWR_FLAG_WU);                  /* 清除Wake_UP标志 */
    
    HAL_PWR_EnableWakeUpPin(PWR_WAKEUP_PIN1);           /* 设置WKUP用于唤醒 */
    HAL_PWR_EnterSTANDBYMode();                         /* 进入待机模式 */
    
}
