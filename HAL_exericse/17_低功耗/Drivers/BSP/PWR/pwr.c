#include "./BSP/PWR/pwr.h"
#include "./BSP/LED/led.h"
#include "./BSP/LCD/lcd.h"
#include "./BSP/RTC/rtc.h"
#include "./BSP/BEEP/beep.h"
#include "./SYSTEM/sys/sys.h"
void pwr_pvd_init(void)
{
    PWR_PVDTypeDef pvd_init_struct;
    
    __HAL_RCC_PWR_CLK_ENABLE();                                     /* ʹ�ܵ�Դʱ�� */
    
    pvd_init_struct.PVDLevel = PWR_PVDLEVEL_7;
    pvd_init_struct.Mode = PWR_PVD_MODE_IT_RISING_FALLING;
    HAL_PWR_ConfigPVD(&pvd_init_struct);                        /* ����PVD */
        
    HAL_PWR_EnablePVD();                                            /* ʹ��PVD��� */
    
    HAL_NVIC_SetPriority(PVD_IRQn, 2, 2);            /* ��ռ���ȼ�2�������ȼ�2 */
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
        lcd_show_string(30, 130, 200, 16, 16, "PVD Voltage OK! ", BLUE);/* LCD��ʾ��ѹ���� */
        LED1(1);    /* ����̵� */
    }
}



/* ��ʼ��WKUP����Ϊ�жϴ���Դ */
void pwr_wkup_key_init(void)
{
    GPIO_InitTypeDef gpio_init_struct;
    
    PWR_WKUP_GPIO_CLK_ENABLE();     /* WKUPʱ��ʹ�� */
    
    gpio_init_struct.Pin = PWR_WKUP_GPIO_PIN;
    gpio_init_struct.Mode = GPIO_MODE_IT_RISING;
    gpio_init_struct.Pull = GPIO_PULLDOWN;
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(PWR_WKUP_GPIO_PORT, &gpio_init_struct);     /* WK_UP���ų�ʼ�� */
    
    HAL_NVIC_SetPriority(PWR_WKUP_INT_IRQn, 2, 2);            /* ��ռ���ȼ�2�������ȼ�2 */
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
        /* HAL_GPIO_EXTI_IRQHandler()�����Ѿ�Ϊ����������жϱ�־λ���������ǽ��˻ص��������Բ����κ��� */
        BEEP_TOGGLE();
    }
}

/* ����˯��ģʽ */
void pwr_enter_sleep(void)
{
    HAL_SuspendTick();  /* ��ͣ�δ�ʱ�ӣ���ֹͨ���δ�ʱ���жϻ��� */
    
    HAL_PWR_EnterSLEEPMode(PWR_MAINREGULATOR_ON, PWR_SLEEPENTRY_WFI); /* ִ��WFIָ��, �������ģʽ */
}
    
/* ����ֹͣģʽ */
void pwr_enter_stop(void)
{
    __HAL_RCC_PWR_CLK_ENABLE();
    HAL_SuspendTick();  /* ��ͣ�δ�ʱ�ӣ���ֹͨ���δ�ʱ���жϻ��� */
    HAL_PWR_EnterSTOPMode(PWR_LOWPOWERREGULATOR_ON, PWR_SLEEPENTRY_WFI);
}

/* �������ģʽ */
void pwr_enter_standby(void)
{
    __HAL_RCC_PWR_CLK_ENABLE();         /* ʹ��PWRʱ�� */
    __HAL_RCC_BACKUPRESET_FORCE();      /* ��λ�������� */
    HAL_PWR_EnableBkUpAccess();         /* ���������ʹ�� */
    
    __HAL_PWR_CLEAR_FLAG(PWR_FLAG_WU);                  /* ���Wake_UP��־ */
    
    HAL_PWR_EnableWakeUpPin(PWR_WAKEUP_PIN1);           /* ����WKUP���ڻ��� */
    HAL_PWR_EnterSTANDBYMode();                         /* �������ģʽ */
    
}
