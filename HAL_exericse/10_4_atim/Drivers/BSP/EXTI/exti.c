#include "./BSP/EXTI/exti.h"
#include "./BSP/LED/led.h"
#include "./BSP/BEEP/beep.h"
#include "./BSP/KEY/key.h"
#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/delay/delay.h"

void KEY0_INT_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(KEY0_INT_GPIO_PIN);         /* �����жϴ����ú��� ���KEY0�����ж��� ���жϱ�־λ */
    __HAL_GPIO_EXTI_CLEAR_IT(KEY0_INT_GPIO_PIN);         /* HAL��Ĭ�������ж��ٴ���ص����˳�ʱ����һ���жϣ����ⰴ�������󴥷� */
}

void KEY1_INT_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(KEY1_INT_GPIO_PIN);         /* �����жϴ����ú��� ���KEY0�����ж��� ���жϱ�־λ */
    __HAL_GPIO_EXTI_CLEAR_IT(KEY1_INT_GPIO_PIN);         /* HAL��Ĭ�������ж��ٴ���ص����˳�ʱ����һ���жϣ����ⰴ�������󴥷� */
}

void KEY2_INT_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(KEY2_INT_GPIO_PIN);         /* �����жϴ����ú��� ���KEY0�����ж��� ���жϱ�־λ */
    __HAL_GPIO_EXTI_CLEAR_IT(KEY2_INT_GPIO_PIN);         /* HAL��Ĭ�������ж��ٴ���ص����˳�ʱ����һ���жϣ����ⰴ�������󴥷� */
}

void KEY_UP_INT_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(KEY_UP_INT_GPIO_PIN);         /* �����жϴ����ú��� ���KEY0�����ж��� ���жϱ�־λ */
    __HAL_GPIO_EXTI_CLEAR_IT(KEY_UP_INT_GPIO_PIN);         /* HAL��Ĭ�������ж��ٴ���ص����˳�ʱ����һ���жϣ����ⰴ�������󴥷� */
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    delay_ms(20);
    switch(GPIO_Pin)
    {
        case KEY0_INT_GPIO_PIN:
            if (KEY0 == 0)
            {
                LED0_TOGGLE();  /* LED0 ״̬ȡ�� */ 
            }
            break;
        case KEY1_INT_GPIO_PIN:
            if (KEY1 == 0)
            {
                LED1_TOGGLE();  /* LED1 ״̬ȡ�� */ 
            }
            break;
        case KEY2_INT_GPIO_PIN:
            if (KEY2 == 0)
            {
                LED1_TOGGLE();  /* LED1 ״̬ȡ�� */
                LED0_TOGGLE();  /* LED0 ״̬ȡ�� */ 
            }
            break;
        case KEY_UP_INT_GPIO_PIN:
            if (KEY_UP == 1)
            {
                BEEP_TOGGLE();  /* ������״̬ȡ�� */ 
            }
            break;
        default:
            break;
    }
}    


/* �ⲿ�жϳ�ʼ�� */
void exti_init()
{
    /* ʹ��IO��ʱ�� */
    KEY0_INT_GPIO_CLK_ENABLE();
    KEY1_INT_GPIO_CLK_ENABLE();
    KEY2_INT_GPIO_CLK_ENABLE();
    KEY_UP_INT_GPIO_CLK_ENABLE();
    //key_init();
    /* ����IO��ģʽ����������������SYSCFGʱ�ӣ�����IO�����ж��߶�Ӧ��ϵ */
    GPIO_InitTypeDef key_int_gpio_init;
    
    
    key_int_gpio_init.Pin = KEY0_INT_GPIO_PIN;
    key_int_gpio_init.Mode = GPIO_MODE_IT_FALLING;
    key_int_gpio_init.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(KEY0_INT_GPIO_PORT, &key_int_gpio_init);
    
    key_int_gpio_init.Pin = KEY1_INT_GPIO_PIN;
    //key_int_gpio_init.Mode = GPIO_MODE_IT_FALLING;
    //key_int_gpio_init.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(KEY1_INT_GPIO_PORT, &key_int_gpio_init);
    
    key_int_gpio_init.Pin = KEY2_INT_GPIO_PIN;
    //key_int_gpio_init.Mode = GPIO_MODE_IT_FALLING;
    //key_int_gpio_init.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(KEY2_INT_GPIO_PORT, &key_int_gpio_init);
    
    key_int_gpio_init.Pin = KEY_UP_INT_GPIO_PIN;
    key_int_gpio_init.Mode = GPIO_MODE_IT_RISING;
    key_int_gpio_init.Pull = GPIO_PULLDOWN;
    HAL_GPIO_Init(KEY_UP_INT_GPIO_PORT, &key_int_gpio_init);
    
    HAL_NVIC_SetPriority(KEY0_INT_IRQn, 1, 2); /* ������ռ���ȼ�3 �����ȼ�2 */
    HAL_NVIC_EnableIRQ(KEY0_INT_IRQn);         /* ʹ���ж���4 */
    
    HAL_NVIC_SetPriority(KEY1_INT_IRQn, 1, 2); /* ������ռ���ȼ�2 �����ȼ�2*/
    HAL_NVIC_EnableIRQ(KEY1_INT_IRQn);         /* ʹ���ж���3 */
    
    HAL_NVIC_SetPriority(KEY2_INT_IRQn, 1, 2); /* ������ռ���ȼ�1 �����ȼ�2*/
    HAL_NVIC_EnableIRQ(KEY2_INT_IRQn);         /* ʹ���ж���2 */
    
    HAL_NVIC_SetPriority(KEY_UP_INT_IRQn, 1, 2); /* ������ռ���ȼ�0 �����ȼ�2*/
    HAL_NVIC_EnableIRQ(KEY_UP_INT_IRQn);         /* ʹ���ж���0 */
}
