#include "pwm_lib.h"
#include "btn_lib.h"

PWM_Generator update_PWM(PWM_Generator gen)
{
	//power_counter goes from MIN_POWER to FULL_POWER with POWER_STEP
	if (gen.power_counter < gen.FULL_POWER)
	{
		gen.power_counter += gen.POWER_STEP;
	} else
	{
		gen.power_counter = 0;
	}
	return gen;
}

int PWM_signal(PWM_Generator gen)
{
	//until power_counter hits current_power, the lsignal is on. Then it's off
	if (gen.power_counter < gen.current_power){
		return 1;
	} else
	{
		return 0;
	}
}

PWM_Generator increase_power(PWM_Generator gen)
{
	//increase current power by CONTROL_STEP
	if (gen.current_power < gen.FULL_POWER)
	{
		gen.current_power += gen.CONTROL_STEP;
	}
	return gen;
}

PWM_Generator decrease_power(PWM_Generator gen)
{
	//decrease current power by CONTROL_STEP
	
	if (gen.current_power > gen.MIN_POWER)
	{
		gen.current_power -= gen.CONTROL_STEP;
	}
	return gen;
}
