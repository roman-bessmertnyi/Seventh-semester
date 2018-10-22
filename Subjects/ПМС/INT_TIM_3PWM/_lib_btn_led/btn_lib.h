#include <stm32f10x.h>
#include <stm32f10x_rcc.h>
#include <stm32f10x_gpio.h>


void led_init_out_c13 (void);
void led_init_out_a0 (void);
void led_init_out_a1 (void);
void led_init_out_b6 (void);
void btn_init_in_c15 (void);

void led_toggled_brown(void);//c13!
void led_toggled_brown_a0(void);
void led_toggled_brown_a1(void);
void led_toggled_b6(void);
uint32_t btn_test_GND_connect(void);
uint32_t btn_test_GND_connect_fast(void);
uint32_t btn_test_GND_connect_toggled(void);

