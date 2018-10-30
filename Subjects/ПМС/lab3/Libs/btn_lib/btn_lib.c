#include "btn_lib.h"

void btn_init_in_c(uint16_t GPIO_Pin){
   
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC , ENABLE); // (1)
    
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin;    
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
}

uint8_t btn_in_c_test_GND_connect(uint16_t GPIO_Pin){
	if (!GPIO_ReadInputDataBit(GPIOC, GPIO_Pin))// Catch from GND 
	{
		 return 1;
	}		
	else 
	{
		return 0;    
	}
	
}
