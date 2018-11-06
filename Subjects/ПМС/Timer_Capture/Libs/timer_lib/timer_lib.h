#include <stm32f10x.h>
#include <stm32f10x_rcc.h>
#include <stm32f10x_gpio.h>

void SetSysClockTo72(void);

void TIMER4_PWM_init_B8(int prescaler, int period);
void TIMER3_init(int prescaler, int period);
void TIMER2_input_init_A2(int prescaler);
