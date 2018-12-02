#include "lib_keyboard.h"

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"




void init_keypad(void){    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);// BUS is ON
    
    GPIO_InitTypeDef      KEYPAD_COL_B_STRUCT; 
		//Init columns 
    KEYPAD_COL_B_STRUCT.GPIO_Pin =     GPIO_Pin_13 |    // KEEP HARD PINS 
                                       GPIO_Pin_14 |
                                       GPIO_Pin_15;
    KEYPAD_COL_B_STRUCT.GPIO_Mode = GPIO_Mode_Out_OD;
		KEYPAD_COL_B_STRUCT.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOB, &KEYPAD_COL_B_STRUCT);
			
		// Init rows
		GPIO_InitTypeDef KEYPAD_ROW_B_STRUCT;
		KEYPAD_ROW_B_STRUCT.GPIO_Pin =     GPIO_Pin_12 |    // KEEP HARD PINS 
																				 GPIO_Pin_11 |
																				 GPIO_Pin_10 |
																				 GPIO_Pin_9;
		KEYPAD_ROW_B_STRUCT.GPIO_Mode = GPIO_Mode_IPU;
		KEYPAD_ROW_B_STRUCT.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOB, &KEYPAD_ROW_B_STRUCT);
}


uint8_t keypadGetKey(void)
{
	
	GPIO_SetBits(GPIOB, GPIO_Pin_13);
	GPIO_SetBits(GPIOB, GPIO_Pin_14);
	GPIO_SetBits(GPIOB, GPIO_Pin_15);
	
	// Scan column 2 (column 2 pin is grounded, other column pins is open drain)
	GPIO_SetBits(GPIOB, GPIO_Pin_13);
	GPIO_SetBits(GPIOB, GPIO_Pin_14);
	GPIO_ResetBits(GPIOB, GPIO_Pin_15);
	// Read rows
	if (!GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_9))
		return '3';
	if (!GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_10))
		return '6';
	if (!GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11))
		return '9';
	if (!GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_12))
		return '#';	
		
	// Scan column 1 (column 1 pin is grounded, other column pins is open drain)
	GPIO_SetBits(GPIOB, GPIO_Pin_13);
	GPIO_ResetBits(GPIOB, GPIO_Pin_14);
	GPIO_SetBits(GPIOB, GPIO_Pin_15);
	// Read rows
	if (!GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_9))
		return '2';
	if (!GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_10))
		return '5';
	if (!GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11))
		return '8';
	if (!GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_12))
		return '0';
		
	
	// Scan column 0 (column 0 pin is grounded, other column pins is open drain)
	GPIO_ResetBits(GPIOB, GPIO_Pin_13);
	GPIO_SetBits(GPIOB,GPIO_Pin_14);
	GPIO_SetBits(GPIOB, GPIO_Pin_15);
	// Read rows
	if (!GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_9))
		return '1';
	if (!GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_10))
		return '4';
	if (!GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11))
		return '7';
	if (!GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_12))
		return '*';
	
	return KEYPAD_NO_PRESSED;
}






//Example:
//	while(1){
//	 key = keypadGetKey();
//	 handleKeyPress_switch(key);
//	}
void handleKeyPress_switch(uint8_t key) {
	
    switch (key)  {
        case KEYPAD_NO_PRESSED: 
            //...
            break;				
       case '0': 
            //...				 
            break;
        case '1': 
            //...
            break;				       
        case '2': 
            //...
            break;				
       case '3': 
            //...
            break;
        case '4': 
            //...
            break;				
        case '5': 
            //...
            break;
        case '6': 
            //...
            break;
        case '7': 
            //...
            break;
        case '8': 
            //...
            break;
        case '9': 
            //...
            break;
        case '*': 
            //...
            break; 
        case '#': 
            //...
						break;
        default:
            ;
    }
}


