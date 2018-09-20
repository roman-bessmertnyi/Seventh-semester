#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "tm1637.h"
#include "brown_delay.h"

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




int main(void) {
sys_tick_ini();    
uint16_t j = 0;	
TM1637_init();	
TM1637_brightness(BRIGHT_DARKEST); 
  while (1) {                    

		for (j = 0; j < 10; j++){
			    delay_from_Brown(DELAY_BROWN);
				TM1637_display_all(j);	
				}
				
		 for (j = 9; j > 1; j--){
				delay_from_Brown(DELAY_BROWN);
				TM1637_display_all(j);
				}
		 		

        delay_from_Brown(DELAY_BROWN);   
	    TM1637_clearDisplay();
        TM1637_display(0,0);
        delay_from_Brown(DELAY_BROWN);
        TM1637_display(1,1);
        delay_from_Brown(DELAY_BROWN);        
        TM1637_display(2,2);
        delay_from_Brown(DELAY_BROWN);      
        TM1637_display(3,3);
        delay_from_Brown(DELAY_BROWN);      
  						
						 }
		}

  
        
        
        
        
        

