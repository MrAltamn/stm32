#include "./BSP/GTIM/gtim.h"
#include "./BSP/LED/led.h"

TIM_HandleTypeDef g_timx_handler;
TIM_HandleTypeDef g_timx_pwm_chy_handler;
TIM_OC_InitTypeDef timx_pwm_chy_handler;
TIM_HandleTypeDef g_timx_cap_chy_handler;


void gtim_timx_init(uint16_t arr, uint16_t psc)
{
    GTIM_TIMX_INT_CLK_ENABLE();

    g_timx_handler.Instance = GTIM_TIMX_INT;
    g_timx_handler.Init.Prescaler = psc;
    g_timx_handler.Init.CounterMode = TIM_COUNTERMODE_UP;
    g_timx_handler.Init.Period = arr;
    HAL_TIM_Base_Init(&g_timx_handler);
    
    HAL_NVIC_SetPriority(GTIM_TIMX_INT_IRQn, 1, 3);
    HAL_NVIC_EnableIRQ(GTIM_TIMX_INT_IRQn);
    
    HAL_TIM_Base_Start_IT(&g_timx_handler);
    
}

void GTIM_TIMX_INT_IRQHandler(void)
{
    if(__HAL_TIM_GET_FLAG(&g_timx_handler, TIM_FLAG_UPDATE) != RESET) 
    { 
        LED1_TOGGLE(); 
        /* �����ʱ������жϱ�־λ */ 
        __HAL_TIM_CLEAR_IT(&g_timx_handler, TIM_IT_UPDATE); 
    }
}

/********************************************************************************/

void gtim_timx_pwm_chy_init(uint16_t arr, uint16_t psc)
{
    g_timx_pwm_chy_handler.Instance = GTIM_TIMX_PWM;
    g_timx_pwm_chy_handler.Init.Prescaler = psc;
    g_timx_pwm_chy_handler.Init.CounterMode = TIM_COUNTERMODE_UP;
    g_timx_pwm_chy_handler.Init.Period = arr;
    HAL_TIM_PWM_Init(&g_timx_pwm_chy_handler);
    
    timx_pwm_chy_handler.OCMode = TIM_OCMODE_PWM1;
    timx_pwm_chy_handler.Pulse = arr / 2;
    timx_pwm_chy_handler.OCPolarity = TIM_OCPOLARITY_LOW;
    HAL_TIM_PWM_ConfigChannel(&g_timx_pwm_chy_handler, &timx_pwm_chy_handler, GTIM_TIMX_PWM_CHY);
    HAL_TIM_PWM_Start(&g_timx_pwm_chy_handler, GTIM_TIMX_PWM_CHY);
}

void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim)
{
    if(htim->Instance == GTIM_TIMX_PWM)
    {
        GTIM_TIMX_PWM_CHY_GPIO_CLK_ENABLE();
        GTIM_TIMX_PWM_CHY_CLK_ENABLE();
        GPIO_InitTypeDef gpio_init_struct;
        
        gpio_init_struct.Pin = GTIM_TIMX_PWM_GPIO_PIN;
        gpio_init_struct.Mode = GPIO_MODE_AF_PP;
        gpio_init_struct.Pull = GPIO_PULLUP;
        gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;
        gpio_init_struct.Alternate = GTIM_TIMX_PWM_CHY_GPIO_AF;
        
        HAL_GPIO_Init(GTIM_TIMX_PWM_GPIO_PORT, &gpio_init_struct);
    }
}

/********************************************************************************/
void gtim_timx_cap_chy_init(uint32_t arr, uint16_t psc)
{
    TIM_IC_InitTypeDef timx_cap_chy_handler;
    
    g_timx_cap_chy_handler.Instance = GTIM_TIMX_CAP;
    g_timx_cap_chy_handler.Init.Prescaler = psc;
    g_timx_cap_chy_handler.Init.Period = arr;
    g_timx_cap_chy_handler.Init.CounterMode = TIM_COUNTERMODE_UP;
    HAL_TIM_IC_Init(&g_timx_cap_chy_handler);
    
    timx_cap_chy_handler.ICPolarity = TIM_ICPOLARITY_RISING;
    timx_cap_chy_handler.ICSelection = TIM_ICSELECTION_DIRECTTI;
    timx_cap_chy_handler.ICPrescaler = TIM_ICPSC_DIV1;
    timx_cap_chy_handler.ICFilter = 0;
    HAL_TIM_IC_ConfigChannel(&g_timx_cap_chy_handler, &timx_cap_chy_handler, GTIM_TIMX_CAP_CHY);
    
    __HAL_TIM_ENABLE_IT(&g_timx_cap_chy_handler, TIM_IT_UPDATE);
    HAL_TIM_IC_Start_IT(&g_timx_cap_chy_handler, GTIM_TIMX_CAP_CHY);
}

void HAL_TIM_IC_MspInit(TIM_HandleTypeDef *htim)
{
    if(htim->Instance == GTIM_TIMX_CAP)
    {
        GTIM_TIMX_CAP_CHY_CLK_ENABLE();
        GTIM_TIMX_CAP_CHY_GPIO_CLK_ENABLE();
        
        GPIO_InitTypeDef gpio_init_struct;
        gpio_init_struct.Pin = GTIM_TIMX_CAP_CHY_GPIO_PIN;
        gpio_init_struct.Mode = GPIO_MODE_AF_PP;
        gpio_init_struct.Pull = GPIO_PULLDOWN;
        gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;
        gpio_init_struct.Alternate = GTIM_TIMX_CAP_CHY_GPIO_AF;
        
        HAL_GPIO_Init(GTIM_TIMX_CAP_CHY_GPIO_PORT, &gpio_init_struct);
        
        HAL_NVIC_SetPriority(GTIM_TIMX_CAP_IRQn, 1, 3);
        HAL_NVIC_EnableIRQ(GTIM_TIMX_CAP_IRQn);
    }
}

/* ���벶��״̬(g_timxchy_cap_sta) 
 * [7] :0,û�гɹ��Ĳ���;1,�ɹ�����һ��.
 * [6] :0,��û���񵽸ߵ�ƽ;1,�Ѿ����񵽸ߵ�ƽ��.
 * [5:0]:����ߵ�ƽ������Ĵ���,������63��,���������ֵ= 63*65536+65535 = 4194303 
 * ע��:Ϊ��ͨ��,����Ĭ��ARR��CCRy����16λ�Ĵ���,����32λ�Ķ�ʱ��(��:TIM5), 
 * Ҳֻ��16λʹ�� * ��1us�ļ���Ƶ��,����ʱ��Ϊ:4194303 us, Լ4.19�� 
 * (˵��һ�£�����32λ��ʱ����˵,1us��������1,���ʱ��:4294��) 
 */ 
uint8_t g_timxchy_cap_sta = 0;                /* ���벶��״̬ */ 
uint16_t g_timxchy_cap_val = 0;               /* ���벶��ֵ */

void GTIM_TIMX_CAP_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&g_timx_cap_chy_handler);
}

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
    if((g_timxchy_cap_sta & 0x80) == 0) //��û�гɹ�����
    {
        if(g_timxchy_cap_sta & 0x40)    //�����½���
        {
            g_timxchy_cap_sta |= 0x80;  //��ǳɹ�����
            g_timxchy_cap_val = HAL_TIM_ReadCapturedValue(&g_timx_cap_chy_handler, GTIM_TIMX_CAP_CHY);
            TIM_RESET_CAPTUREPOLARITY(&g_timx_cap_chy_handler, GTIM_TIMX_CAP_CHY);
            TIM_SET_CAPTUREPOLARITY(&g_timx_cap_chy_handler, GTIM_TIMX_CAP_CHY, TIM_ICPOLARITY_RISING);
        }
        else                            //��һ�β���������
        {
            g_timxchy_cap_sta = 0;
            g_timxchy_cap_val = 0;
            g_timxchy_cap_sta |= 0x40;
            __HAL_TIM_DISABLE(&g_timx_cap_chy_handler);
            __HAL_TIM_SET_COUNTER(&g_timx_cap_chy_handler, 0);
            TIM_RESET_CAPTUREPOLARITY(&g_timx_cap_chy_handler, GTIM_TIMX_CAP_CHY);
            TIM_SET_CAPTUREPOLARITY(&g_timx_cap_chy_handler, GTIM_TIMX_CAP_CHY, TIM_ICPOLARITY_FALLING);
            __HAL_TIM_ENABLE(&g_timx_cap_chy_handler);
        }
    }
}
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if(htim->Instance == GTIM_TIMX_CAP)
    {
        if((g_timxchy_cap_sta & 0x80) == 0)
        {
            if(g_timxchy_cap_sta & 0x40)   //����������
            {
                if((g_timxchy_cap_sta & 0x3F) == 0x3F) //���������
                {
                    TIM_RESET_CAPTUREPOLARITY(&g_timx_cap_chy_handler, GTIM_TIMX_CAP_CHY);
                    TIM_SET_CAPTUREPOLARITY(&g_timx_cap_chy_handler, GTIM_TIMX_CAP_CHY, TIM_ICPOLARITY_RISING);
                    g_timxchy_cap_sta |= 0x80;  //��ǳɹ�����
                    g_timxchy_cap_val = 0xFFFF;
                }
                else{
                    g_timxchy_cap_sta++;
                }
            }
        }
    }
}



