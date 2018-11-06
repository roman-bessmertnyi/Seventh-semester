#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include <string.h>
#include "btn_lib.h"
#include "led_lib.h"
#include "pwm_lib.h"
#include "timer_lib.h"
#include "math_.h"

#define C15_PRESS 2
#define C13_PRESS 4
#define SIN_UPDATE 5
#define DEFAULT 0


#define FULL_POWER 1
#define MIN_POWER 0.1
#define POWER_STEP 0.05

#define PERIOD 20000 //in miliseconds period T

#define MAX_SIN 255



volatile uint8_t finite_state = DEFAULT;

void state_set_sin(void)
{
	finite_state = SIN_UPDATE;
}

void state_set_c15(void)
{
	if (btn_in_c_test_GND_connect(GPIO_Pin_15))
	{
		finite_state = C15_PRESS;
	}
}

void state_set_c13(void)
{
	if (btn_in_c_test_GND_connect(GPIO_Pin_13))
	{
		finite_state = C13_PRESS;
	}
}

void TIM2_IRQHandler(void)
{
		if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
		{
			TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
			state_set_c15();
			state_set_c13();
			state_set_sin();
		}
		
}

int main (void)
{
	btn_init_in_c(GPIO_Pin_15);
	btn_init_in_c(GPIO_Pin_13);
	SetSysClockToHSE();
	TIMER4_PWM_init(PERIOD); //pwm period
	TIMER2_init(2); //button check period
	
	
	double pulse_width = MIN_POWER; //control width of pulth
	TIM4->CCR1 = PERIOD * FULL_POWER * pulse_width;
	
	int sin_counter = 250;
	
	while(1)
	{
		switch(finite_state)
		{
			case C15_PRESS:
				if (pulse_width < FULL_POWER)
				{
					pulse_width += POWER_STEP;
				}
        TIM4->CCR1 = PERIOD * FULL_POWER * pulse_width;
				finite_state = DEFAULT;
				break;
			case C13_PRESS:
				if (pulse_width > MIN_POWER)
				{
					pulse_width -= POWER_STEP;
				}
        TIM4->CCR1 = PERIOD * FULL_POWER * pulse_width;
				finite_state = DEFAULT;
				break;
			case SIN_UPDATE:
			
				pulse_width = sin_array[sin_counter];
				
				TIM4->CCR1 = PERIOD * pulse_width / 255;
			
				if (sin_counter < MAX_SIN-1) //occurs every TIM4 tic
				{
					sin_counter++;
				}
				else sin_counter=0;
			
				finite_state = DEFAULT;
				break;
		}
	}
}
