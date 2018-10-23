#include <stm32f10x.h>
#include <stm32f10x_rcc.h>
#include <stm32f10x_gpio.h>

void btn_init_in_c15 (void);
void led_init_in_a0 (void);
uint32_t btn_c15_test_GND_connect(void);
void SetSysClockToHSE(void);
void TIMER4_init(int period);
