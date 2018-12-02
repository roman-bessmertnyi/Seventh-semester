#include "pc_usart.h"

char pc_res = PC_NO_SYMBOL;

//uint8_t pcGetSympbol(){
//	
//	return PC_NO_SYMBOL;
//}



void USART2_IRQHandler(void)
{
    /* RXNE handler */
    if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
    {
        /* If received 't', toggle LED and transmit 'T' */
        pc_res=(char)USART_ReceiveData(USART2);
      			
			//USART_SendData(USART2, 't');
			
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

void init_usart2(){
		
	/* USART configuration structure for USART1 */
    USART_InitTypeDef usart2_init_struct;
    /* Bit configuration structure for GPIOA PIN9 and PIN10 */
    GPIO_InitTypeDef gpioa_init_struct;
     
    /* Enalbe clock for USART1, AFIO and GPIOA */
    //RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_AFIO | 
    //                     RCC_APB2Periph_GPIOA, ENABLE);
	
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
                            
    /* GPIOA PIN9 alternative function Tx */
    gpioa_init_struct.GPIO_Pin = GPIO_Pin_2;
    gpioa_init_struct.GPIO_Speed = GPIO_Speed_50MHz;
    gpioa_init_struct.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &gpioa_init_struct);
    /* GPIOA PIN10 alternative function Rx */
    gpioa_init_struct.GPIO_Pin = GPIO_Pin_3;
    gpioa_init_struct.GPIO_Speed = GPIO_Speed_50MHz;
    gpioa_init_struct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &gpioa_init_struct);
 
    /* Enable USART1 */
    USART_Cmd(USART2, ENABLE);  
    /* Baud rate 9600, 8-bit data, One stop bit
     * No parity, Do both Rx and Tx, No HW flow control
     */
    usart2_init_struct.USART_BaudRate = 9600;   
    usart2_init_struct.USART_WordLength = USART_WordLength_8b;  
    usart2_init_struct.USART_StopBits = USART_StopBits_1;   
    usart2_init_struct.USART_Parity = USART_Parity_No ;
    usart2_init_struct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    usart2_init_struct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    /* Configure USART1 */
    USART_Init(USART2, &usart2_init_struct);
    /* Enable RXNE interrupt */
    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
    /* Enable USART1 global interrupt */
    NVIC_EnableIRQ(USART2_IRQn);
}

//int uart_open(USART_TypeDef* USARTx, uint32_t baud, uint32_t flags)
//{
//	// This function assumes GPIOA is used for USART

//	GPIO_InitTypeDef GPIO_InitStructure;
//	USART_InitTypeDef USART_InitStructure;
//	
//	GPIO_StructInit(&GPIO_InitStructure);
//	
//	// Enable GPIOA Clock
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
//	
//	if(USARTx == USART1)
//	{
//		// Enable USART1 Clock
//		 /* Enalbe clock for USART1, AFIO and GPIOA */
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_AFIO | 
//                           RCC_APB2Periph_GPIOA, ENABLE);
//		
//		// Initalise Pin Alternate Function Config
//		//GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_1);
//    //GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_1);
//		
//		/* GPIOA PIN9 alternative function Tx */
//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
//    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
//    GPIO_Init(GPIOA, &GPIO_InitStructure);
//    /* GPIOA PIN9 alternative function Rx */
//   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
//    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
//    GPIO_Init(GPIOA, &GPIO_InitStructure);
//	}
//	;

//	// Initialise USART structure
//	USART_StructInit(&USART_InitStructure);
//	
//	// Modify USART_InitStructure for non-default values, e.G.
//	USART_InitStructure.USART_BaudRate = baud;
//	USART_InitStructure.USART_Mode = flags;
//	USART_InitStructure.USART_WordLength = USART_WordLength_9b;
//	USART_InitStructure.USART_Parity = USART_Parity_Even;
//	USART_Init(USARTx, &USART_InitStructure);
//	USART_Cmd(USARTx, ENABLE);
//	
//	return 0;
//}

//char uart_getc(USART_TypeDef* USARTx)
//{
//	//wait income
//	while(USART_GetFlagStatus(USARTx, USART_FLAG_RXNE) == RESET);
//	//if parity error
//	///
//	if(USART_GetFlagStatus(USARTx, USART_FLAG_PE) == SET){
//		while(1);
//	}
//	return USART_ReceiveData(USARTx);
//}
