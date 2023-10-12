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

    temp = at24cxx_read_one_byte(addr);     /* ����ÿ�ο�����дAT24CXX */
    if (temp == 0x55)   /* ��ȡ�������� */
    {
        return 0;
    }
    else    /* �ų���һ�γ�ʼ������� */
    {
        at24cxx_write_one_byte(addr, 0x55); /* ��д������ */
        temp = at24cxx_read_one_byte(255);  /* �ٶ�ȡ���� */

        if (temp == 0x55)return 0;
    }

    return 1;
}

uint8_t at24cxx_read_one_byte(uint16_t addr)
{
    uint8_t temp = 0;
    
    iic_start();                   /* ������ʼ�ź� */
    iic_send_byte(0xA0);           /* ����д����, IIC�涨���λ��0, ��ʾд�� */
    iic_wait_ack();                /* ÿ�η�����һ���ֽ�,��Ҫ�ȴ�ACK */
    iic_send_byte(addr);           /* ���͵�λ��ַ */
    iic_wait_ack();                /* ÿ�η�����һ���ֽ�,��Ҫ�ȴ�ACK */
    iic_start();                   /* ������ʼ�ź� */
    //iic_wait_ack();                /* ÿ�η�����һ���ֽ�,��Ҫ�ȴ�ACK */
    iic_send_byte(0xA1);           /* �������ģʽ, IIC�涨���λ��1, ��ʾ��ȡ */
    iic_wait_ack();                /* ÿ�η�����һ���ֽ�,��Ҫ�ȴ�ACK */
    temp = iic_read_byte(0);       /* ����һ���ֽ����� */
    iic_stop();                    /* ����һ��ֹͣ���� */
    return temp;
}

void at24cxx_write_one_byte(uint16_t addr,uint8_t data)
{ 
    iic_start();                   /* ������ʼ�ź� */
    iic_send_byte(0xA0);           /* ����д����, IIC�涨���λ��0, ��ʾд�� */
    iic_wait_ack();                /* ÿ�η�����һ���ֽ�,��Ҫ�ȴ�ACK */
    iic_send_byte(addr);           /* ���͵�ַ */
    iic_wait_ack();                /* ÿ�η�����һ���ֽ�,��Ҫ�ȴ�ACK */
    iic_send_byte(data);           /* ����1�ֽ� */
    iic_wait_ack();                /* �ȴ�ACK */
    iic_stop();                    /* ����һ��ֹͣ���� */
    delay_ms(10);                  /* ע��: EEPROM д��Ƚ���,����ȵ�10ms����д��һ���ֽ� */
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






