#include "./BSP/IIC/myiic.h"
#include "./BSP/ST480MC/st480mc.h"
#include "./SYSTEM/delay/delay.h"
#include "./SYSTEM/usart/usart.h"
#include <math.h>

uint8_t st480mc_read_nbytes(uint8_t addr, uint8_t length, uint8_t *buf)
{
    uint8_t i;
    
    iic_start();
    iic_send_byte((ST480MC_ADDR << 1) | 0X00);  /* IIC地址最低位是0, 表示写入 */
    
    if (iic_wait_ack())
    {
        iic_stop();
        return 1;
    }
    
    iic_send_byte(addr);                        /* 写地址/命令 */
    iic_wait_ack();
    
    iic_start();
    iic_send_byte((ST480MC_ADDR << 1) | 0x01);  /* IIC地址最低位是1, 表示读取 */
    iic_wait_ack();
    
    for (i = 0; i < length; i++)                /* 循环读取 数据 */
    {
        buf[i] = iic_read_byte(1);
    }
    
    iic_stop();
    return 0;
}

uint8_t st480mc_write_register(uint8_t reg, uint16_t data)
{
    iic_start();
    iic_send_byte((ST480MC_ADDR << 1) | 0X00);  /* IIC地址最低位是0, 表示写入 */
    if (iic_wait_ack())
    {
        iic_stop();
        return 1;
    }
    
    iic_send_byte(ST480MC_WRITE_REG);           /* 发送写寄存器命令 */
    iic_wait_ack();
    
    iic_send_byte(data >> 8);                   /* 发送高字节数据 */
    iic_wait_ack();
    
    iic_send_byte(data & 0XFF);                 /* 发送低字节数据 */
    iic_wait_ack();
    
    iic_send_byte(reg << 2);                    /* 发送寄存器地址(低2位默认是0) */
    iic_wait_ack();
    
    iic_stop();
    
    return 0;
}

uint16_t st480mc_read_register(uint8_t reg)
{
    uint8_t buf[3];
    uint8_t i;

    iic_start();
    iic_send_byte((ST480MC_ADDR << 1) | 0X00);  /* IIC地址最低位是0, 表示写入 */
    iic_wait_ack();
    
    iic_send_byte(ST480MC_READ_REG);            /* 发送读寄存器命令 */
    iic_wait_ack();
    
    iic_send_byte(reg << 2);                    /* 发送寄存器地址(低2位默认是0) */
    iic_wait_ack();
    
    iic_start();
    iic_send_byte((ST480MC_ADDR << 1) | 0x01);  /* IIC地址最低位是1, 表示读取 */
    iic_wait_ack();
    
    for (i = 0; i < 3; i++)                     /* 循环读取 数据 */
    {
        buf[i] = iic_read_byte(1);
    }
    
    iic_stop();
    
    if (buf[0] & 0X10)
    {
        return 0XFFFF;
    }
    
    return ((uint16_t)buf[1] << 8) | buf[2];    /* 返回寄存器数据(16位) */
}

uint8_t st480mc_init(void)
{
    uint8_t status;
    uint8_t res = 0XFF;
    uint8_t retry = 10;
    
    iic_init();
    
    while ((retry --) && res)    /* 多次尝试, 直到 res == 0, 即等到ST480MC有 ACK反应 */
    {
        res = st480mc_read_nbytes(ST480MC_RESET, 1, &status);   /* 发送复位命令,并读状态寄存器 */
        delay_ms(20);
    }
    return res;
}

uint8_t st480mc_read_magdata(int16_t *pmagx, int16_t *pmagy, int16_t *pmagz)
{
    uint8_t buf[7];

    st480mc_read_nbytes(ST480MC_SINGLE_MODE & 0XFE, 1, buf);    /* 发送单次测量命令(不测量温度) */
    delay_ms(15);                                               /* 延时15ms,基本能争取读取数据 */
    st480mc_read_nbytes(ST480MC_READ_DATA & 0XFE, 7, buf);      /* 发送读取数据命令(不读取温度) */

    if (buf[0] & 0X10)  /* 读取数据异常 */
    {
        return buf[0];  /* 发生错误了 */
    }
    else
    {
        *pmagx = (short int)(buf[1] << 8) | buf[2];     /* 组合数据 */
        *pmagy = (short int)(buf[3] << 8) | buf[4];     /* 组合数据 */
        *pmagz = (short int)(buf[5] << 8) | buf[6];     /* 组合数据 */
    }
    return 0;
}

uint8_t st480mc_read_temperature(float *ptemp)
{
    uint8_t buf[9];

    st480mc_read_nbytes(ST480MC_SINGLE_MODE, 1, buf);    /* 发送单次测量命令(含温度) */
    delay_ms(15);                                        /* 延时15ms,基本能争取读取数据 */
    st480mc_read_nbytes(ST480MC_READ_DATA, 9, buf);      /* 发送读取数据命令(含温度) */

    if (buf[0] & 0X10)  /* 读取数据异常 */
    {
        return buf[0];  /* 发生错误了 */
    }
    else
    {
        *ptemp = (uint16_t)(buf[1] << 8) | buf[2];      /* 得到温度传感器原始值 */
        *ptemp = (*ptemp - 46244) / 45.2f + 25;         /* 根据原厂提供的计算公式,换算成℃ */
    }
    return 0;
}

uint8_t st480mc_read_magdata_average(int16_t *pmagx, int16_t *pmagy, int16_t *pmagz, uint8_t times)
{
    uint8_t i = 0;
    uint8_t error_cnt = 0;
    int32_t magx = 0;
    int32_t magy = 0;
    int32_t magz = 0;

    while (i < times)    /* 连续读取times次 */
    {
        if (st480mc_read_magdata(pmagx, pmagy, pmagz) == 0)    /* 读取数据是否正常? */
        {
            magx += *pmagx;         /* 累加 */
            magy += *pmagy;
            magz += *pmagz;
            
            i++;
            error_cnt = 0;
        }
        else
        {
            error_cnt++;            /* 错误计数器 */
            delay_ms(10);
            if (error_cnt > 100)    /* 连续100次出错, 直接返回异常 */
            {
                return 0XFF;
            }
        }
    }
    
    *pmagx = magx / times;  /* 取平均值 */
    *pmagy = magy / times;  /* 取平均值 */
    *pmagz = magz / times;  /* 取平均值 */
    
    return 0;
}









