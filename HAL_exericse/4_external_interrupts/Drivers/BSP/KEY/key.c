#include "./BSP/KEY/key.h"

void key_init()
{
    /* 使能时钟 */
    KEY0_GPIO_CLK_ENABLE();
    KEY1_GPIO_CLK_ENABLE();
    KEY2_GPIO_CLK_ENABLE();
    KEY_UP_GPIO_CLK_ENABLE();
    
    /* GPIO_INIT 初始化GPIO_InitTypeDef struct*/
    GPIO_InitTypeDef key_gpio_init;
    key_gpio_init.Pin = KEY0_GPIO_PIN;
    key_gpio_init.Mode = GPIO_MODE_INPUT;
    key_gpio_init.Pull = GPIO_PULLUP;
    key_gpio_init.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(KEY0_GPIO_PORT, &key_gpio_init);
    
    key_gpio_init.Pin = KEY1_GPIO_PIN;
    HAL_GPIO_Init(KEY1_GPIO_PORT, &key_gpio_init);
    
    key_gpio_init.Pin = KEY2_GPIO_PIN;
    HAL_GPIO_Init(KEY2_GPIO_PORT, &key_gpio_init);
    
    key_gpio_init.Pin = KEY_UP_GPIO_PIN;
    key_gpio_init.Pull = GPIO_PULLDOWN;
    HAL_GPIO_Init(KEY_UP_GPIO_PORT, &key_gpio_init);
}

uint8_t key_scan(uint8_t mode)
{
    uint8_t key_val = 0;
    static uint8_t key_up = 1; 
    
    if(key_up && (KEY0 == 0 || KEY1 == 0 || KEY2 == 0 || KEY_UP == 1))
    {
        delay_ms(10);
        key_up = 0;
        if(KEY0 == 0)   key_val= KEY0_PRES;
        if(KEY1 == 0)   key_val= KEY1_PRES;
        if(KEY2 == 0)   key_val= KEY2_PRES;
        if(KEY_UP == 1) key_val= KEY_UP_PRES;
    }
    else if(KEY0 == 1 && KEY1 == 1 && KEY2 == 1 && KEY_UP == 0)
    {
        key_up = 1;
    }
    return key_val;
}
