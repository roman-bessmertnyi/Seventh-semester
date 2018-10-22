#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include <string.h>
#include "btn_lib.h"

#define FULL_POWER 1
#define MIN_POWER 0.1
#define POWER_STEP 0.01
#define CONTROL_STEP 0.05
#define BUTTON_SPEED 500

double current_power = 1;
double power_counter = 0;
int button_tick_counter = 0;

void sys_tick_ini(int tick_per_second)
{
	RCC_ClocksTypeDef RCC_Clocks;
	RCC_GetClocksFreq(&RCC_Clocks);
	SysTick_Config(RCC_Clocks.HCLK_Frequency / tick_per_second);
}

void LED_Power_Handler(void)
{
	//until power_counter hits current_power, the led is on. Then it's off
	if (power_counter < current_power) GPIO_SetBits(GPIOB, GPIO_Pin_8);
	else GPIO_ResetBits(GPIOB, GPIO_Pin_8);
	
	//power_counter goes from MIN_POWER to FULL_POWER with POWER_STEP
	if (power_counter < FULL_POWER) power_counter += POWER_STEP;
	else 
	{
		power_counter = 0;
	}
}

void Button_Handler(void)
{
	if (++button_tick_counter >= BUTTON_SPEED) 
	{
		if (btn_c15_test_GND_connect()) 
		{
			//increase current power by CONTROL_STEP
			current_power += CONTROL_STEP;
			if (current_power > FULL_POWER) current_power = MIN_POWER;
		}
		button_tick_counter = 0;
	}
}

void SysTick_Handler(void){                               /* SysTick interrupt Handler. */
	LED_Power_Handler();
	Button_Handler();
	/*//debug for testing without button. remove when button
	int step_divider = 300; 
	//increase current power by CONTROL_STEP
				current_power += CONTROL_STEP/step_divider;
				if (current_power > FULL_POWER) current_power = MIN_POWER;*/
}

int main (void)
{
	sys_tick_ini(10000); //init timer
	btn_init_in_c15 (); //init button
	led_init_in_b8_to_15 (); //init LED
	
	int btn_was_off = 1;
	while(1)
	{
		//button controls
		/*if (btn_c15_test_GND_connect()) 
		{
			if (btn_was_off == 1)
			{
				//increase current power by CONTROL_STEP
				current_power += CONTROL_STEP;
				if (current_power > FULL_POWER) current_power = MIN_POWER;
			}
			btn_was_off = 0;
		}
		else btn_was_off = 1;*/
	}
}
