#define USE_STDPERIPH_DRIVER

#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"

#include "stm32f10x_usart.h"
#include "usart_lib.h"
#include "tm1637.h"
#include "brown_delay.h"


// RESEIVER 

/*************************
 * stm32 uart main.c
 Tx PORTA9
 Rx PORTA10
 
 PORTC Pin13 toggeld -> 
                        in void GPIOC_Init(void) 
                        led_toggle(void)
 *************************/
 

 
/* User defined function prototypes */

  


void GPIOC_Init(void);
void USART1_Init(void);
void led_toggle(void);
void Display_Loop_1_effect(int times);
void Display_Loop_2_effect(int times);
void Display_Loop_4_effect(int times);
void Display_Loop_4_effect_2(int times);
void Display_Loop_dash_effect_1(int times);
char tem_res;
int displayLoopDalay = 400; 

void Display_Test(){
	TM1637_display_all(55);
	delay_from_Brown(1000);
	TM1637_display_all(77);
	delay_from_Brown(1000);
}


int main(void)
{
    
    sys_tick_ini();
    TM1637_init();	
    TM1637_brightness(BRIGHT_DARKEST); 
    //uint16_t j = 55;
    //Display_Test();
    TM1637_clearDisplay();
    /* Initialize GPIOA PIN8 */
   // GPIOC_Init();
    /* Initialize USART1 */
    USART1_Init();
 tem_res='4';
 char old_tem_res=tem_res;
	uint8_t a=0x75;

    while(1)
    {
			if(old_tem_res!=tem_res){
        switch (tem_res) {
					case 0:
						Display_Loop_1_effect(5);
						break;
					case 1:
						Display_Loop_4_effect(5);
						break;
					case 2:
						Display_Loop_2_effect(5);
						break;
					case 3:
						Display_Loop_dash_effect_1(5);
						break;
					default:
						//1
						break;
				}
				//delay_from_Brown(600);
				old_tem_res = tem_res;
			}else{
        TM1637_display_all('T');
				//Display_Loop_dash_effect_1_next(1);
			}
    }
}   
 
void Display_Loop_1_effect(int times){			
	//по очереди 1 сектор по всему циферблату
	uint32_t b=0x01;
	times*=32;//1 cycle
	uint8_t shift = 1;
    while(times--)
    {        
			delay_from_Brown(displayLoopDalay);			
			TM1637_display_all_custom(b);			
			//постоянное смещение сегментов shift=8
			b= (b >> (sizeof(b)*8 - shift))| (b << shift) ;						
    }
}

void Display_Loop_4_effect(int times){	
	//по очереди в каждой цифре 1 сектор
	uint32_t b=0x01010101;
	uint8_t shift = 1;
	times*=8;
    while(times--)
    {        
			delay_from_Brown(displayLoopDalay);			
			TM1637_display_all_custom(b);			
			//постоянное смещение сегментов shift=8
			b= (b >> (sizeof(b)*8 - shift))| (b << shift) ;						
    }
}

void Display_Loop_2_effect(int times){			
	//по очереди 1 сектор по всему циферблату
	uint32_t b=0x0101;
	times*=6;//1 cycle
	uint8_t shift = 1;
    while(times--)
    { 
			if(b==0x00004040)
				b=0x0101;			
			delay_from_Brown(displayLoopDalay);			
			TM1637_display_all_custom(b);			
			//постоянное смещение сегментов shift=8
			b= (b >> (sizeof(b)*8 - shift))| (b << shift) ;									
    }
}
void Display_Loop_4_effect_2(int times){			
	//Все ячейки по кругу обходит одновременно
	uint32_t b=0x01010101;
	times*=6;//1 cycle
	uint8_t shift = 1;
    while(times--)
    { 
			if(b==0x40404040)
				b=0x01010101;			
			delay_from_Brown(displayLoopDalay);			
			TM1637_display_all_custom(b);			
			//постоянное смещение сегментов shift=8
			b= (b >> (sizeof(b)*8 - shift))| (b << shift) ;									
    }
}

void Display_Loop_dash_effect_1(int times){			
	//по очереди тире едет в верхнем ряду, в среднем и в нижнем
	uint32_t b=0x01;
	uint8_t shift = 8;
	int displayLoopDalay2=200;
	times*=3;
	
    while(times--)
    { 			
			for(int i=0;i<4;i++){
				delay_from_Brown(displayLoopDalay2);			
				TM1637_display_all_custom(b);			
				//постоянное смещение сегментов shift=8
				b= (b >> (sizeof(b)*8 - shift))| (b << shift) ;					
			}			
			if(times%3==2)
				b=0x40;			
			else if(times%3==1)
				b=0x08;
			else 
				b=0x01;											
    }
}
/***********************************************
 * Initialize GPIOC PIN8 as push-pull output
 ***********************************************/
void GPIOC_Init(void)
{
    /* Bit configuration structure for GPIOA PIN8 */
    GPIO_InitTypeDef gpioC_init_struct = { GPIO_Pin_13, GPIO_Speed_50MHz, 
                                           GPIO_Mode_Out_PP };
                                             
    /* Enable PORT C clock */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    /* Initialize GPIOC: 50MHz, PIN8, Push-pull Output */
    GPIO_Init(GPIOC, &gpioC_init_struct);   
     
    /* Turn off LED to start with */
    GPIO_SetBits(GPIOC, GPIO_Pin_13);
}
 
/*****************************************************
 * Initialize USART1: enable interrupt on reception
 * of a character
 *****************************************************/
void USART1_Init(void)
{
    /* USART configuration structure for USART1 */
    USART_InitTypeDef usart1_init_struct;
    /* Bit configuration structure for GPIOA PIN9 and PIN10 */
    GPIO_InitTypeDef gpioa_init_struct;
     
    /* Enalbe clock for USART1, AFIO and GPIOA */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_AFIO | 
                           RCC_APB2Periph_GPIOA, ENABLE);
                            
    /* GPIOA PIN9 alternative function Tx */
    gpioa_init_struct.GPIO_Pin = GPIO_Pin_9;
    gpioa_init_struct.GPIO_Speed = GPIO_Speed_50MHz;
    gpioa_init_struct.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &gpioa_init_struct);
    /* GPIOA PIN10 alternative function Rx */
    gpioa_init_struct.GPIO_Pin = GPIO_Pin_10;
    gpioa_init_struct.GPIO_Speed = GPIO_Speed_50MHz;
    gpioa_init_struct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &gpioa_init_struct);
 
    /* Enable USART1 */
    USART_Cmd(USART1, ENABLE);  
    /* Baud rate 9600, 8-bit data, One stop bit
     * No parity, Do both Rx and Tx, No HW flow control
     */
    usart1_init_struct.USART_BaudRate = 9600;   
    usart1_init_struct.USART_WordLength = USART_WordLength_8b;  
    usart1_init_struct.USART_StopBits = USART_StopBits_1;   
    usart1_init_struct.USART_Parity = USART_Parity_No ;
    usart1_init_struct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    usart1_init_struct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    /* Configure USART1 */
    USART_Init(USART1, &usart1_init_struct);
    /* Enable RXNE interrupt */
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
    /* Enable USART1 global interrupt */
    NVIC_EnableIRQ(USART1_IRQn);
}
 
/*******************************************
 * Toggle LED 
 *******************************************/
void led_toggle(void)
{
    /* Read LED output (GPIOA PIN8) status */
    uint8_t led_bit = GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_13);
     
    /* If LED output set, clear it */
    if(led_bit == (uint8_t)Bit_SET)
    {
        GPIO_ResetBits(GPIOC, GPIO_Pin_13);
    }
    /* If LED output clear, set it */
    else
    {
        GPIO_SetBits(GPIOC, GPIO_Pin_13);
    }
}
 
/**********************************************************
 * USART1 interrupt request handler: on reception of a 
 * character 't', toggle LED and transmit a character 'T'
 *********************************************************/
void USART1_IRQHandler(void)
{
    /* RXNE handler */
    if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
    {
        /* If received 't', toggle LED and transmit 'T' */
        tem_res=(char)USART_ReceiveData(USART1);
        USART_SendData(USART1, tem_res);
            /* Wait until Tx data register is empty, not really 
             * required for this example but put in here anyway.
             */
            /*
            while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET)
            {
            }*/
      
    }
     
    /* ------------------------------------------------------------ */

}

