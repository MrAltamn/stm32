#include "./BSP/IIC/myiic.h"
#include "./SYSTEM/delay/delay.h"

void iic_init(void)
{
    GPIO_InitTypeDef iic_gpio_init;
    
    IIC_SCL_GPIO_CLK_ENABLE();     /* SCL引脚时钟使能 */
    IIC_SDA_GPIO_CLK_ENABLE();     /* SDA引脚时钟使能 */
    
    iic_gpio_init.Pin = IIC_SCL_GPIO_PIN;
    iic_gpio_init.Mode = GPIO_MODE_OUTPUT_PP;         /* 推挽输出 */
    iic_gpio_init.Pull = GPIO_PULLUP;                 /* 上拉 */
    iic_gpio_init.Speed = GPIO_SPEED_FREQ_VERY_HIGH;  /* 快速 */
    HAL_GPIO_Init(IIC_SCL_GPIO_PORT, &iic_gpio_init); /* SCL */
    
    iic_gpio_init.Pin = IIC_SDA_GPIO_PIN;
    iic_gpio_init.Mode = GPIO_MODE_OUTPUT_OD;         /* 开漏输出 */
    HAL_GPIO_Init(IIC_SDA_GPIO_PORT, &iic_gpio_init); /* SDA */
    
    iic_stop();     /* 停止总线上所有设备 */
}

static void iic_delay(void)
{
    delay_us(2);    /* 2us的延时, 读写速度在250Khz以内 */
}


void iic_start(void)
{
    IIC_SDA(1);
    IIC_SCL(1);
    iic_delay();
    IIC_SDA(0);          /* START信号: 当SCL为高时, SDA从高变成低, 表示起始信号 */
    iic_delay();
    IIC_SCL(0);          /* 钳住I2C总线，准备发送或接收数据 */
    iic_delay(); 
}

void iic_stop(void)
{
    IIC_SDA(0);          /* STOP信号: 当SCL为高时, SDA从低变成高, 表示停止信号 */
    iic_delay();
    IIC_SCL(1);
    iic_delay();
    IIC_SDA(1);          /* 发送I2C总线结束信号 */
    iic_delay();
}

void iic_ack(void)
{
    IIC_SDA(0);     /* SCL 0 -> 1 时 SDA = 0,表示应答 */
    iic_delay();
    IIC_SCL(1);     /* 产生一个时钟 */
    iic_delay();
    IIC_SCL(0);
    iic_delay();
    IIC_SDA(1);     /* 主机释放SDA线 */
    iic_delay();
}

void iic_nack(void)
{
    IIC_SDA(1);     /* SCL 0 -> 1  时 SDA = 1,表示不应答 */
    iic_delay();
    IIC_SCL(1);     /* 产生一个时钟 */
    iic_delay();
    IIC_SCL(0);
    iic_delay();
}

uint8_t iic_wait_ack(void)
{
    uint8_t waittime = 0;
    uint8_t rack = 0;
    
    IIC_SDA(1);             /* 主机释放SDA线(此时外部器件可以拉低SDA线) */
    iic_delay();
    IIC_SCL(1);             /* SCL=1, 此时从机可以返回ACK */
    iic_delay();
    
    while(IIC_READ_SDA)     /* 等待应答 */
    {
        waittime++;
        if(waittime > 250)
        {
            iic_stop();
            rack = 1;
            break;
        }
    }
    IIC_SCL(0);             /* SCL=0, 结束ACK检查 */
    iic_delay();
    return rack;
}

void iic_send_byte(uint8_t txd)
{
    uint8_t t;
    for(t = 0; t < 8; t++)
    {
        IIC_SDA((txd & 0x80) >> 7);  /* 高位先发送 */
        iic_delay(); 
        IIC_SCL(1);
        iic_delay();
        IIC_SCL(0);
        iic_delay();
        txd <<= 1;                  /* 左移1位,用于下一次发送 */
    }
    IIC_SDA(1);                     /* 发送完成, 主机释放SDA线 */
}

uint8_t iic_read_byte(unsigned char ack)
{
    uint8_t i, receive = 0;
    
        for (i = 0; i < 8; i++ )    /* 接收1个字节数据 */
    {
        receive <<= 1;  /* 高位先输出,所以先收到的数据位要左移 */
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
        iic_nack();     /* 发送nACK */
    }
    else
    {
        iic_ack();      /* 发送ACK */
    }

    return receive;
}
