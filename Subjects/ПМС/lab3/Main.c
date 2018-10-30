#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include <string.h>
#include "btn_lib.h"
#include "led_lib.h"
#include "pwm_lib.h"
#include "timer_lib.h"


volatile uint8_t is_signal_update = 0;
volatile uint8_t is_button_check = 0;


volatile uint8_t signal = 0;

void send_signal_GPIOA(int signal, uint16_t GPIO_Pin)
{
	if (signal == 1)
	{
		GPIO_SetBits(GPIOA, GPIO_Pin);
	}
	else
	{
		GPIO_ResetBits(GPIOA, GPIO_Pin);
	}
}

void TIM4_IRQHandler(void)
{
		if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)
		{
			TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
			is_signal_update = 1;
		}
		
		//signal ^=1;
}

void TIM2_IRQHandler(void)
{
		if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
		{
			TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
			is_button_check = 1;
		}
		
}

int main (void)
{
	btn_init_in_c(GPIO_Pin_15);
	btn_init_in_c(GPIO_Pin_13);
	init_GPIOA(GPIO_Pin_0);
	SetSysClockToHSE();
	TIMER4_init(100); //pwm period
	TIMER2_init(100); //button check period
	
	PWM_Generator PWM_Generator_A0;
	PWM_Generator_A0.FULL_POWER = 1;
	PWM_Generator_A0.MIN_POWER = 0.1;
	PWM_Generator_A0.POWER_STEP = 0.01;
	PWM_Generator_A0.CONTROL_STEP = 0.05;
	PWM_Generator_A0.current_power = 1;
	PWM_Generator_A0.power_counter = 0;
	
	
	while(1)
	{
		if (is_signal_update == 1)
		{
			signal = PWM_signal(PWM_Generator_A0);
			PWM_Generator_A0 = update_PWM(PWM_Generator_A0);
			
			is_signal_update = 0;
		}
		if (is_button_check == 1)
		{
			if (btn_in_c_test_GND_connect(GPIO_Pin_15) == 1)
			{
				PWM_Generator_A0 = increase_power(PWM_Generator_A0);
			}
			if (btn_in_c_test_GND_connect(GPIO_Pin_13) == 1)
			{
				PWM_Generator_A0 = decrease_power(PWM_Generator_A0);
			}
			
			is_button_check = 0;
		}
		send_signal_GPIOA(signal, GPIO_Pin_0);
	}
}
