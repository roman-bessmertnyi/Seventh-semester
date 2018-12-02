#include "lib_8_leds_on_board.h"


void delay(int time) {
	for (int i = 0; i < time; i++);
}

void leds_init(void){
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);// BUS is ON
	
    GPIO_InitTypeDef      DISPLAY_A_STRUCT;         // REDY for struct 
    DISPLAY_A_STRUCT.GPIO_Pin =     GPIO_Pin_0 |     
                                    GPIO_Pin_1 |
                                    GPIO_Pin_2 |
                                    GPIO_Pin_3 |     
                                    GPIO_Pin_4 |
                                    GPIO_Pin_5 |     
                                    GPIO_Pin_6 |
                                    GPIO_Pin_7;
    DISPLAY_A_STRUCT.GPIO_Mode = GPIO_Mode_Out_PP;
	DISPLAY_A_STRUCT.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &DISPLAY_A_STRUCT);
}

void leds_reset(void){
   GPIO_ResetBits (GPIOA,      GPIO_Pin_0 |     
                               GPIO_Pin_1 |
                               GPIO_Pin_2 |
                               GPIO_Pin_3 |     
                               GPIO_Pin_4 |
                               GPIO_Pin_5 |     
                               GPIO_Pin_6 |
                               GPIO_Pin_7);
 }

void leds_test(void){
	int i = 0;
	int j = 0;
	for (; j<1; j++) {			
			i = 0;
			for (i = 1<<0; i < 1<<8; i <<= 1) {     /* Blink LED 0-7        */
			GPIO_SetBits(GPIOA,i);
			delay (500000);                               /* call wait function            */
			GPIO_ResetBits(GPIOA,i);
			}
			for (; i > 0; i >>= 1) {     /* Blink LED 0-7        */
			GPIO_SetBits(GPIOA,i);
			delay (500000);                               /* call wait function            */
			GPIO_ResetBits(GPIOA,i);
			}
	 }  
}

void leds_from_key(uint8_t key) {
	
    switch (key)  {
        case KEYPAD_NO_PRESSED: 
            leds_reset();
            GPIO_SetBits(GPIOA, GPIO_Pin_5 | GPIO_Pin_4 | GPIO_Pin_3|GPIO_Pin_2 | GPIO_Pin_1 | GPIO_Pin_0);
            delay(400000);
            break;
        case '1': 
            leds_reset();
            GPIO_SetBits(GPIOA, GPIO_Pin_0);
            delay(400000);
            break;
        case '4': 
            leds_reset();
            GPIO_SetBits(GPIOA, GPIO_Pin_2);
            delay(400000);
            break;
        case '7': 
            leds_reset();
            GPIO_SetBits(GPIOA, GPIO_Pin_2 | GPIO_Pin_1 | GPIO_Pin_0);
            delay(400000);
            break;
        case '*': 
            //----
            leds_reset();
            GPIO_SetBits(GPIOA, GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7);
            delay(400000);
            break;        
        case '2': 
            leds_reset();
            GPIO_SetBits(GPIOA,  GPIO_Pin_1);
            delay(400000);
            break;
        case '5': 
            leds_reset();
            GPIO_SetBits(GPIOA, GPIO_Pin_2 | GPIO_Pin_0);
            delay(400000);
            break;
        case '8': 
            leds_reset();
            GPIO_SetBits(GPIOA,  GPIO_Pin_3);
            delay(400000);
            break;
       case '0': 
            leds_reset();
            GPIO_SetBits(GPIOA, GPIO_Pin_8);
            delay(400000);
            break;
       case '3': 
            leds_reset();
            GPIO_SetBits(GPIOA, GPIO_Pin_1|GPIO_Pin_0);
            delay(400000);
            break;
      //---
        case '6': 
            leds_reset();
            GPIO_SetBits(GPIOA, GPIO_Pin_1|GPIO_Pin_2);
            delay(400000);
            break;
        case '9': 
            leds_reset();
            GPIO_SetBits(GPIOA, GPIO_Pin_3|GPIO_Pin_0);
            delay(400000);
            break;
        case '#': 
            leds_reset();
            GPIO_SetBits(GPIOA, GPIO_Pin_6 | GPIO_Pin_4| GPIO_Pin_2| GPIO_Pin_0);
            delay(400000);
        default:
            ;
    }
}

//use this if handleKeyPress_switch not working
void leds_from_key_2(uint8_t key) {
	
    switch (key)  {
        case KEYPAD_NO_PRESSED: 
            leds_reset();            
            delay(400000);
            break;				
       case '0': 
            leds_reset();
            GPIO_SetBits(GPIOA, GPIO_Pin_8);
            delay(400000);
            break;
        case '1': 
            leds_reset();
            GPIO_SetBits(GPIOA, GPIO_Pin_0);
            delay(400000);
            break;				       
        case '2': 
            leds_reset();
            GPIO_SetBits(GPIOA,  GPIO_Pin_1);
            delay(400000);
            break;				
       case '3': 
            leds_reset();
            GPIO_SetBits(GPIOA, GPIO_Pin_1|GPIO_Pin_2);
            delay(400000);
            break;
        case '4': 
            leds_reset();
            GPIO_SetBits(GPIOA, GPIO_Pin_2);
            delay(400000);
            break;				
        case '5': 
            leds_reset();
            GPIO_SetBits(GPIOA, GPIO_Pin_2 | GPIO_Pin_3);
            delay(400000);
            break;
        case '6': 
            leds_reset();
            GPIO_SetBits(GPIOA, GPIO_Pin_3);
            delay(400000);
            break;
        case '7': 
            leds_reset();
            GPIO_SetBits(GPIOA, GPIO_Pin_3 | GPIO_Pin_4);
            delay(400000);
            break;
        case '8': 
            leds_reset();
            GPIO_SetBits(GPIOA,  GPIO_Pin_5);
            delay(400000);
            break;
        case '9': 
            leds_reset();
            GPIO_SetBits(GPIOA, GPIO_Pin_5|GPIO_Pin_6);
            delay(400000);
            break;
        case '*': 
            //----
            leds_reset();
            GPIO_SetBits(GPIOA, GPIO_Pin_2 | GPIO_Pin_4 | GPIO_Pin_6);
            delay(400000);
            break; 
        case '#': 
            leds_reset();
            GPIO_SetBits(GPIOA, GPIO_Pin_1 | GPIO_Pin_3 | GPIO_Pin_5 | GPIO_Pin_7);
            delay(400000);
        default:
					GPIO_SetBits(GPIOA, GPIO_Pin_5 | GPIO_Pin_4 | GPIO_Pin_3|GPIO_Pin_2 | GPIO_Pin_1 | GPIO_Pin_0);
            ;
    }
}
