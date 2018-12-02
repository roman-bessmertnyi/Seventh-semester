#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include <string.h>
#include "stm32f10x_usart.h"
#include "usart_lib.h"
#include "tm1637.h"
#include "brown_delay.h"
#include "btn_lib.h"
#include "lib_keyboard.h"
#include "lib_8_leds_on_board.h"
// TRANSMITT !!!!

void DisplaySymbol(uint8_t c);

int main (void)
{	
    sys_tick_ini();
    btn_init_in_c15 ();
		init_keypad();
		leds_init();
    TM1637_init();	
	
		leds_test();
	
    TM1637_brightness(BRIGHT_TYPICAL); 		    	
    TM1637_display_all(55);
    delay_from_Brown(1000);
    TM1637_display_all(77);
    delay_from_Brown(1000);
    TM1637_clearDisplay();
	
	uart_open(USART1, 9600, USART_Mode_Rx | USART_Mode_Tx);

	uint8_t key;
	while(1)
	{       
		key = keypadGetKey();
		uart_putc(USART1, key);
		DisplaySymbol(key);
		leds_from_key_2(key);
		
		delay_from_Brown(200);		       
	}
};

void DisplaySymbol(uint8_t c){
	TM1637_clearDisplay();	
	if(c>=48 && c<=58){
		TM1637_display(1,c-48);
	}
	else{	
    switch (c)  {
			case '*': 
					TM1637_display_all_custom(0x00f9cf00 );
					break; 
			case '#': 
					TM1637_display_all_custom(0x00f6f600 );					
					break;
			default:	
					//TM1637_display_custom(3,0x7f&c);	
					break;
    }
	}
}

