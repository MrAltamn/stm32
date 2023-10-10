#ifndef __OLED_H
#define __OLED_H
#include "stdlib.h" 
#include "./SYSTEM/sys/sys.h"
/* OLED 8080并口模式三个函数
 * OLED_RST()    设置RST 复位引脚
 * OLED_CS()     设置CS  片选引脚
 * OLED_RS()     设置RS  D/C 命令/数据标志引脚  1：读写数据，  0：读写命令
 * OLED_WR()     设置WR  写入数据引脚
 * OLED_RD()     设置RD  读入数据引脚
*/
#define OLED_RST(x)     do{ x ? \
                                  HAL_GPIO_WritePin(GPIOG, GPIO_PIN_15, GPIO_PIN_SET) : \
                                  HAL_GPIO_WritePin(GPIOG, GPIO_PIN_15, GPIO_PIN_RESET); \
                        }while(0)       /* 设置RST引脚 */

#define OLED_CS(x)      do{ x ? \
                                  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_SET) : \
                                  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_RESET); \
                        }while(0)       /* 设置CS引脚 */

#define OLED_RS(x)      do{ x ? \
                                  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_6, GPIO_PIN_SET) : \
                                  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_6, GPIO_PIN_RESET); \
                        }while(0)       /* 设置RS引脚 */

#define OLED_WR(x)      do{ x ? \
                                  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET) :  \
                                  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET); \
                        } while (0)     /* 设置WR引脚 */

#define OLED_RD(x)      do{ x ? \
                                  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, GPIO_PIN_SET) : \
                                  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, GPIO_PIN_RESET); \
                        }while(0)       /* 设置RD引脚 */

/* 命令/数据 定义 */
#define OLED_CMD        0       /* 写命令 */
#define OLED_DATA       1       /* 写数据 */
                        
                        
/******************************************************************************************/
    
static void oled_wr_byte(uint8_t data, uint8_t cmd);    /* 写一个字节到OLED */
static uint32_t oled_pow(uint8_t m, uint8_t n);         /* OLED求平方函数 */


void oled_init(void);           /* OLED初始化 */
void oled_clear(void);          /* OLED清屏 */
void oled_display_on(void);     /* 开启OLED显示 */
void oled_display_off(void);    /* 关闭OLED显示 */
void oled_refresh_gram(void);   /* 更新显存到OLED */ 
void oled_draw_point(uint8_t x, uint8_t y, uint8_t dot);    /* OLED画点 */
void oled_fill(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t dot);        /* OLED区域填充 */
void oled_show_char(uint8_t x, uint8_t y, uint8_t chr, uint8_t size, uint8_t mode); /* OLED显示字符 */
void oled_show_num(uint8_t x, uint8_t y, uint32_t num, uint8_t len, uint8_t size);  /* OLED显示数字 */
void oled_show_string(uint8_t x, uint8_t y, const char *p, uint8_t size);           /* OLED显示字符串 */                        

#endif
