#ifndef __ST480MC_H
#define __ST480MC_H

#include "./SYSTEM/sys/sys.h"


#define ST480MC_ADDR            0X0C    /* ST480MC IIC器件地址(A0 = 0时) */
#define ST480MC_RESET           0XF0    /* ST480MC 复位命令 */
#define ST480MC_READ_REG        0X50    /* ST480MC 读寄存器 */
#define ST480MC_WRITE_REG       0X60    /* ST480MC 写寄存器 */
#define ST480MC_READ_DATA       0X4F    /* ST480MC 读取全部数据(zxyt) */
#define ST480MC_BURST_MODE      0X1F    /* ST480MC 突发模式读取数据(zxyt) */
#define ST480MC_SINGLE_MODE     0X3F    /* ST480MC 单次测量读取数据(zxyt) */

#define ST480MC_SENS_XY         667     /* X,Y 轴灵敏度; 单位:  LSB/Gauss */
#define ST480MC_SENS_Z          400     /* Z   轴灵敏度  单位:  LSB/Gauss */


uint8_t st480mc_init(void);                                                             /* 初始化 */
uint8_t st480mc_read_nbytes(uint8_t addr, uint8_t length, uint8_t *buf);                /* 读N字节,可以发送命令 */
uint16_t st480mc_read_register(uint8_t reg);                                            /* 读寄存器 */
uint8_t st480mc_write_register(uint8_t reg, uint16_t data);                             /* 写寄存器 */

uint8_t st480mc_read_magdata(int16_t *pmagx, int16_t *pmagy, int16_t *pmagz);           /* 读取磁力原始数据(单次) */
uint8_t st480mc_read_temperature(float *ptemp);                                         /* 读取温度传感器值(单次,℃) */
uint8_t st480mc_read_magdata_average(int16_t *pmagx, int16_t *pmagy, int16_t *pmagz, uint8_t times);    /* 读取磁力原始数据(平均值) */

#endif
