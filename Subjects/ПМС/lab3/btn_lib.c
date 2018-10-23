#include "btn_lib.h"

void btn_init_in_c15 (void){
   
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC , ENABLE); // (1)
    
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;    
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
}

void led_init_in_a0 (void){ 
  GPIO_InitTypeDef  GPIO_InitStructureA;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	GPIO_InitStructureA.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructureA.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructureA.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructureA);
}

uint32_t btn_c15_test_GND_connect(void){
	if (!GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_15))// Catch from GND 
	{
		 return 1;
	}		
	else 
	{
		return 0;    
	}
	
}

void TIMER4_init(int period)
{
	// ========================TIMER4
    TIM_TimeBaseInitTypeDef TIMER_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
 
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); // ???????? ?????????? ??????? TIM4
 
    TIM_TimeBaseStructInit(&TIMER_InitStructure);
    TIMER_InitStructure.TIM_CounterMode = TIM_CounterMode_Up; // ????? ???????
    TIMER_InitStructure.TIM_Prescaler = 8; // ????????? ??????? ??? ???????
    // ????? ?? ??????????? ?? ??????????? ?????????? RCC_HCLKConfig( RCC_SYSCLK_Div1); RCC_PCLK1Config(RCC_HCLK_Div1);
    // ? ?????? ??????? ??????  = RCC_SYSCLK_Div1, ????? ?? ?????????? ??????? ???????? ??????? ??????????? ?????? (8???)
    TIMER_InitStructure.TIM_Period = period; // ??????, ????? ???? ??????????? ??????????? ?? ????????????  // F=8000000/8000/500 = 2 ????/???.
    TIM_TimeBaseInit(TIM4, &TIMER_InitStructure);
    TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE); // ???????? ??????????? ?? ???????????? ???????
    TIM_Cmd(TIM4, ENABLE);// ???????? ??????
 
    /* NVIC Configuration */
    /* Enable the TIM4_IRQn Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

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
