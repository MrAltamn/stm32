#include "./BSP/WWDG/wwdg.h"

WWDG_HandleTypeDef wwdg_handle;

void wwdg_init(uint32_t coun, uint32_t wind, uint32_t fpre)
{
    wwdg_handle.Instance = WWDG;
    wwdg_handle.Init.Prescaler = fpre;
    wwdg_handle.Init.Window = wind;
    wwdg_handle.Init.Counter = coun;
    wwdg_handle.Init.EWIMode = WWDG_EWI_ENABLE;
    HAL_WWDG_Init(&wwdg_handle);
}

void HAL_WWDG_MspInit(WWDG_HandleTypeDef *hwwdg)
{
    __HAL_RCC_WWDG_CLK_ENABLE();
    
    HAL_NVIC_SetPriority(WWDG_IRQn, 2, 3);
    HAL_NVIC_EnableIRQ(WWDG_IRQn);
}

void WWDG_IRQHandler(void)
{
    HAL_WWDG_IRQHandler(&wwdg_handle);
}

void HAL_WWDG_EarlyWakeupCallback(WWDG_HandleTypeDef *hwwdg)
{
    HAL_WWDG_Refresh(&wwdg_handle);
    LED1_TOGGLE();
}
