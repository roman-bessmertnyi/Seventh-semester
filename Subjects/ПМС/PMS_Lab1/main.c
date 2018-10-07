#include "brown_delay.h"
#include "tm1637.h"
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"

#define LED_ONOFF();  GPIOC->ODR ^= GPIO_Pin_13;
#define DELAY_BROWN 500 // 1000=0.25 ** 500=0.125


void board_led_ini(void){// Init GPIO_Pin_13  led on board on GPIOC
  GPIO_InitTypeDef  GPIO_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
  GPIO_SetBits(GPIOC, GPIO_Pin_13); 
}

int main(void)
{
	float display_number = 31.45;
	
	int intpart = (int)display_number; //310
	int leftdrop = intpart/100; //3
	intpart = intpart - leftdrop*100; //10
	
  int decpart = (int)((display_number - intpart)*100);//45
	
	int num_1 = (int)(intpart/10);
	int num_2 = intpart - num_1*10;; //31-30=1
	int num_3 = (int)(decpart/10); //4
	int num_4 = decpart - num_3*10; //45-40=5
	
	sys_tick_ini();    
	TM1637_init();	
	TM1637_brightness(BRIGHTEST);
	
  while (1) {  
			TM1637_display(0,num_1);
			TM1637_display(1,num_2);     
			TM1637_display(2,num_3);  
			TM1637_display(3,num_4);  
  						
	}
}
