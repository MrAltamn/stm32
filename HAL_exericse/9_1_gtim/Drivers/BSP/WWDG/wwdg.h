#ifndef __WWDG_H
#define __WWDG_H
#include "./SYSTEM/sys/sys.h"
#include "./BSP/LED/led.h"
void wwdg_init(uint32_t coun, uint32_t wind, uint32_t fpre);        /* 初始化WWDG，并使能WWDG */

#endif
