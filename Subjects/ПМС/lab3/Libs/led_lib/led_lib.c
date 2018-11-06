#include "led_lib.h"

void init_GPIOA (uint16_t GPIO_Pin){ 
  GPIO_InitTypeDef  GPIO_InitStructureA;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	GPIO_InitStructureA.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructureA.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructureA.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructureA);
}

void init_GPIOB (uint16_t GPIO_Pin){ 
  GPIO_InitTypeDef  GPIO_InitStructureB;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

	GPIO_InitStructureB.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructureB.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructureB.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructureB);
}

void init_GPIOC (uint16_t GPIO_Pin){ 
  GPIO_InitTypeDef  GPIO_InitStructureC;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

	GPIO_InitStructureC.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructureC.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructureC.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructureC);
}
