#ifndef __IWDG_H
#define __IWDG_H
#include "./SYSTEM/sys/sys.h"

void iwdg_init(uint32_t prer, uint16_t rlr);        /* ��ʼ��IWDG����ʹ��IWDG */
void iwdg_feed(void);                               /* ι�� */


#endif
