#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include <string.h>
#include "btn_lib.h"

#define FULL_POWER 1
#define MIN_POWER 0.1
#define POWER_STEP 0.01
#define CONTROL_STEP 0.05
#define BUTTON_SPEED 3000

double current_power = 1;// if not no global 
double power_counter = 0;
int button_tick_counter = 0;

void power_control(void)
{
	//until power_counter hits current_power, the led is on. Then it's off
	if (power_counter < current_power){
				GPIO_SetBits(GPIOA, GPIO_Pin_0);
		}else {
		GPIO_ResetBits(GPIOA, GPIO_Pin_0);
		}
	//power_counter goes from MIN_POWER to FULL_POWER with POWER_STEP
	if (power_counter < FULL_POWER){
		power_counter += POWER_STEP;
	}else {
				power_counter = 0;
				}
}

void button_asker(void)// h
{
	if (++button_tick_counter >= BUTTON_SPEED) 
	{
		if (btn_c15_test_GND_connect()) 
		{
			//increase current power by CONTROL_STEP
			current_power += CONTROL_STEP;
			if (current_power > FULL_POWER)
			{
				current_power = MIN_POWER;
			}
		}
		button_tick_counter = 0;
	}
}



void TIM4_IRQHandler(void)
{
        if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)
        {
            // ????'?????? ???????? ??????. ???? ????? ?? ???????, ????? ??????? ??????????? ????? ???????? ????
            TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
						power_control();
						button_asker();
          
        }
}



void SysTick_Handler(void){                               /* SysTick interrupt Handler. */
	//LED_Power_Handler();
	button_asker();
}

int main (void)
{
	SetSysClockToHSE();
	btn_init_in_c15();
	led_init_in_a0();
	TIMER4_init(1); //period 10 milsec
	
	while(1)
	{
	}
}
