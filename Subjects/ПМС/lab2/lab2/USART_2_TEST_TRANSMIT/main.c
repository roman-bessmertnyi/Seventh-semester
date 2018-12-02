#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include <string.h>
#include "stm32f10x_usart.h"
#include "usart_lib.h"
#include "tm1637.h"
#include "brown_delay.h"
#include "lab2.h"

extern void buttonHandler(void);

// TRANSMITT !!!!

int main (void)
{
    sys_tick_ini();
    btn_init_RED ();
    TM1637_init();	
    TM1637_brightness(BRIGHT_DARKEST); 
     
	uart_open(USART1, 9600, USART_Mode_Rx | USART_Mode_Tx);
	
	
	while(1)
	{
		
		buttonHandler();

		//receive answer
		 char answer = uart_getc(USART1);		
		//show answer			
		 TM1637_display_all((uint16_t)answer);
        
	}

}

