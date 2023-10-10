#include "./BSP/IWDG/iwdg.h"

IWDG_HandleTypeDef iwdg_handle;

void iwdg_init(uint32_t prer, uint16_t rlr)
{
    iwdg_handle.Instance = IWDG;
    iwdg_handle.Init.Prescaler = prer;
    iwdg_handle.Init.Reload = rlr;
    HAL_IWDG_Init(&iwdg_handle);
}

void iwdg_feed(void)
{
    HAL_IWDG_Refresh(&iwdg_handle);
}
