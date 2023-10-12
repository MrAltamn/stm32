#include "./BSP/IIC/myiic.h"
#include "./SYSTEM/delay/delay.h"

void iic_init(void)
{
    GPIO_InitTypeDef iic_gpio_init;
    
    IIC_SCL_GPIO_CLK_ENABLE();     /* SCL����ʱ��ʹ�� */
    IIC_SDA_GPIO_CLK_ENABLE();     /* SDA����ʱ��ʹ�� */
    
    iic_gpio_init.Pin = IIC_SCL_GPIO_PIN;
    iic_gpio_init.Mode = GPIO_MODE_OUTPUT_PP;         /* ������� */
    iic_gpio_init.Pull = GPIO_PULLUP;                 /* ���� */
    iic_gpio_init.Speed = GPIO_SPEED_FREQ_VERY_HIGH;  /* ���� */
    HAL_GPIO_Init(IIC_SCL_GPIO_PORT, &iic_gpio_init); /* SCL */
    
    iic_gpio_init.Pin = IIC_SDA_GPIO_PIN;
    iic_gpio_init.Mode = GPIO_MODE_OUTPUT_OD;         /* ��©��� */
    HAL_GPIO_Init(IIC_SDA_GPIO_PORT, &iic_gpio_init); /* SDA */
    
    iic_stop();     /* ֹͣ�����������豸 */
}

static void iic_delay(void)
{
    delay_us(2);    /* 2us����ʱ, ��д�ٶ���250Khz���� */
}


void iic_start(void)
{
    IIC_SDA(1);
    IIC_SCL(1);
    iic_delay();
    IIC_SDA(0);          /* START�ź�: ��SCLΪ��ʱ, SDA�Ӹ߱�ɵ�, ��ʾ��ʼ�ź� */
    iic_delay();
    IIC_SCL(0);          /* ǯסI2C���ߣ�׼�����ͻ�������� */
    iic_delay(); 
}

void iic_stop(void)
{
    IIC_SDA(0);          /* STOP�ź�: ��SCLΪ��ʱ, SDA�ӵͱ�ɸ�, ��ʾֹͣ�ź� */
    iic_delay();
    IIC_SCL(1);
    iic_delay();
    IIC_SDA(1);          /* ����I2C���߽����ź� */
    iic_delay();
}

void iic_ack(void)
{
    IIC_SDA(0);     /* SCL 0 -> 1 ʱ SDA = 0,��ʾӦ�� */
    iic_delay();
    IIC_SCL(1);     /* ����һ��ʱ�� */
    iic_delay();
    IIC_SCL(0);
    iic_delay();
    IIC_SDA(1);     /* �����ͷ�SDA�� */
    iic_delay();
}

void iic_nack(void)
{
    IIC_SDA(1);     /* SCL 0 -> 1  ʱ SDA = 1,��ʾ��Ӧ�� */
    iic_delay();
    IIC_SCL(1);     /* ����һ��ʱ�� */
    iic_delay();
    IIC_SCL(0);
    iic_delay();
}

uint8_t iic_wait_ack(void)
{
    uint8_t waittime = 0;
    uint8_t rack = 0;
    
    IIC_SDA(1);             /* �����ͷ�SDA��(��ʱ�ⲿ������������SDA��) */
    iic_delay();
    IIC_SCL(1);             /* SCL=1, ��ʱ�ӻ����Է���ACK */
    iic_delay();
    
    while(IIC_READ_SDA)     /* �ȴ�Ӧ�� */
    {
        waittime++;
        if(waittime > 250)
        {
            iic_stop();
            rack = 1;
            break;
        }
    }
    IIC_SCL(0);             /* SCL=0, ����ACK��� */
    iic_delay();
    return rack;
}

void iic_send_byte(uint8_t txd)
{
    uint8_t t;
    for(t = 0; t < 8; t++)
    {
        IIC_SDA((txd & 0x80) >> 7);  /* ��λ�ȷ��� */
        iic_delay(); 
        IIC_SCL(1);
        iic_delay();
        IIC_SCL(0);
        iic_delay();
        txd <<= 1;                  /* ����1λ,������һ�η��� */
    }
    IIC_SDA(1);                     /* �������, �����ͷ�SDA�� */
}

uint8_t iic_read_byte(unsigned char ack)
{
    uint8_t i, receive = 0;
    
        for (i = 0; i < 8; i++ )    /* ����1���ֽ����� */
    {
        receive <<= 1;  /* ��λ�����,�������յ�������λҪ���� */
        IIC_SCL(1);
        iic_delay();

        if (IIC_READ_SDA)
        {
            receive++;
        }
        
        IIC_SCL(0);
        iic_delay();
    }
    
    if (!ack)
    {
        iic_nack();     /* ����nACK */
    }
    else
    {
        iic_ack();      /* ����ACK */
    }

    return receive;
}
