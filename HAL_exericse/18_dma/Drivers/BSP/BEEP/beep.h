#ifndef _BEEP_H
#define _BEEP_H

#include "./SYSTEM/sys/sys.h"

/* ���Ŷ��� */
#define BEEP_GPIO_PORT      GPIOF
#define BEEP_GPIO_PIN       GPIO_PIN_8

/* PF��ʹ�� */
#define BEEP_GPIO_CLK_ENABLE() do{ __HAL_RCC_GPIOF_CLK_ENABLE(); }while(0)

/* ���������� 1-�죬0-��*/
#define BEEP(x) do{ x ? \
                    HAL_GPIO_WritePin(BEEP_GPIO_PORT, BEEP_GPIO_PIN, GPIO_PIN_SET) : \
                    HAL_GPIO_WritePin(BEEP_GPIO_PORT, BEEP_GPIO_PIN, GPIO_PIN_RESET); \
                  }while(0) 

/* ��������ת */
#define BEEP_TOGGLE() do{ HAL_GPIO_TogglePin(BEEP_GPIO_PORT, BEEP_GPIO_PIN ); }while(0)

/* ������������ʼ������ */
void beep_init(void);
#endif
