#include "./BSP/BEEP/beep.h"

void beep_init()
{
    BEEP_GPIO_CLK_ENABLE();
    GPIO_InitTypeDef beep_init_struct;
    
    beep_init_struct.Pin = BEEP_GPIO_PIN;
    beep_init_struct.Mode = GPIO_MODE_OUTPUT_PP;
    beep_init_struct.Pull = GPIO_PULLUP;
    beep_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;
    
    HAL_GPIO_Init(BEEP_GPIO_PORT, &beep_init_struct);
    
    BEEP(0);
}
