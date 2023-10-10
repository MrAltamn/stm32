#include "./BSP/TIMER/atim.h"
#include "./BSP/LED/led.h"

//TIM_HandleTypeDef a_timx_npwm_chy_handler;


//void atim_timx_npwm_chy_init(uint16_t arr, uint16_t psc)
//{
//    ATIM_TIMX_NPWM_CHY_GPIO_CLK_ENABLE();
//    ATIM_TIMX_NPWM_CHY_CLK_ENABLE();
//    
//    GPIO_InitTypeDef gpio_init_struct;
//    TIM_OC_InitTypeDef timx_npwm_chy_handler;
//    
//    a_timx_npwm_chy_handler.Instance = ATIM_TIMX_NPWM;
//    a_timx_npwm_chy_handler.Init.Prescaler = psc;
//    a_timx_npwm_chy_handler.Init.CounterMode = TIM_COUNTERMODE_UP;
//    a_timx_npwm_chy_handler.Init.Period = arr;
//    a_timx_npwm_chy_handler.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
//    a_timx_npwm_chy_handler.Init.RepetitionCounter = 0;
//    HAL_TIM_PWM_Init(&a_timx_npwm_chy_handler);
//    
//    gpio_init_struct.Pin = ATIM_TIMX_NPWM_GPIO_PIN;
//    gpio_init_struct.Mode = GPIO_MODE_AF_PP;
//    gpio_init_struct.Pull = GPIO_PULLUP;
//    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;
//    gpio_init_struct.Alternate = ATIM_TIMX_NPWM_CHY_GPIO_AF;
//    HAL_GPIO_Init(ATIM_TIMX_NPWM_GPIO_PORT, &gpio_init_struct);
//    
//    timx_npwm_chy_handler.OCMode = TIM_OCMODE_PWM1;
//    timx_npwm_chy_handler.Pulse = arr / 2;
//    timx_npwm_chy_handler.OCPolarity = TIM_OCPOLARITY_HIGH;
//    HAL_TIM_PWM_ConfigChannel(&a_timx_npwm_chy_handler, &timx_npwm_chy_handler, ATIM_TIMX_NPWM_CHY);
//    
//    HAL_NVIC_SetPriority(ATIM_TIMX_NPWM_IRQn, 1, 3);
//    HAL_NVIC_EnableIRQ(ATIM_TIMX_NPWM_IRQn);
//    
//    __HAL_TIM_ENABLE_IT(&a_timx_npwm_chy_handler, TIM_IT_UPDATE);
//    HAL_TIM_PWM_Start(&a_timx_npwm_chy_handler, ATIM_TIMX_NPWM_CHY);
//    
//}

//static uint32_t g_npwm_remain = 0;

//void atim_timx_npwm_chy_set(uint32_t npwm)
//{
//    if (npwm == 0) return;
//    
//    g_npwm_remain = npwm;
//    HAL_TIM_GenerateEvent(&a_timx_npwm_chy_handler, TIM_EVENTSOURCE_UPDATE);
//    __HAL_TIM_ENABLE(&a_timx_npwm_chy_handler);
//}

//void ATIM_TIMX_NPWM_IRQHandler(void)
//{
//    uint16_t npwm = 0;
//    if(__HAL_TIM_GET_FLAG(&a_timx_npwm_chy_handler, TIM_FLAG_UPDATE) != RESET)
//    {
//        if(g_npwm_remain >= 256)
//        {
//            g_npwm_remain = g_npwm_remain - 256;
//            npwm = 256;
//        }else if(g_npwm_remain % 256)
//        {
//            npwm = g_npwm_remain % 256;
//            g_npwm_remain = 0;
//        }
//        if(npwm)
//        {
//            ATIM_TIMX_NPWM->RCR = npwm - 1;                                         /* 设置重复计数寄存器值为npwm-1, 即npwm个脉冲 */
//            HAL_TIM_GenerateEvent(&a_timx_npwm_chy_handler, TIM_EVENTSOURCE_UPDATE); /* 产生一次更新事件,在中断里面处理脉冲输出 */
//            __HAL_TIM_ENABLE(&a_timx_npwm_chy_handler);
//        }
//        else
//        {
//            ATIM_TIMX_NPWM->CR1 &= ~(1 << 0); /* 关闭定时器TIMX，使用HAL Disable会清除PWM通道信息，此处不用 */
//        }
//        
//        __HAL_TIM_CLEAR_IT(&a_timx_npwm_chy_handler, TIM_IT_UPDATE);  /* 清除定时器溢出中断标志位 */

//    }
//}

/*************************************输出比较模式********************************************/
//TIM_HandleTypeDef g_timx_comp_pwm_handle;
//void atim_timx_comp_pwm_init(uint16_t arr, uint16_t psc)
//{
//    TIM_OC_InitTypeDef timx_oc_comp_pwm;
//    
//    g_timx_comp_pwm_handle.Instance = ATIM_TIMX_COMP;                              /* 定时器x */
//    g_timx_comp_pwm_handle.Init.Prescaler = psc;                                   /* 定时器预分频 */
//    g_timx_comp_pwm_handle.Init.CounterMode = TIM_COUNTERMODE_UP;                  /* 递增计数 */
//    g_timx_comp_pwm_handle.Init.Period = arr;                                      /* 自动装载值 */
//    g_timx_comp_pwm_handle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE; /* 使能影子寄存器 */
//    HAL_TIM_OC_Init(&g_timx_comp_pwm_handle);                                      /* 输出比较初始化 */
//    
//    timx_oc_comp_pwm.OCMode = TIM_OCMODE_TOGGLE;                                   /* 比较输出模式翻转模式 */
//    timx_oc_comp_pwm.Pulse = 250-1;                                                /* 设置输出比较寄存器的值 */
//    timx_oc_comp_pwm.OCPolarity = TIM_OCPOLARITY_HIGH;                             /* 输出比较极性为高 */
//    HAL_TIM_OC_ConfigChannel(&g_timx_comp_pwm_handle, &timx_oc_comp_pwm, TIM_CHANNEL_1); /* 初始化定时器输出通道1 */
//    __HAL_TIM_ENABLE_OCxPRELOAD(&g_timx_comp_pwm_handle, TIM_CHANNEL_1);           /* CCR1寄存器预装使能 */
//    
//    timx_oc_comp_pwm.Pulse = 500;
//    HAL_TIM_OC_ConfigChannel(&g_timx_comp_pwm_handle, &timx_oc_comp_pwm, TIM_CHANNEL_2); /* 初始化定时器输出通道2 */
//    __HAL_TIM_ENABLE_OCxPRELOAD(&g_timx_comp_pwm_handle, TIM_CHANNEL_2);           /* CCR2寄存器预装使能 */
//    
//    timx_oc_comp_pwm.Pulse = 750;
//    HAL_TIM_OC_ConfigChannel(&g_timx_comp_pwm_handle, &timx_oc_comp_pwm, TIM_CHANNEL_3); /* 初始化定时器输出通道3 */
//    __HAL_TIM_ENABLE_OCxPRELOAD(&g_timx_comp_pwm_handle, TIM_CHANNEL_3);           /* CCR3寄存器预装使能 */
//    
//    timx_oc_comp_pwm.Pulse = 1000;
//    HAL_TIM_OC_ConfigChannel(&g_timx_comp_pwm_handle, &timx_oc_comp_pwm, TIM_CHANNEL_4); /* 初始化定时器输出通道4 */
//    __HAL_TIM_ENABLE_OCxPRELOAD(&g_timx_comp_pwm_handle, TIM_CHANNEL_4);           /* CCR4寄存器预装使能 */
//    
//    HAL_TIM_OC_Start(&g_timx_comp_pwm_handle, TIM_CHANNEL_1);
//    HAL_TIM_OC_Start(&g_timx_comp_pwm_handle, TIM_CHANNEL_2);
//    HAL_TIM_OC_Start(&g_timx_comp_pwm_handle, TIM_CHANNEL_3);
//    HAL_TIM_OC_Start(&g_timx_comp_pwm_handle, TIM_CHANNEL_4);
//}

//void HAL_TIM_OC_MspInit(TIM_HandleTypeDef *htim)
//{
//    if(htim->Instance == ATIM_TIMX_COMP)
//    {
//        GPIO_InitTypeDef gpio_init_struct;
//       
//        ATIM_TIMX_COMP_CLK_ENABLE();
//        ATIM_TIMX_COMP_CH1_GPIO_CLK_ENABLE();
//        ATIM_TIMX_COMP_CH2_GPIO_CLK_ENABLE();
//        ATIM_TIMX_COMP_CH3_GPIO_CLK_ENABLE();
//        ATIM_TIMX_COMP_CH4_GPIO_CLK_ENABLE();
//        
//        gpio_init_struct.Pin = ATIM_TIMX_COMP_CH1_GPIO_PIN;
//        gpio_init_struct.Mode = GPIO_MODE_AF_PP;
//        gpio_init_struct.Pull = GPIO_NOPULL;
//        gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;
//        gpio_init_struct.Alternate = ATIM_TIMX_COMP_GPIO_AF;
//        HAL_GPIO_Init(ATIM_TIMX_COMP_CH1_GPIO_PORT, &gpio_init_struct);
//        
//        gpio_init_struct.Pin = ATIM_TIMX_COMP_CH2_GPIO_PIN;
//        HAL_GPIO_Init(ATIM_TIMX_COMP_CH2_GPIO_PORT, &gpio_init_struct);
//        
//        gpio_init_struct.Pin = ATIM_TIMX_COMP_CH3_GPIO_PIN;
//        HAL_GPIO_Init(ATIM_TIMX_COMP_CH3_GPIO_PORT, &gpio_init_struct);
//        
//        gpio_init_struct.Pin = ATIM_TIMX_COMP_CH4_GPIO_PIN;
//        HAL_GPIO_Init(ATIM_TIMX_COMP_CH4_GPIO_PORT, &gpio_init_struct);
//    }
//}

///******************************************************************************/
//TIM_HandleTypeDef g_timx_cplm_pwm_handle;                              /* 定时器x句柄 */
//TIM_BreakDeadTimeConfigTypeDef g_sbreak_dead_time_config = {0};        /* 死区时间设置 */

//void atim_timx_cplm_pwm_init(uint16_t arr, uint16_t psc)
//{
//    GPIO_InitTypeDef gpio_init_struct = {0};
//    TIM_OC_InitTypeDef tim_oc_cplm_pwm = {0};
//    
//    ATIM_TIMX_CPLM_CHY_GPIO_CLK_ENABLE();                                         /* 通道X对应IO口时钟使能 */
//    ATIM_TIMX_CPLM_CHYN_GPIO_CLK_ENABLE();                                        /* 通道X互补通道对应IO口时钟使能 */
//    ATIM_TIMX_CPLM_BKIN_GPIO_CLK_ENABLE();                                        /* 通道X刹车输入对应IO口时钟使能 */
//    ATIM_TIMX_CPLM_CLK_ENABLE();                                                  /* TIMx 时钟使能 */
//    
//    gpio_init_struct.Pin = ATIM_TIMX_CPLM_CHY_GPIO_PIN;
//    gpio_init_struct.Mode = GPIO_MODE_AF_PP;
//    gpio_init_struct.Pull = GPIO_PULLDOWN;
//    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;
//    HAL_GPIO_Init(ATIM_TIMX_CPLM_CHY_GPIO_PORT, &gpio_init_struct);
//    
//    gpio_init_struct.Pin = ATIM_TIMX_CPLM_CHYN_GPIO_PIN;
//    HAL_GPIO_Init(ATIM_TIMX_CPLM_CHY_GPIO_PORT, &gpio_init_struct);
//    
//    gpio_init_struct.Pin = ATIM_TIMX_CPLM_BKIN_GPIO_PIN;
//    HAL_GPIO_Init(ATIM_TIMX_CPLM_CHY_GPIO_PORT, &gpio_init_struct);
//    
//    
//    g_timx_cplm_pwm_handle.Instance = ATIM_TIMX_CPLM;                             /* 定时器x */
//    g_timx_cplm_pwm_handle.Init.Prescaler = psc;                                  /* 预分频 */
//    g_timx_cplm_pwm_handle.Init.CounterMode = TIM_COUNTERMODE_UP;                 /* 递增计数 */
//    g_timx_cplm_pwm_handle.Init.Period = arr;                                     /* 预装载值 */
//    g_timx_cplm_pwm_handle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE; /* 自动装载使能 */
//    g_timx_cplm_pwm_handle.Init.ClockDivision = TIM_CLOCKDIVISION_DIV4;           /* CKD[1:0] = 10, tDTS = 4 * tCK_INT = Ft / 4 = 42Mhz */
//    HAL_TIM_PWM_Init(&g_timx_cplm_pwm_handle);                                    /* PWM初始化 */
//    
//    tim_oc_cplm_pwm.OCMode = TIM_OCMODE_PWM1;                                     /* PWM 模式1 */
//    tim_oc_cplm_pwm.OCPolarity = TIM_OCPOLARITY_HIGH;                             /* OCy 高电平有效 */
//    tim_oc_cplm_pwm.OCNPolarity = TIM_OCNPOLARITY_HIGH;                           /* OCyN 高电平有效 */
//    tim_oc_cplm_pwm.OCIdleState = TIM_OCIDLESTATE_SET;                            /* 空闲状态时通道输出电平设置     当MOE=0，OCx=0 */
//    tim_oc_cplm_pwm.OCNIdleState = TIM_OCNIDLESTATE_SET;                          /* 空闲状态时互补通道输出电平设置 当MOE=0，OCxN=0*/
//    HAL_TIM_PWM_ConfigChannel(&g_timx_cplm_pwm_handle, &tim_oc_cplm_pwm, ATIM_TIMX_CPLM_CHY);
//    
//    g_sbreak_dead_time_config.OffStateRunMode = TIM_OSSR_DISABLE;                 /* 运行模式的关闭输出状态 */
//    g_sbreak_dead_time_config.OffStateIDLEMode = TIM_OSSI_DISABLE;                /* 空闲模式的关闭输出状态 */
//    g_sbreak_dead_time_config.LockLevel = TIM_LOCKLEVEL_OFF;                      /* 不用寄存器锁功能 */
//    g_sbreak_dead_time_config.BreakState = TIM_BREAK_ENABLE;                      /* 使能刹车输入 */
//    g_sbreak_dead_time_config.BreakPolarity = TIM_BREAKPOLARITY_HIGH;             /* 刹车输入有效信号极性为高 */
//    g_sbreak_dead_time_config.AutomaticOutput = TIM_AUTOMATICOUTPUT_ENABLE;       /* 使能AOE位，允许刹车结束后自动恢复输出 */
//    HAL_TIMEx_ConfigBreakDeadTime(&g_timx_cplm_pwm_handle, &g_sbreak_dead_time_config);
//    
//    HAL_TIM_PWM_Start(&g_timx_cplm_pwm_handle, ATIM_TIMX_CPLM_CHY);                /* OCy 输出使能 */
//    HAL_TIMEx_PWMN_Start(&g_timx_cplm_pwm_handle, ATIM_TIMX_CPLM_CHY);             /* OCyN 输出使能 */
//    
//}

//void atim_timx_cplm_pwm_set(uint16_t ccr, uint8_t dtg)
//{
//    g_sbreak_dead_time_config.DeadTime = dtg;
//    HAL_TIMEx_ConfigBreakDeadTime(&g_timx_cplm_pwm_handle, &g_sbreak_dead_time_config);      /*重设死区时间*/
//    __HAL_TIM_MOE_ENABLE(&g_timx_cplm_pwm_handle);      /* MOE=1,使能主输出 */    
//    ATIM_TIMX_CPLM_CHY_CCRY = ccr;                      /* 设置比较寄存器 */
//}

/******************************************************************************/
TIM_HandleTypeDef g_timx_pwmin_chy_handle;                              /* 定时器x句柄 */

/* PWM输入状态(g_timxchy_cap_sta)
 * 0,没有成功捕获.
 * 1,已经成功捕获了
 */
uint8_t g_timxchy_pwmin_sta  = 0;   /* PWM输入状态 */
uint16_t g_timxchy_pwmin_psc  = 0;  /* PWM输入分频系数 */
uint32_t g_timxchy_pwmin_hval = 0;  /* PWM的高电平脉宽 */
uint32_t g_timxchy_pwmin_cval = 0;  /* PWM的周期宽度 */

void atim_timx_pwmin_chy_init(void)
{
    GPIO_InitTypeDef       gpio_init_struct = {0};
    TIM_SlaveConfigTypeDef slave_config = {0};
    TIM_IC_InitTypeDef     tim_ic_pwmin_chy = {0};
    
    /* 开启 TIMx和输入通道的 GPIO时钟，配置该 IO口的复用功能输入 */
    ATIM_TIMX_PWMIN_CHY_GPIO_CLK_ENABLE();                                        /* 输入通道GPIO使能 */
    ATIM_TIMX_PWMIN_CHY_CLK_ENABLE();                                             /* TIM8 定时器使能 */
    
    gpio_init_struct.Pin = ATIM_TIMX_PWMIN_CHY_GPIO_PIN;
    gpio_init_struct.Mode = GPIO_MODE_AF_PP;
    gpio_init_struct.Pull = GPIO_PULLDOWN;
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;
    gpio_init_struct.Alternate = ATIM_TIMX_PWMIN_CHY_GPIO_AF;
    HAL_GPIO_Init(ATIM_TIMX_PWMIN_CHY_GPIO_PORT, &gpio_init_struct);
    
    /* ）初始化 TIMx，设置 TIMx的 ARR和 PSC等参数 */
    g_timx_pwmin_chy_handle.Instance = ATIM_TIMX_PWMIN;                            /* 定时器8 */
    g_timx_pwmin_chy_handle.Init.Prescaler = 0;                                   /* 定时器预分频器 */
    g_timx_pwmin_chy_handle.Init.CounterMode = TIM_COUNTERMODE_UP;                /* 递增计数 */
    g_timx_pwmin_chy_handle.Init.Period = 65535;                                  /* 自动重装载值 */
    HAL_TIM_IC_Init(&g_timx_pwmin_chy_handle);
    
    /* 从模式配置 IT1触发更新 */
    slave_config.SlaveMode = TIM_SLAVEMODE_RESET;                                 /* 从模式：复位模式 */
    slave_config.InputTrigger = TIM_TS_TI1FP1;                                    /* 定时器输入触发源： TI1FP1 */
    slave_config.TriggerPolarity = TIM_INPUTCHANNELPOLARITY_RISING;               /* 上升沿检测 */
    slave_config.TriggerFilter = 0;                                               /* 不滤波 */
    HAL_TIM_SlaveConfigSynchro(&g_timx_pwmin_chy_handle, &slave_config);
    
    /* IC1捕获：上升沿触发TI1FP1 */
    tim_ic_pwmin_chy.ICPolarity = TIM_INPUTCHANNELPOLARITY_RISING;                /* 边缘检测上升沿检测 */
    tim_ic_pwmin_chy.ICPrescaler = TIM_ICPSC_DIV1;                                /* 不分频 */
    tim_ic_pwmin_chy.ICSelection = TIM_ICSELECTION_DIRECTTI;                      /* 选择输入端IC1 映射到TI1 */
    tim_ic_pwmin_chy.ICFilter = 0;                                                /* 不滤波 */
    HAL_TIM_IC_ConfigChannel(&g_timx_pwmin_chy_handle, &tim_ic_pwmin_chy, TIM_CHANNEL_1);
    
    /* IC2捕获：上升沿触发TI1FP2 */
    tim_ic_pwmin_chy.ICSelection = TIM_ICSELECTION_INDIRECTTI;                    /* 选择输入端IC2 映射到TI1*/
    tim_ic_pwmin_chy.ICPolarity = TIM_INPUTCHANNELPOLARITY_FALLING;               /* 边缘检测下降沿检测*/
    HAL_TIM_IC_ConfigChannel(&g_timx_pwmin_chy_handle, &tim_ic_pwmin_chy, TIM_CHANNEL_2);
    
    /* 使能定时器更新中断，开启捕获功能，配置定时器 中断优先级 */
    HAL_NVIC_EnableIRQ(ATIM_TIMX_PWMIN_IRQn);                                 /* 使能定时器中断 */
    HAL_NVIC_SetPriority(ATIM_TIMX_PWMIN_IRQn, 1, 3);                         /* 设置中断优先级， 抢占优先级1， 子优先级3 */
    
    /* TIM1/TIM8有独立的输入捕获中断服务函数 */
    if ( ATIM_TIMX_PWMIN == TIM1 || ATIM_TIMX_PWMIN == TIM8)
    {
        HAL_NVIC_SetPriority(ATIM_TIMX_PWMIN_CC_IRQn, 1, 3);        /* 设置中断优先级，抢占优先级1，子优先级3 */
        HAL_NVIC_EnableIRQ(ATIM_TIMX_PWMIN_CC_IRQn);                /* 开启TIMx中断 */
    }
    
    __HAL_TIM_ENABLE_IT(&g_timx_pwmin_chy_handle ,TIM_IT_UPDATE);                 /* 使能定时器更新中断 */
    HAL_TIM_IC_Start_IT(&g_timx_pwmin_chy_handle, TIM_CHANNEL_1);                 /* 开启通道1捕获功能并使能捕获中断 */
    HAL_TIM_IC_Start_IT(&g_timx_pwmin_chy_handle, TIM_CHANNEL_2);                 /* 开启通道2捕获功能并使能捕获中断 */
}

/**
 * @brief       定时器TIMX PWM输入模式 重新启动捕获
 * @param       无
 * @retval      无
 */
void atim_timx_pwmin_chy_restart(void)
{
    sys_intx_disable();                                             /* 关闭中断 */

    g_timxchy_pwmin_sta = 0;                                        /* 清零状态,重新开始检测 */
    g_timxchy_pwmin_psc = 0;                                        /* 分频系数清零 */

    __HAL_TIM_SET_PRESCALER(&g_timx_pwmin_chy_handle, 0);           /* 以最大的计数频率采集,以得到最好的精度 */
    __HAL_TIM_SET_COUNTER(&g_timx_pwmin_chy_handle, 0);             /* 计数器清零 */
    
    __HAL_TIM_ENABLE_IT(&g_timx_pwmin_chy_handle, TIM_IT_CC1);      /* 使能通道1捕获中断 */
    __HAL_TIM_ENABLE_IT(&g_timx_pwmin_chy_handle, TIM_IT_UPDATE);   /* 使能溢出中断 */
    __HAL_TIM_ENABLE(&g_timx_pwmin_chy_handle);                     /* 使能定时器TIMX */

    __HAL_TIM_CLEAR_FLAG(&g_timx_pwmin_chy_handle, TIM_FLAG_CC1);   /* 清零捕获/比较1中断标志 */
    __HAL_TIM_CLEAR_FLAG(&g_timx_pwmin_chy_handle, TIM_FLAG_CC2);   /* 清零捕获/比较2中断标志 */
    __HAL_TIM_CLEAR_FLAG(&g_timx_pwmin_chy_handle, TIM_FLAG_UPDATE);/* 清零更新中断标志 */

    sys_intx_enable();                                              /* 打开中断 */
}

static void atim_timx_pwmin_chy_process(void)
{
    static uint8_t sflag = 0;               /* 启动PWMIN输入检测标志 */

    if (g_timxchy_pwmin_sta)
    {
        g_timxchy_pwmin_psc = 0;
        __HAL_TIM_CLEAR_FLAG(&g_timx_pwmin_chy_handle, TIM_FLAG_CC1);   /* 清零捕获/比较1中断标志 */
        __HAL_TIM_CLEAR_FLAG(&g_timx_pwmin_chy_handle, TIM_FLAG_CC2);   /* 清零捕获/比较2中断标志 */
        __HAL_TIM_CLEAR_FLAG(&g_timx_pwmin_chy_handle, TIM_FLAG_UPDATE);/* 清零更新中断标志 */
        __HAL_TIM_SET_COUNTER(&g_timx_pwmin_chy_handle, 0);             /* 计数器清零 */
        return ;
    }

    if (__HAL_TIM_GET_FLAG(&g_timx_pwmin_chy_handle, TIM_FLAG_UPDATE))         /* 发生了溢出中断 */
    { 
        __HAL_TIM_CLEAR_FLAG(&g_timx_pwmin_chy_handle, TIM_FLAG_UPDATE);       /* 清除溢出中断标记 */

        if (__HAL_TIM_GET_FLAG(&g_timx_pwmin_chy_handle, TIM_FLAG_CC1) == 0)   /* 没有发生周期捕获中断,且捕获未完成 */
        {
            sflag = 0;
            if (g_timxchy_pwmin_psc == 0)   /* 从0 到 1 */
            {
                g_timxchy_pwmin_psc ++;
            }
            else
            {
                if (g_timxchy_pwmin_psc == 65535)               /* 已经最大了,可能是无输入状态 */
                {
                    g_timxchy_pwmin_psc = 0;                    /* 重新恢复不分频 */
                }
                else if (g_timxchy_pwmin_psc > 32767)           /* 不能倍增了 */
                {
                    g_timxchy_pwmin_psc = 65535;                /* 直接等于最大分频系数 */
                }
                else
                {
                    g_timxchy_pwmin_psc += g_timxchy_pwmin_psc; /* 倍增 */
                }
            }

            __HAL_TIM_SET_PRESCALER(&g_timx_pwmin_chy_handle, g_timxchy_pwmin_psc); /* 设置定时器预分频系数 */
            __HAL_TIM_SET_COUNTER(&g_timx_pwmin_chy_handle, 0);                     /* 计数器清零 */
            __HAL_TIM_CLEAR_FLAG(&g_timx_pwmin_chy_handle, TIM_FLAG_CC1);           /* 清零捕获/比较1中断标志 */
            __HAL_TIM_CLEAR_FLAG(&g_timx_pwmin_chy_handle, TIM_FLAG_CC2);           /* 清零捕获/比较2中断标志 */
            __HAL_TIM_CLEAR_FLAG(&g_timx_pwmin_chy_handle, TIM_FLAG_UPDATE);        /* 清零更新中断标志 */
            return ;
        }
    }

    if (sflag == 0)   /* 第一次采集到捕获中断 */
    {
        if (__HAL_TIM_GET_FLAG(&g_timx_pwmin_chy_handle, TIM_FLAG_CC1))   /* 检测到了第一次周期捕获中断 */
        { 
            sflag = 1;              /* 标记第一次周期已经捕获, 第二次周期捕获可以开始了 */
        }
        
        __HAL_TIM_CLEAR_FLAG(&g_timx_pwmin_chy_handle, TIM_FLAG_CC1);           /* 清零捕获/比较1中断标志 */
        __HAL_TIM_CLEAR_FLAG(&g_timx_pwmin_chy_handle, TIM_FLAG_CC2);           /* 清零捕获/比较2中断标志 */
        __HAL_TIM_CLEAR_FLAG(&g_timx_pwmin_chy_handle, TIM_FLAG_UPDATE);        /* 清零更新中断标志 */
        return ;                    /* 完成此次操作 */
    }

    if (g_timxchy_pwmin_sta == 0)   /* 还没有成功捕获 */
    {
        if (__HAL_TIM_GET_FLAG(&g_timx_pwmin_chy_handle, TIM_FLAG_CC1))         /* 检测到了周期捕获中断 */
        {
            g_timxchy_pwmin_hval = HAL_TIM_ReadCapturedValue(&g_timx_pwmin_chy_handle, TIM_CHANNEL_2) + 1; /* 高定平脉宽捕获值 */
            g_timxchy_pwmin_cval = HAL_TIM_ReadCapturedValue(&g_timx_pwmin_chy_handle, TIM_CHANNEL_1) + 1; /* 周期捕获值 */

            if (g_timxchy_pwmin_hval < g_timxchy_pwmin_cval)    /* 高电平脉宽必定小于周期长度 */
            {
                g_timxchy_pwmin_sta = 1;                        /* 标记捕获成功 */

                g_timxchy_pwmin_psc = ATIM_TIMX_PWMIN->PSC;     /* 获取PWM输入分频系数 */
                
                if (g_timxchy_pwmin_psc == 0)                   /* 分频系数为0的时候, 修正读取数据 */
                {
                    g_timxchy_pwmin_hval++;                     /* 修正系数为1, 加1 */
                    g_timxchy_pwmin_cval++;                     /* 修正系数为1, 加1 */
                }

                sflag = 0;
                /* 每次捕获PWM输入成功后, 停止捕获, 避免频繁中断影响系统正常代码运行 */
                ATIM_TIMX_PWMIN->CR1  &= ~(1 << 0);                             /* 关闭定时器TIMX */
                __HAL_TIM_DISABLE_IT(&g_timx_pwmin_chy_handle, TIM_IT_CC1);     /* 使能通道1捕获中断 */
                __HAL_TIM_DISABLE_IT(&g_timx_pwmin_chy_handle, TIM_IT_CC2);     /* 使能通道2捕获中断 */
                __HAL_TIM_DISABLE_IT(&g_timx_pwmin_chy_handle, TIM_IT_UPDATE);  /* 使能溢出中断 */

                __HAL_TIM_CLEAR_FLAG(&g_timx_pwmin_chy_handle, TIM_FLAG_CC1);   /* 清零捕获/比较1中断标志 */
                __HAL_TIM_CLEAR_FLAG(&g_timx_pwmin_chy_handle, TIM_FLAG_CC2);   /* 清零捕获/比较2中断标志 */
                __HAL_TIM_CLEAR_FLAG(&g_timx_pwmin_chy_handle, TIM_FLAG_UPDATE);/* 清零更新中断标志 */
            }
            else
            {
                atim_timx_pwmin_chy_restart();
            }
        }
    }
    
    /* 清除捕获/比较1中断标志\捕获/比较2中断标志/更新中断标志 */
    __HAL_TIM_CLEAR_FLAG(&g_timx_pwmin_chy_handle, TIM_FLAG_CC1);
    __HAL_TIM_CLEAR_FLAG(&g_timx_pwmin_chy_handle, TIM_FLAG_CC2);
    __HAL_TIM_CLEAR_FLAG(&g_timx_pwmin_chy_handle, TIM_FLAG_UPDATE);
}






/**
 * @brief       定时器TIMX 更新/溢出 中断服务函数
 *   @note      TIM1/TIM8的这个函数仅用于更新/溢出中断服务,捕获在另外一个函数!
 *              其他普通定时器则更新/溢出/捕获,都在这个函数里面处理!
 */
void ATIM_TIMX_PWMIN_IRQHandler(void)
{
    atim_timx_pwmin_chy_process();
}

/**
 * @brief       定时器TIMX 输入捕获 中断服务函数
 *   @note      仅TIM1/TIM8有这个函数,其他普通定时器没有这个中断服务函数!
 */
void ATIM_TIMX_PWMIN_CC_IRQHandler(void)
{
    atim_timx_pwmin_chy_process();
}
