#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include <string.h>
#include "btn_lib.h"

#define FULL_POWER 1
#define MIN_POWER 0.1
#define POWER_STEP 0.05

double current_power = FULL_POWER;
double power_counter = 0;

void sys_tick_ini(int _SECOND)
{
	RCC_ClocksTypeDef RCC_Clocks;
	RCC_GetClocksFreq(&RCC_Clocks);
	SysTick_Config(RCC_Clocks.HCLK_Frequency / _SECOND);
}

void SysTick_Handler(void){                               /* SysTick interrupt Handler. */
	if (power_counter < current_power) GPIO_SetBits(GPIOA, GPIO_Pin_0);
	else GPIO_ResetBits(GPIOA, GPIO_Pin_0);
	
	if (power_counter < FULL_POWER) power_counter += POWER_STEP;
	else power_counter = 0;
}

int main (void)
{
	sys_tick_ini(1);
	btn_init_in_c15 ();
	btn_init_RED ();
	
	while(1)
	{
		if (btn_RED_test_GND_connect()) 
		{
			if (current_power >= FULL_POWER) current_power = MIN_POWER;
			else current_power += MIN_POWER;
		}
	}
}
