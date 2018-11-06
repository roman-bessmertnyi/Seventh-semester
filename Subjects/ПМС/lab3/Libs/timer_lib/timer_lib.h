#include <stm32f10x.h>
#include <stm32f10x_rcc.h>
#include <stm32f10x_gpio.h>

void SetSysClockToHSE(void);
void TIMER4_PWM_init(int period);
void TIMER3_init(int period);
void TIMER2_init(int period);
