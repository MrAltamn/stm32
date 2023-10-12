#ifndef _KEY_H
#define _KEY_H
#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/delay/delay.h"

/* KEY0 ���Ŷ��� */
#define KEY0_GPIO_PORT GPIOE
#define KEY0_GPIO_PIN  GPIO_PIN_4
/* KEY0 ʱ��ʹ�� */
#define KEY0_GPIO_CLK_ENABLE() do{ __HAL_RCC_GPIOE_CLK_ENABLE(); }while(0)

/* KEY1 ���Ŷ��� */
#define KEY1_GPIO_PORT GPIOE
#define KEY1_GPIO_PIN  GPIO_PIN_3
/* KEY1 ʱ��ʹ�� */
#define KEY1_GPIO_CLK_ENABLE() do{ __HAL_RCC_GPIOE_CLK_ENABLE(); }while(0)

/* KEY2 ���Ŷ��� */
#define KEY2_GPIO_PORT GPIOE
#define KEY2_GPIO_PIN  GPIO_PIN_2
/* KEY2 ʱ��ʹ�� */
#define KEY2_GPIO_CLK_ENABLE() do{ __HAL_RCC_GPIOE_CLK_ENABLE(); }while(0)

/* KEY_UP ���Ŷ��� */
#define KEY_UP_GPIO_PORT GPIOA
#define KEY_UP_GPIO_PIN  GPIO_PIN_0
/* KEY_UP ʱ��ʹ�� */
#define KEY_UP_GPIO_CLK_ENABLE() do{ __HAL_RCC_GPIOA_CLK_ENABLE(); }while(0)

/* ���������� */
#define KEY0   HAL_GPIO_ReadPin(KEY0_GPIO_PORT, KEY0_GPIO_PIN)
#define KEY1   HAL_GPIO_ReadPin(KEY1_GPIO_PORT, KEY1_GPIO_PIN)
#define KEY2   HAL_GPIO_ReadPin(KEY2_GPIO_PORT, KEY2_GPIO_PIN)
#define KEY_UP HAL_GPIO_ReadPin(KEY_UP_GPIO_PORT, KEY_UP_GPIO_PIN)

/* �������� */
#define KEY0_PRES   1
#define KEY1_PRES   2
#define KEY2_PRES   3
#define KEY_UP_PRES 4

void key_init(void);
uint8_t key_scan(uint8_t mode);
#endif
