#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

//=================================
//
//  Connect to keyboard as following:
//
//  PORT B - 9 10 11 12  13 14 15
//					 ^	^	 ^  ^
//
//=================================

#define KEYPAD_NO_PRESSED 0xFF

void init_keypad(void);

uint8_t keypadGetKey(void);
