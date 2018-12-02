#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

#ifndef LEDS8
#define LEDS8

// if lib_keyboard\lib_keypad is absent
#ifndef KEYPAD_NO_PRESSED
#define KEYPAD_NO_PRESSED 0xFF
#endif

//===============================================
//
// This lib uses:
//			PORT A 0-7 pins for LEDs
//
//-----------------------------------------------


void leds_init(void);
void leds_reset(void);
void leds_test(void);

//lights LEDs depending on key
void leds_from_key(uint8_t key);

//use this if leds_from_key not working
void leds_from_key_2(uint8_t key);

#endif
