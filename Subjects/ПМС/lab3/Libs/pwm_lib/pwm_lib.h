#include <stm32f10x.h>
#include <stm32f10x_rcc.h>
#include <stm32f10x_gpio.h>

typedef struct
{
  double FULL_POWER;
	double MIN_POWER;
	double POWER_STEP;
	double CONTROL_STEP;
	volatile double power_counter;
	volatile double current_power;
}PWM_Generator;

int PWM_signal(PWM_Generator gen);
PWM_Generator update_PWM(PWM_Generator gen);
PWM_Generator increase_power(PWM_Generator gen);
PWM_Generator decrease_power(PWM_Generator gen);
