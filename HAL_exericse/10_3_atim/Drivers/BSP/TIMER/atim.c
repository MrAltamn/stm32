#include "./BSP/TIMER/atim.h"
#include "./BSP/LED/led.h"

TIM_HandleTypeDef a_timx_npwm_chy_handler;


void atim_timx_npwm_chy_init(uint16_t arr, uint16_t psc)
{
    ATIM_TIMX_NPWM_CHY_GPIO_CLK_ENABLE();
    ATIM_TIMX_NPWM_CHY_CLK_ENABLE();
    
    GPIO_InitTypeDef gpio_init_struct;
    TIM_OC_InitTypeDef timx_npwm_chy_handler;
    
    a_timx_npwm_chy_handler.Instance = ATIM_TIMX_NPWM;
    a_timx_npwm_chy_handler.Init.Prescaler = psc;
    a_timx_npwm_chy_handler.Init.CounterMode = TIM_COUNTERMODE_UP;
    a_timx_npwm_chy_handler.Init.Period = arr;
    a_timx_npwm_chy_handler.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
    a_timx_npwm_chy_handler.Init.RepetitionCounter = 0;
    HAL_TIM_PWM_Init(&a_timx_npwm_chy_handler);
    
    gpio_init_struct.Pin = ATIM_TIMX_NPWM_GPIO_PIN;
    gpio_init_struct.Mode = GPIO_MODE_AF_PP;
    gpio_init_struct.Pull = GPIO_PULLUP;
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;
    gpio_init_struct.Alternate = ATIM_TIMX_NPWM_CHY_GPIO_AF;
    HAL_GPIO_Init(ATIM_TIMX_NPWM_GPIO_PORT, &gpio_init_struct);
    
    timx_npwm_chy_handler.OCMode = TIM_OCMODE_PWM1;
    timx_npwm_chy_handler.Pulse = arr / 2;
    timx_npwm_chy_handler.OCPolarity = TIM_OCPOLARITY_HIGH;
    HAL_TIM_PWM_ConfigChannel(&a_timx_npwm_chy_handler, &timx_npwm_chy_handler, ATIM_TIMX_NPWM_CHY);
    
    HAL_NVIC_SetPriority(ATIM_TIMX_NPWM_IRQn, 1, 3);
    HAL_NVIC_EnableIRQ(ATIM_TIMX_NPWM_IRQn);
    
    __HAL_TIM_ENABLE_IT(&a_timx_npwm_chy_handler, TIM_IT_UPDATE);
    HAL_TIM_PWM_Start(&a_timx_npwm_chy_handler, ATIM_TIMX_NPWM_CHY);
    
}

static uint32_t g_npwm_remain = 0;

void atim_timx_npwm_chy_set(uint32_t npwm)
{
    if (npwm == 0) return;
    
    g_npwm_remain = npwm;
    HAL_TIM_GenerateEvent(&a_timx_npwm_chy_handler, TIM_EVENTSOURCE_UPDATE);
    __HAL_TIM_ENABLE(&a_timx_npwm_chy_handler);
}

void ATIM_TIMX_NPWM_IRQHandler(void)
{
    uint16_t npwm = 0;
    if(__HAL_TIM_GET_FLAG(&a_timx_npwm_chy_handler, TIM_FLAG_UPDATE) != RESET)
    {
        if(g_npwm_remain >= 256)
        {
            g_npwm_remain = g_npwm_remain - 256;
            npwm = 256;
        }else if(g_npwm_remain % 256)
        {
            npwm = g_npwm_remain % 256;
            g_npwm_remain = 0;
        }
        if(npwm)
        {
            ATIM_TIMX_NPWM->RCR = npwm - 1;                                         /* �����ظ������Ĵ���ֵΪnpwm-1, ��npwm������ */
            HAL_TIM_GenerateEvent(&a_timx_npwm_chy_handler, TIM_EVENTSOURCE_UPDATE); /* ����һ�θ����¼�,���ж����洦��������� */
            __HAL_TIM_ENABLE(&a_timx_npwm_chy_handler);
        }
        else
        {
            ATIM_TIMX_NPWM->CR1 &= ~(1 << 0); /* �رն�ʱ��TIMX��ʹ��HAL Disable�����PWMͨ����Ϣ���˴����� */
        }
        
        __HAL_TIM_CLEAR_IT(&a_timx_npwm_chy_handler, TIM_IT_UPDATE);  /* �����ʱ������жϱ�־λ */

    }
}

/*************************************����Ƚ�ģʽ********************************************/
TIM_HandleTypeDef g_timx_comp_pwm_handle;
void atim_timx_comp_pwm_init(uint16_t arr, uint16_t psc)
{
    TIM_OC_InitTypeDef timx_oc_comp_pwm;
    
    g_timx_comp_pwm_handle.Instance = ATIM_TIMX_COMP;                              /* ��ʱ��x */
    g_timx_comp_pwm_handle.Init.Prescaler = psc;                                   /* ��ʱ��Ԥ��Ƶ */
    g_timx_comp_pwm_handle.Init.CounterMode = TIM_COUNTERMODE_UP;                  /* �������� */
    g_timx_comp_pwm_handle.Init.Period = arr;                                      /* �Զ�װ��ֵ */
    g_timx_comp_pwm_handle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE; /* ʹ��Ӱ�ӼĴ��� */
    HAL_TIM_OC_Init(&g_timx_comp_pwm_handle);                                      /* ����Ƚϳ�ʼ�� */
    
    timx_oc_comp_pwm.OCMode = TIM_OCMODE_TOGGLE;                                   /* �Ƚ����ģʽ��תģʽ */
    timx_oc_comp_pwm.Pulse = 250-1;                                                /* ��������ȽϼĴ�����ֵ */
    timx_oc_comp_pwm.OCPolarity = TIM_OCPOLARITY_HIGH;                             /* ����Ƚϼ���Ϊ�� */
    HAL_TIM_OC_ConfigChannel(&g_timx_comp_pwm_handle, &timx_oc_comp_pwm, TIM_CHANNEL_1); /* ��ʼ����ʱ�����ͨ��1 */
    __HAL_TIM_ENABLE_OCxPRELOAD(&g_timx_comp_pwm_handle, TIM_CHANNEL_1);           /* CCR1�Ĵ���Ԥװʹ�� */
    
    timx_oc_comp_pwm.Pulse = 500;
    HAL_TIM_OC_ConfigChannel(&g_timx_comp_pwm_handle, &timx_oc_comp_pwm, TIM_CHANNEL_2); /* ��ʼ����ʱ�����ͨ��2 */
    __HAL_TIM_ENABLE_OCxPRELOAD(&g_timx_comp_pwm_handle, TIM_CHANNEL_2);           /* CCR2�Ĵ���Ԥװʹ�� */
    
    timx_oc_comp_pwm.Pulse = 750;
    HAL_TIM_OC_ConfigChannel(&g_timx_comp_pwm_handle, &timx_oc_comp_pwm, TIM_CHANNEL_3); /* ��ʼ����ʱ�����ͨ��3 */
    __HAL_TIM_ENABLE_OCxPRELOAD(&g_timx_comp_pwm_handle, TIM_CHANNEL_3);           /* CCR3�Ĵ���Ԥװʹ�� */
    
    timx_oc_comp_pwm.Pulse = 1000;
    HAL_TIM_OC_ConfigChannel(&g_timx_comp_pwm_handle, &timx_oc_comp_pwm, TIM_CHANNEL_4); /* ��ʼ����ʱ�����ͨ��4 */
    __HAL_TIM_ENABLE_OCxPRELOAD(&g_timx_comp_pwm_handle, TIM_CHANNEL_4);           /* CCR4�Ĵ���Ԥװʹ�� */
    
    HAL_TIM_OC_Start(&g_timx_comp_pwm_handle, TIM_CHANNEL_1);
    HAL_TIM_OC_Start(&g_timx_comp_pwm_handle, TIM_CHANNEL_2);
    HAL_TIM_OC_Start(&g_timx_comp_pwm_handle, TIM_CHANNEL_3);
    HAL_TIM_OC_Start(&g_timx_comp_pwm_handle, TIM_CHANNEL_4);
}

void HAL_TIM_OC_MspInit(TIM_HandleTypeDef *htim)
{
    if(htim->Instance == ATIM_TIMX_COMP)
    {
        GPIO_InitTypeDef gpio_init_struct;
       
        ATIM_TIMX_COMP_CLK_ENABLE();
        ATIM_TIMX_COMP_CH1_GPIO_CLK_ENABLE();
        ATIM_TIMX_COMP_CH2_GPIO_CLK_ENABLE();
        ATIM_TIMX_COMP_CH3_GPIO_CLK_ENABLE();
        ATIM_TIMX_COMP_CH4_GPIO_CLK_ENABLE();
        
        gpio_init_struct.Pin = ATIM_TIMX_COMP_CH1_GPIO_PIN;
        gpio_init_struct.Mode = GPIO_MODE_AF_PP;
        gpio_init_struct.Pull = GPIO_NOPULL;
        gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;
        gpio_init_struct.Alternate = ATIM_TIMX_COMP_GPIO_AF;
        HAL_GPIO_Init(ATIM_TIMX_COMP_CH1_GPIO_PORT, &gpio_init_struct);
        
        gpio_init_struct.Pin = ATIM_TIMX_COMP_CH2_GPIO_PIN;
        HAL_GPIO_Init(ATIM_TIMX_COMP_CH2_GPIO_PORT, &gpio_init_struct);
        
        gpio_init_struct.Pin = ATIM_TIMX_COMP_CH3_GPIO_PIN;
        HAL_GPIO_Init(ATIM_TIMX_COMP_CH3_GPIO_PORT, &gpio_init_struct);
        
        gpio_init_struct.Pin = ATIM_TIMX_COMP_CH4_GPIO_PIN;
        HAL_GPIO_Init(ATIM_TIMX_COMP_CH4_GPIO_PORT, &gpio_init_struct);
    }
}

/******************************************************************************/
TIM_HandleTypeDef g_timx_cplm_pwm_handle;                              /* ��ʱ��x��� */
TIM_BreakDeadTimeConfigTypeDef g_sbreak_dead_time_config = {0};        /* ����ʱ������ */

void atim_timx_cplm_pwm_init(uint16_t arr, uint16_t psc)
{
    GPIO_InitTypeDef gpio_init_struct = {0};
    TIM_OC_InitTypeDef tim_oc_cplm_pwm = {0};
    
    ATIM_TIMX_CPLM_CHY_GPIO_CLK_ENABLE();                                         /* ͨ��X��ӦIO��ʱ��ʹ�� */
    ATIM_TIMX_CPLM_CHYN_GPIO_CLK_ENABLE();                                        /* ͨ��X����ͨ����ӦIO��ʱ��ʹ�� */
    ATIM_TIMX_CPLM_BKIN_GPIO_CLK_ENABLE();                                        /* ͨ��Xɲ�������ӦIO��ʱ��ʹ�� */
    ATIM_TIMX_CPLM_CLK_ENABLE();                                                  /* TIMx ʱ��ʹ�� */
    
    gpio_init_struct.Pin = ATIM_TIMX_CPLM_CHY_GPIO_PIN;
    gpio_init_struct.Mode = GPIO_MODE_AF_PP;
    gpio_init_struct.Pull = GPIO_PULLDOWN;
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(ATIM_TIMX_CPLM_CHY_GPIO_PORT, &gpio_init_struct);
    
    gpio_init_struct.Pin = ATIM_TIMX_CPLM_CHYN_GPIO_PIN;
    HAL_GPIO_Init(ATIM_TIMX_CPLM_CHY_GPIO_PORT, &gpio_init_struct);
    
    gpio_init_struct.Pin = ATIM_TIMX_CPLM_BKIN_GPIO_PIN;
    HAL_GPIO_Init(ATIM_TIMX_CPLM_CHY_GPIO_PORT, &gpio_init_struct);
    
    
    g_timx_cplm_pwm_handle.Instance = ATIM_TIMX_CPLM;                             /* ��ʱ��x */
    g_timx_cplm_pwm_handle.Init.Prescaler = psc;                                  /* Ԥ��Ƶ */
    g_timx_cplm_pwm_handle.Init.CounterMode = TIM_COUNTERMODE_UP;                 /* �������� */
    g_timx_cplm_pwm_handle.Init.Period = arr;                                     /* Ԥװ��ֵ */
    g_timx_cplm_pwm_handle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE; /* �Զ�װ��ʹ�� */
    g_timx_cplm_pwm_handle.Init.ClockDivision = TIM_CLOCKDIVISION_DIV4;           /* CKD[1:0] = 10, tDTS = 4 * tCK_INT = Ft / 4 = 42Mhz */
    HAL_TIM_PWM_Init(&g_timx_cplm_pwm_handle);                                    /* PWM��ʼ�� */
    
    tim_oc_cplm_pwm.OCMode = TIM_OCMODE_PWM1;                                     /* PWM ģʽ1 */
    tim_oc_cplm_pwm.OCPolarity = TIM_OCPOLARITY_HIGH;                             /* OCy �ߵ�ƽ��Ч */
    tim_oc_cplm_pwm.OCNPolarity = TIM_OCNPOLARITY_HIGH;                           /* OCyN �ߵ�ƽ��Ч */
    tim_oc_cplm_pwm.OCIdleState = TIM_OCIDLESTATE_SET;                            /* ����״̬ʱͨ�������ƽ����     ��MOE=0��OCx=0 */
    tim_oc_cplm_pwm.OCNIdleState = TIM_OCNIDLESTATE_SET;                          /* ����״̬ʱ����ͨ�������ƽ���� ��MOE=0��OCxN=0*/
    HAL_TIM_PWM_ConfigChannel(&g_timx_cplm_pwm_handle, &tim_oc_cplm_pwm, ATIM_TIMX_CPLM_CHY);
    
    g_sbreak_dead_time_config.OffStateRunMode = TIM_OSSR_DISABLE;                 /* ����ģʽ�Ĺر����״̬ */
    g_sbreak_dead_time_config.OffStateIDLEMode = TIM_OSSI_DISABLE;                /* ����ģʽ�Ĺر����״̬ */
    g_sbreak_dead_time_config.LockLevel = TIM_LOCKLEVEL_OFF;                      /* ���üĴ��������� */
    g_sbreak_dead_time_config.BreakState = TIM_BREAK_ENABLE;                      /* ʹ��ɲ������ */
    g_sbreak_dead_time_config.BreakPolarity = TIM_BREAKPOLARITY_HIGH;             /* ɲ��������Ч�źż���Ϊ�� */
    g_sbreak_dead_time_config.AutomaticOutput = TIM_AUTOMATICOUTPUT_ENABLE;       /* ʹ��AOEλ������ɲ���������Զ��ָ���� */
    HAL_TIMEx_ConfigBreakDeadTime(&g_timx_cplm_pwm_handle, &g_sbreak_dead_time_config);
    
    HAL_TIM_PWM_Start(&g_timx_cplm_pwm_handle, ATIM_TIMX_CPLM_CHY);                /* OCy ���ʹ�� */
    HAL_TIMEx_PWMN_Start(&g_timx_cplm_pwm_handle, ATIM_TIMX_CPLM_CHY);             /* OCyN ���ʹ�� */
    
}

void atim_timx_cplm_pwm_set(uint16_t ccr, uint8_t dtg)
{
    g_sbreak_dead_time_config.DeadTime = dtg;
    HAL_TIMEx_ConfigBreakDeadTime(&g_timx_cplm_pwm_handle, &g_sbreak_dead_time_config);      /*��������ʱ��*/
    __HAL_TIM_MOE_ENABLE(&g_timx_cplm_pwm_handle);      /* MOE=1,ʹ������� */    
    ATIM_TIMX_CPLM_CHY_CCRY = ccr;                      /* ���ñȽϼĴ��� */
}


