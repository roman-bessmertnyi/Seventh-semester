#include "timer_lib.h"

void SetSysClockToHSE(void)
{
	ErrorStatus HSEStartUpStatus;
	/* SYSCLK, HCLK, PCLK2 and PCLK1 configuration -----------------------------*/
	/* RCC system reset(for debug purpose) */
	RCC_DeInit();

	/* Enable HSE */
	RCC_HSEConfig( RCC_HSE_ON);

	/* Wait till HSE is ready */
	HSEStartUpStatus = RCC_WaitForHSEStartUp();

	if (HSEStartUpStatus == SUCCESS)
	{
		/* HCLK = SYSCLK */
		RCC_HCLKConfig( RCC_SYSCLK_Div1);

		/* PCLK2 = HCLK */
		RCC_PCLK2Config( RCC_HCLK_Div1);

		/* PCLK1 = HCLK */
		RCC_PCLK1Config(RCC_HCLK_Div1);

		/* Select HSE as system clock source */
		RCC_SYSCLKConfig( RCC_SYSCLKSource_HSE);

		/* Wait till PLL is used as system clock source */
		while (RCC_GetSYSCLKSource() != 0x04)
		{
		}
	}
	else
	{ /* If HSE fails to start-up, the application will have wrong clock configuration.
	 User can add here some code to deal with this error */

		/* Go to infinite loop */
		while (1)
		{
		}
	}
}

void SetSysClockTo72(void)
{
    ErrorStatus HSEStartUpStatus;
    /* SYSCLK, HCLK, PCLK2 and PCLK1 configuration -----------------------------*/
    /* RCC system reset(for debug purpose) */
    RCC_DeInit();
 
    /* Enable HSE */
    RCC_HSEConfig( RCC_HSE_ON);
 
    /* Wait till HSE is ready */
    HSEStartUpStatus = RCC_WaitForHSEStartUp();
 
    if (HSEStartUpStatus == SUCCESS)
    {
        /* Enable Prefetch Buffer */
        //FLASH_PrefetchBufferCmd( FLASH_PrefetchBuffer_Enable);
 
        /* Flash 2 wait state */
        //FLASH_SetLatency( FLASH_Latency_2);
 
        /* HCLK = SYSCLK */
        RCC_HCLKConfig( RCC_SYSCLK_Div1);
 
        /* PCLK2 = HCLK */
        RCC_PCLK2Config( RCC_HCLK_Div1);
 
        /* PCLK1 = HCLK/2 */
        RCC_PCLK1Config( RCC_HCLK_Div2);
 
        /* PLLCLK = 8MHz * 9 = 72 MHz */
        RCC_PLLConfig(0x00010000, RCC_PLLMul_9);
 
        /* Enable PLL */
        RCC_PLLCmd( ENABLE);
 
        /* Wait till PLL is ready */
        while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
        {
        }
 
        /* Select PLL as system clock source */
        RCC_SYSCLKConfig( RCC_SYSCLKSource_PLLCLK);
 
        /* Wait till PLL is used as system clock source */
        while (RCC_GetSYSCLKSource() != 0x08)
        {
        }
    }
    else
    { /* If HSE fails to start-up, the application will have wrong clock configuration.
     User can add here some code to deal with this error */
 
        /* Go to infinite loop */
        while (1)
        {
        }
    }
}

void TIMER2_input_init_A2(int prescaler) {
 
    GPIO_InitTypeDef gpio_cfg;
    GPIO_StructInit(&gpio_cfg);
 
    /* Timer TIM2, channel 1 */
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
      //gpio_cfg.GPIO_Mode = GPIO_Mode_IN_FLOATING;
      gpio_cfg.GPIO_Mode = GPIO_Mode_IPU;
      gpio_cfg.GPIO_Pin = GPIO_Pin_1;
      GPIO_Init(GPIOA, &gpio_cfg);
 
      /* Timer TIM2 enable clock */
      RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
 
      /* Timer TIM2 settings */
      TIM_TimeBaseInitTypeDef timer_base;
      TIM_TimeBaseStructInit(&timer_base);
      timer_base.TIM_Prescaler = prescaler;
      TIM_TimeBaseInit(TIM2, &timer_base);
 
      /* Signal capture settings:
       - Channel: 1
       - Count: Up
       - Source: Input
       - Divider: Disable
       - Filter: Disable */
      TIM_ICInitTypeDef timer_ic;
      timer_ic.TIM_Channel = TIM_Channel_2;
      //timer_ic.TIM_ICPolarity = TIM_ICPolarity_BothEdge; # !!! BothEdge not supported
      timer_ic.TIM_ICPolarity = TIM_ICPolarity_Rising;
      timer_ic.TIM_ICSelection = TIM_ICSelection_DirectTI;
      timer_ic.TIM_ICPrescaler = TIM_ICPSC_DIV1;
      timer_ic.TIM_ICFilter = 5;
      TIM_ICInit(TIM2, &timer_ic);
 
      /* Enable Interrupt by overflow */
      TIM_ITConfig(TIM2, TIM_IT_CC2, ENABLE);
      /* Timer TIM2 Enable */
      TIM_Cmd(TIM2, ENABLE);
      /* Enable Interrupt of Timer TIM2 */
      NVIC_EnableIRQ(TIM2_IRQn);
}

void TIMER4_PWM_init_B8(int prescaler, int period)
{
	GPIO_InitTypeDef port;
	TIM_TimeBaseInitTypeDef timer;
	TIM_OCInitTypeDef timerPWM;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

	GPIO_StructInit(&port);
	port.GPIO_Mode = GPIO_Mode_AF_PP;
	port.GPIO_Pin = GPIO_Pin_8;
	port.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOB, &port);

	TIM_TimeBaseStructInit(&timer);
	timer.TIM_Prescaler = prescaler;
	timer.TIM_Period = period;
	timer.TIM_ClockDivision = 0;
	timer.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM4, &timer);

	TIM_OCStructInit(&timerPWM);
	timerPWM.TIM_OCMode = TIM_OCMode_PWM1;
	timerPWM.TIM_OutputState = TIM_OutputState_Enable;
	timerPWM.TIM_Pulse = 10;
	timerPWM.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC3Init(TIM4, &timerPWM);

	TIM_Cmd(TIM4, ENABLE);
}

void TIMER3_init(int prescaler, int period)
{
 //========================= TIMER3
	TIM_TimeBaseInitTypeDef TIMER_InitStructure3;
	NVIC_InitTypeDef NVIC_InitStructure3;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); // Вмикаємо тактування таймера TIM4

	TIM_TimeBaseStructInit(&TIMER_InitStructure3);
	TIMER_InitStructure3.TIM_CounterMode = TIM_CounterMode_Up; // Режим рахунку
	TIMER_InitStructure3.TIM_Prescaler = prescaler; // Поділювач частоти для таймера
	// Треба ще враховувати як налаштовані поділювачі RCC_HCLKConfig( RCC_SYSCLK_Div1); RCC_PCLK1Config(RCC_HCLK_Div1);
	// У нашому випадку обидва  = RCC_SYSCLK_Div1, тобто до поділювача таймера доходить частота зовнішнього кварцу (8МГц)
	TIMER_InitStructure3.TIM_Period = period; // Період, через який виконується переривання по переповненню  // F=8000000/8000/500 = 2 рази/сек.
	TIM_TimeBaseInit(TIM3, &TIMER_InitStructure3);
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE); // Вмикаємо переривання по переповненню таймера
	TIM_Cmd(TIM3, ENABLE);// Вмикаємо таймер

	/* NVIC Configuration */
	/* Enable the TIM4_IRQn Interrupt */
	NVIC_InitStructure3.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitStructure3.NVIC_IRQChannelPreemptionPriority = 5;
	NVIC_InitStructure3.NVIC_IRQChannelSubPriority = 5;
	NVIC_InitStructure3.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure3);
}
