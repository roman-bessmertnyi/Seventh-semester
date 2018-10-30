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

void TIMER4_init(int period)
{
	// ========================TIMER4
	TIM_TimeBaseInitTypeDef TIMER_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); // Вмикаємо тактування таймера TIM4

	TIM_TimeBaseStructInit(&TIMER_InitStructure);
	TIMER_InitStructure.TIM_CounterMode = TIM_CounterMode_Up; // Режим рахунку
	TIMER_InitStructure.TIM_Prescaler = 8; // Поділювач частоти для таймера
	// Треба ще враховувати як налаштовані поділювачі RCC_HCLKConfig( RCC_SYSCLK_Div1); RCC_PCLK1Config(RCC_HCLK_Div1);
	// У нашому випадку обидва  = RCC_SYSCLK_Div1, тобто до поділювача таймера доходить частота зовнішнього кварцу (8МГц)
	TIMER_InitStructure.TIM_Period = period; // Період, через який виконується переривання по переповненню  // F=8000000/8000/500 = 2 рази/сек.
	TIM_TimeBaseInit(TIM4, &TIMER_InitStructure);
	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE); // Вмикаємо переривання по переповненню таймера
	TIM_Cmd(TIM4, ENABLE);// Вмикаємо таймер

	/* NVIC Configuration */
	/* Enable the TIM4_IRQn Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

void TIMER2_init(int period)
{
	//========================= TIMER2
	TIM_TimeBaseInitTypeDef TIMER_InitStructure2;
	NVIC_InitTypeDef NVIC_InitStructure2;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); // Вмикаємо тактування таймера TIM4

	TIM_TimeBaseStructInit(&TIMER_InitStructure2);
	TIMER_InitStructure2.TIM_CounterMode = TIM_CounterMode_Up; // Режим рахунку
	TIMER_InitStructure2.TIM_Prescaler = 8000; // Поділювач частоти для таймера
	// Треба ще враховувати як налаштовані поділювачі RCC_HCLKConfig( RCC_SYSCLK_Div1); RCC_PCLK1Config(RCC_HCLK_Div1);
	// У нашому випадку обидва  = RCC_SYSCLK_Div1, тобто до поділювача таймера доходить частота зовнішнього кварцу (8МГц)
	TIMER_InitStructure2.TIM_Period = period; // Період, через який виконується переривання по переповненню  // F=8000000/8000/500 = 2 рази/сек.
	TIM_TimeBaseInit(TIM2, &TIMER_InitStructure2);
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE); // Вмикаємо переривання по переповненню таймера
	TIM_Cmd(TIM2, ENABLE);// Вмикаємо таймер

	/* NVIC Configuration */
	/* Enable the TIM2_IRQn Interrupt */
	NVIC_InitStructure2.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure2.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure2.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure2.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure2);
}

void TIMER3_init(int period)
{
 //========================= TIMER3
	TIM_TimeBaseInitTypeDef TIMER_InitStructure3;
	NVIC_InitTypeDef NVIC_InitStructure3;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); // Вмикаємо тактування таймера TIM4

	TIM_TimeBaseStructInit(&TIMER_InitStructure3);
	TIMER_InitStructure3.TIM_CounterMode = TIM_CounterMode_Up; // Режим рахунку
	TIMER_InitStructure3.TIM_Prescaler = 8; // Поділювач частоти для таймера
	// Треба ще враховувати як налаштовані поділювачі RCC_HCLKConfig( RCC_SYSCLK_Div1); RCC_PCLK1Config(RCC_HCLK_Div1);
	// У нашому випадку обидва  = RCC_SYSCLK_Div1, тобто до поділювача таймера доходить частота зовнішнього кварцу (8МГц)
	TIMER_InitStructure3.TIM_Period = period; // Період, через який виконується переривання по переповненню  // F=8000000/8000/500 = 2 рази/сек.
	TIM_TimeBaseInit(TIM3, &TIMER_InitStructure3);
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE); // Вмикаємо переривання по переповненню таймера
	TIM_Cmd(TIM3, ENABLE);// Вмикаємо таймер

	/* NVIC Configuration */
	/* Enable the TIM4_IRQn Interrupt */
	NVIC_InitStructure3.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitStructure3.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure3.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure3.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure3);
}
