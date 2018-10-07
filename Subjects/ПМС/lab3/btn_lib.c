#include "btn_lib.h"

void btn_init_in_c15 (void){
   
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC , ENABLE); // (1)
    
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;    
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
}

void btn_init_RED (void){
   
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE); // (1)
    
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;    
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}

uint32_t btn_RED_test_GND_connect(void){
	if (!GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0))// Catch from GND 
	{
		 return 1;
	}		
	else 
	{
		return 0;    
	}
	
}
