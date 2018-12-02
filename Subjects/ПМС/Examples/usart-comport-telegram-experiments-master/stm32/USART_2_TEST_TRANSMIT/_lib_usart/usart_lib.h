#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include <string.h>
#include "stm32f10x_usart.h"

//--------------------
//
// THIS lib uses: 
//				PA9  PA10 	for USART1
//				
//-------------------

// Open UART, configure baudrate and the Tx/Rx
int uart_open(USART_TypeDef* USARTx, uint32_t baud, uint32_t flags);

// Close UART
int uart_close(USART_TypeDef* USARTx);

// Get a character from UART
char uart_getc(USART_TypeDef* USARTx);

// Put a character to UART
int uart_putc(USART_TypeDef* USARTx, char c);

