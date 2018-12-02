#include "lab2.h"

void btn_init_RED (void){
    //кнопка
   
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE); // (1)
    
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;    
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}

// for tetsing this lib !!!
uint32_t btn_RED_test_GND_connect_A0(void){
    if (!GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0))// Catch from GND 
		{//slow, press and connect GPIOC 13 to GND 
			 return 1;
		}		
		else 
		{//fast no press !!!
			return 0;    
		}
		
	}

	uint32_t btn_RED_test_GND_connect_A1(void){
    if (!GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1))// Catch from GND 
		{//slow, press and connect GPIOC 13 to GND 
			 return 1;
		}		
		else 
		{//fast no press !!!
			return 0;    
		}
		
	} 
	
	uint32_t btn_RED_test_GND_connect_A2(void){
    if (!GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_2))// Catch from GND 
		{//slow, press and connect GPIOC 13 to GND 
			 return 1;
		}		
		else 
		{//fast no press !!!
			return 0;    
		}
		
	} 
	
	uint32_t btn_RED_test_GND_connect_A3(void){
    if (!GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_3))// Catch from GND 
		{//slow, press and connect GPIOC 13 to GND 
			 return 1;
		}		
		else 
		{//fast no press !!!
			return 0;    
		}
		
	} 
	
	void buttonHandler()
	{
		if (btn_RED_test_GND_connect_A0()) 
		{
			uart_putc(USART1, 0);
			TM1637_display_all(0);
			delay_from_Brown(1000);
		}
		
		
		if (btn_RED_test_GND_connect_A1()) 
		{
			uart_putc(USART1, 1);
			delay_from_Brown(1000);
			TM1637_display_all(1);
		}
		
		
		if (btn_RED_test_GND_connect_A2()) 
		{
			uart_putc(USART1, 2);
			TM1637_display_all(2);
			delay_from_Brown(1000);
		}
		//2
		
		if (btn_RED_test_GND_connect_A3()) 
		{
			uart_putc(USART1, 3);
			TM1637_display_all(3);
			delay_from_Brown(1000);
		}
	}
