#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_tim.h"
#include "timer_lib.h"
#include "tm1637.h"

#define STATE_WRITE_DATA 1
#define STATE_SEND_DATA 2
#define STATE_RECIEVE_DATA 3
#define STATE_UPLOAD_DATA 4
#define STATE_IDLE 0

volatile double input[1000];
volatile double output[1000];

volatile int i = 0;

volatile int finite_state = STATE_IDLE;

int getInput(int i)
{
	if (i % 200 < 100)
		return 1;
	else
		return 0;
}

void TIM3_IRQHandler(void){
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
	{
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
		finite_state = STATE_SEND_DATA;
		
	}
}

int main(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
	
	SetSysClockTo72();
	TIMER3_writer_init(10);
	TM1637_init();	
	TM1637_brightness(BRIGHTEST);
	
	while (1)
	{
		switch(finite_state)
		{
			case STATE_SEND_DATA:
				if (getInput(i)) GPIO_SetBits(GPIOA, GPIO_Pin_7);
				else GPIO_ResetBits(GPIOA, GPIO_Pin_7);
				finite_state = STATE_WRITE_DATA;
				break;
			case STATE_WRITE_DATA:
				if (i < 1000)	
				{
					input[i] = getInput(i) * 3.3;
					TM1637_display_all(input[i]);
					//output[i] = getOutput();
					i++;
				}
				else TM1637_display_all(0);
			
				finite_state = STATE_IDLE;
				break;
		}
	}
	
}
