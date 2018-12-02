#include <stm32f10x.h>
#include <stm32f10x_rcc.h>
#include <stm32f10x_gpio.h>
#include "btn_lib.h"
#include "brown_delay.h"
#include "tm1637.h"
#include "usart_lib.h"

void btn_init_RED (void);
uint32_t btn_RED_test_GND_connect_A0(void);
uint32_t btn_RED_test_GND_connect_A1(void);
uint32_t btn_RED_test_GND_connect_A2(void);
uint32_t btn_RED_test_GND_connect_A3(void);
void buttonHandler(void);
