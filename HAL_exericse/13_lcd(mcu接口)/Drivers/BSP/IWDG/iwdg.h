#ifndef __IWDG_H
#define __IWDG_H
#include "./SYSTEM/sys/sys.h"

void iwdg_init(uint32_t prer, uint16_t rlr);        /* 初始化IWDG，并使能IWDG */
void iwdg_feed(void);                               /* 喂狗 */


#endif
