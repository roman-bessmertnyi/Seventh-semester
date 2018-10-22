#include "btn_lib.h"

void btn_init_in_c15 (void){
   
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC , ENABLE); // (1)
    
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;    
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
}

void led_init_in_b8_to_15 (void){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);// BUS init 
    
GPIO_InitTypeDef   LAB_3_GPIO_B; 
GPIO_StructInit(&LAB_3_GPIO_B);
LAB_3_GPIO_B.GPIO_Pin =
            GPIO_Pin_8 |
            GPIO_Pin_9 |
            GPIO_Pin_10 |
            GPIO_Pin_11 |
            GPIO_Pin_12 |
            GPIO_Pin_13 |
            GPIO_Pin_14 |
            GPIO_Pin_15;
LAB_3_GPIO_B.GPIO_Mode = GPIO_Mode_Out_PP;
LAB_3_GPIO_B.GPIO_Speed = GPIO_Speed_50MHz;
GPIO_Init(GPIOB, &LAB_3_GPIO_B);
}

uint32_t btn_c15_test_GND_connect(void){
	if (!GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_15))// Catch from GND 
	{
		 return 1;
	}		
	else 
	{
		return 0;    
	}
	
}
