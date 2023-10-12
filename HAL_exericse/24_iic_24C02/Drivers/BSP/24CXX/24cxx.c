#include "./BSP/IIC/myiic.h"
#include "./BSP/24CXX/24cxx.h"
#include "./SYSTEM/delay/delay.h"

void at24cxx_init(void)
{
    iic_init();
}

uint8_t at24cxx_check(void)
{
    uint8_t temp;
    uint16_t addr = EE_TYPE;

    temp = at24cxx_read_one_byte(addr);     /* 避免每次开机都写AT24CXX */
    if (temp == 0x55)   /* 读取数据正常 */
    {
        return 0;
    }
    else    /* 排除第一次初始化的情况 */
    {
        at24cxx_write_one_byte(addr, 0x55); /* 先写入数据 */
        temp = at24cxx_read_one_byte(255);  /* 再读取数据 */

        if (temp == 0x55)return 0;
    }

    return 1;
}

uint8_t at24cxx_read_one_byte(uint16_t addr)
{
    uint8_t temp = 0;
    
    iic_start();                   /* 发送起始信号 */
    iic_send_byte(0xA0);           /* 发送写命令, IIC规定最低位是0, 表示写入 */
    iic_wait_ack();                /* 每次发送完一个字节,都要等待ACK */
    iic_send_byte(addr);           /* 发送低位地址 */
    iic_wait_ack();                /* 每次发送完一个字节,都要等待ACK */
    iic_start();                   /* 发送起始信号 */
    //iic_wait_ack();                /* 每次发送完一个字节,都要等待ACK */
    iic_send_byte(0xA1);           /* 进入接收模式, IIC规定最低位是1, 表示读取 */
    iic_wait_ack();                /* 每次发送完一个字节,都要等待ACK */
    temp = iic_read_byte(0);       /* 接收一个字节数据 */
    iic_stop();                    /* 产生一个停止条件 */
    return temp;
}

void at24cxx_write_one_byte(uint16_t addr,uint8_t data)
{ 
    iic_start();                   /* 发送起始信号 */
    iic_send_byte(0xA0);           /* 发送写命令, IIC规定最低位是0, 表示写入 */
    iic_wait_ack();                /* 每次发送完一个字节,都要等待ACK */
    iic_send_byte(addr);           /* 发送地址 */
    iic_wait_ack();                /* 每次发送完一个字节,都要等待ACK */
    iic_send_byte(data);           /* 发送1字节 */
    iic_wait_ack();                /* 等待ACK */
    iic_stop();                    /* 产生一个停止条件 */
    delay_ms(10);                  /* 注意: EEPROM 写入比较慢,必须等到10ms后再写下一个字节 */
}

void at24cxx_write(uint16_t addr, uint8_t *pbuf, uint16_t datalen)
{
    while (datalen--)
    {
        at24cxx_write_one_byte(addr, *pbuf);
        addr++;
        pbuf++;
    }
}

void at24cxx_read(uint16_t addr, uint8_t *pbuf, uint16_t datalen)
{
    while (datalen--)
    {
        *pbuf++ = at24cxx_read_one_byte(addr++);
    }
}






