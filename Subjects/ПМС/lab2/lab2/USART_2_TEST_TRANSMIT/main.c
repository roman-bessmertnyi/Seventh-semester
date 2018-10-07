#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include <string.h>
#include "stm32f10x_usart.h"
#include "usart_lib.h"
#include "tm1637.h"
#include "brown_delay.h"
#include "btn_lib.h"

extern void buttonHandler(void);

// TRANSMITT !!!!

int main (void)
{
    sys_tick_ini();
    btn_init_in_c15 ();
    btn_init_RED ();
    TM1637_init();	
    TM1637_brightness(BRIGHT_DARKEST); 
    //uint16_t j = 55;
    TM1637_display_all(55);
    delay_from_Brown(1000);
    TM1637_display_all(77);
    delay_from_Brown(1000);
    TM1637_clearDisplay();
     
	uart_open(USART1, 9600, USART_Mode_Rx | USART_Mode_Tx);
	
	
	while(1)
	{
		TM1637_display_all(1234);
		
		buttonHandler();

		//receive answer
		 char answer = uart_getc(USART1);		
		//show answer			
		 TM1637_display_all((uint16_t)answer);
		
       //a9, a10 - busy for ua
		//for (i = 0; (i < strlen(stringToSend1))&&(btn_test_GND_connect_fast()); i ++)   {
		/*for (i = 0; (i < strlen(stringToSend1))&&(btn_RED_test_GND_connect()); i ++)   {
				 delay_from_Brown(100);
				//send
				 uart_putc(USART1, stringToSend1[i]);
				 delay_from_Brown(1000);
				//receive answer
				 char answer = uart_getc(USART1);		
				//show answer			
				 TM1637_display_all((uint16_t)answer);
				 delay_from_Brown(1000);
				//show char that was sent
				 TM1637_display_all((uint16_t)stringToSend1[i]);
		 } */
        
	}

}

