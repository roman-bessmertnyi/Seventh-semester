#include "usart_lib.h"

int uart_open(USART_TypeDef* USARTx, uint32_t baud, uint32_t flags)
{
	// This function assumes GPIOA is used for USART

	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	
	GPIO_StructInit(&GPIO_InitStructure);
	
	// Enable GPIOA Clock
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	if(USARTx == USART1)
	{
		// Enable USART1 Clock
		 /* Enalbe clock for USART1, AFIO and GPIOA */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_AFIO | 
                           RCC_APB2Periph_GPIOA, ENABLE);
		
		// Initalise Pin Alternate Function Config
		//GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_1);
    //GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_1);
		
		/* GPIOA PIN9 alternative function Tx */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    /* GPIOA PIN9 alternative function Rx */
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
	}
	;

	// Initialise USART structure
	USART_StructInit(&USART_InitStructure);
	
	// Modify USART_InitStructure for non-default values, e.G.
	USART_InitStructure.USART_BaudRate = baud;
	USART_InitStructure.USART_Mode = flags;
	USART_InitStructure.USART_WordLength = USART_WordLength_9b;
	USART_InitStructure.USART_Parity = USART_Parity_Even;
	USART_Init(USARTx, &USART_InitStructure);
	USART_Cmd(USARTx, ENABLE);
	
	return 0;
}

char uart_getc(USART_TypeDef* USARTx)
{
	//wait income
	while(USART_GetFlagStatus(USARTx, USART_FLAG_RXNE) == RESET);
	//if parity error
	///
	if(USART_GetFlagStatus(USARTx, USART_FLAG_PE) == SET){
		while(1);
	}
	return USART_ReceiveData(USARTx);
}
int uart_putc(USART_TypeDef* USARTx, char c)
{
	while(USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET);
	USART_SendData(USARTx, c);
	
	return 0;
}
