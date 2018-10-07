#include "btn_lib.h"
#include "brown_delay.h"
#include "usart_lib.h"
#include "lab2.h"

// for tetsing this lib !!!
uint32_t btn_RED_test_GND_connect_A0(void){
    if (!GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0))// Catch from GND 
		{//slow, press and connect GPIOC 13 to GND 
			 led_toggled_brown();
			 delay_from_Brown(500);
			 return 1;
		}		
		else 
		{//fast no press !!!
			led_toggled_brown();
			delay_from_Brown(100);
			return 0;    
		}
		
	}

	uint32_t btn_RED_test_GND_connect_A1(void){
    if (!GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1))// Catch from GND 
		{//slow, press and connect GPIOC 13 to GND 
			 led_toggled_brown();
			 delay_from_Brown(500);
			 return 1;
		}		
		else 
		{//fast no press !!!
			led_toggled_brown();
			delay_from_Brown(100);
			return 0;    
		}
		
	} 
	
	uint32_t btn_RED_test_GND_connect_A2(void){
    if (!GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_2))// Catch from GND 
		{//slow, press and connect GPIOC 13 to GND 
			 led_toggled_brown();
			 delay_from_Brown(500);
			 return 1;
		}		
		else 
		{//fast no press !!!
			led_toggled_brown();
			delay_from_Brown(100);
			return 0;    
		}
		
	} 
	
	uint32_t btn_RED_test_GND_connect_A3(void){
    if (!GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_3))// Catch from GND 
		{//slow, press and connect GPIOC 13 to GND 
			 led_toggled_brown();
			 delay_from_Brown(500);
			 return 1;
		}		
		else 
		{//fast no press !!!
			led_toggled_brown();
			delay_from_Brown(100);
			return 0;    
		}
		
	} 
	
	void buttonHandler()
	{
		if (btn_RED_test_GND_connect_A0()) 
		{
			uart_putc(USART1, 0);
			delay_from_Brown(1000);
		}
		
		
		if (btn_RED_test_GND_connect_A1()) 
		{
			uart_putc(USART1, 1);
			delay_from_Brown(1000);
		}
		
		
		if (btn_RED_test_GND_connect_A2()) 
		{
			uart_putc(USART1, 2);
			delay_from_Brown(1000);
		}
		//2
		
		if (btn_RED_test_GND_connect_A3()) 
		{
			uart_putc(USART1, 3);
			delay_from_Brown(1000);
		}
	}
