#include "./BSP/EXTI/exti.h"
#include "./BSP/LED/led.h"
#include "./BSP/BEEP/beep.h"
#include "./BSP/KEY/key.h"
#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/delay/delay.h"

void KEY0_INT_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(KEY0_INT_GPIO_PIN);         /* 调用中断处理公用函数 清除KEY0所在中断线 的中断标志位 */
    __HAL_GPIO_EXTI_CLEAR_IT(KEY0_INT_GPIO_PIN);         /* HAL库默认先清中断再处理回调，退出时再清一次中断，避免按键抖动误触发 */
}

void KEY1_INT_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(KEY1_INT_GPIO_PIN);         /* 调用中断处理公用函数 清除KEY0所在中断线 的中断标志位 */
    __HAL_GPIO_EXTI_CLEAR_IT(KEY1_INT_GPIO_PIN);         /* HAL库默认先清中断再处理回调，退出时再清一次中断，避免按键抖动误触发 */
}

void KEY2_INT_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(KEY2_INT_GPIO_PIN);         /* 调用中断处理公用函数 清除KEY0所在中断线 的中断标志位 */
    __HAL_GPIO_EXTI_CLEAR_IT(KEY2_INT_GPIO_PIN);         /* HAL库默认先清中断再处理回调，退出时再清一次中断，避免按键抖动误触发 */
}

void KEY_UP_INT_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(KEY_UP_INT_GPIO_PIN);         /* 调用中断处理公用函数 清除KEY0所在中断线 的中断标志位 */
    __HAL_GPIO_EXTI_CLEAR_IT(KEY_UP_INT_GPIO_PIN);         /* HAL库默认先清中断再处理回调，退出时再清一次中断，避免按键抖动误触发 */
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    delay_ms(20);
    switch(GPIO_Pin)
    {
        case KEY0_INT_GPIO_PIN:
            if (KEY0 == 0)
            {
                LED0_TOGGLE();  /* LED0 状态取反 */ 
            }
            break;
        case KEY1_INT_GPIO_PIN:
            if (KEY1 == 0)
            {
                LED1_TOGGLE();  /* LED1 状态取反 */ 
            }
            break;
        case KEY2_INT_GPIO_PIN:
            if (KEY2 == 0)
            {
                LED1_TOGGLE();  /* LED1 状态取反 */
                LED0_TOGGLE();  /* LED0 状态取反 */ 
            }
            break;
        case KEY_UP_INT_GPIO_PIN:
            if (KEY_UP == 1)
            {
                BEEP_TOGGLE();  /* 蜂鸣器状态取反 */ 
            }
            break;
        default:
            break;
    }
}    


/* 外部中断初始化 */
void exti_init()
{
    /* 使能IO口时钟 */
    KEY0_INT_GPIO_CLK_ENABLE();
    KEY1_INT_GPIO_CLK_ENABLE();
    KEY2_INT_GPIO_CLK_ENABLE();
    KEY_UP_INT_GPIO_CLK_ENABLE();
    //key_init();
    /* 设置IO口模式，触发条件，开启SYSCFG时钟，设置IO口与中断线对应关系 */
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
    
    HAL_NVIC_SetPriority(KEY0_INT_IRQn, 1, 2); /* 设置抢占优先级3 子优先级2 */
    HAL_NVIC_EnableIRQ(KEY0_INT_IRQn);         /* 使能中断线4 */
    
    HAL_NVIC_SetPriority(KEY1_INT_IRQn, 1, 2); /* 设置抢占优先级2 子优先级2*/
    HAL_NVIC_EnableIRQ(KEY1_INT_IRQn);         /* 使能中断线3 */
    
    HAL_NVIC_SetPriority(KEY2_INT_IRQn, 1, 2); /* 设置抢占优先级1 子优先级2*/
    HAL_NVIC_EnableIRQ(KEY2_INT_IRQn);         /* 使能中断线2 */
    
    HAL_NVIC_SetPriority(KEY_UP_INT_IRQn, 1, 2); /* 设置抢占优先级0 子优先级2*/
    HAL_NVIC_EnableIRQ(KEY_UP_INT_IRQn);         /* 使能中断线0 */
}
