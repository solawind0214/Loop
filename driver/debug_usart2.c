#include "debug_usart2.h"

UART_HandleTypeDef debug_uart2;

/**************************************************************************************
*@function 	:debug_usart_init
*@input		:bound ->>>(2400-1152000)
*@return	:none
*@author	:sola
*@time		:2019/2/15
**************************************************************************************/
void debug_usart_init(uint32_t bound) {
    
	/* GPIO init */
	GPIO_InitTypeDef GPIO_Init;

	/* ø™∆Ù ±÷” */
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_USART2_CLK_ENABLE();
	
	/* GPIO config */
	GPIO_Init.Alternate = GPIO_AF7_USART2;
	GPIO_Init.Mode = GPIO_MODE_AF_PP;
	GPIO_Init.Pull = GPIO_PULLUP;
	GPIO_Init.Speed = GPIO_SPEED_FREQ_HIGH;
    
	/* TX */
	GPIO_Init.Pin = GPIO_PIN_2;
	HAL_GPIO_Init(GPIOA, &GPIO_Init);
	/* RX */
	GPIO_Init.Pin = GPIO_PIN_3;
    HAL_GPIO_Init(GPIOA, &GPIO_Init);
	/* usart config */
	debug_uart2.Instance = USART2;
	debug_uart2.Init.BaudRate = bound;
	debug_uart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	debug_uart2.Init.Mode = UART_MODE_TX_RX;
    debug_uart2.Init.Parity = UART_PARITY_NONE;
    debug_uart2.Init.StopBits = UART_STOPBITS_1;
    debug_uart2.Init.WordLength = UART_WORDLENGTH_8B;
    debug_uart2.Init.OverSampling = UART_OVERSAMPLING_16;
	HAL_UART_Init(&debug_uart2);
}



/**************************************************************************************
*@function 	:fputc
*@input		:ch,*f(Êñá‰ª∂ÊµÅÊ†ºÂº?  
*@return	:ch
*@author	:sola
*@time		:2019/2/15
**************************************************************************************/
int fputc(int ch,FILE *f) {

	HAL_UART_Transmit(&debug_uart2, (uint8_t *)&ch, 1, 0xffff);
	return (ch);
}

/**************************************************************************************
*@function 	:fputc
*@input		:*f  (ËæìÂÖ•Êñá‰ª∂Êµ?
*@return	:ch
*@author	:sola
*@time		:2019/2/15
**************************************************************************************/
int fgetc(FILE *f) {

	int ch;
	while(__HAL_UART_GET_FLAG(&debug_uart2,UART_FLAG_RXNE)==RESET);
	HAL_UART_Receive(&debug_uart2, (uint8_t *)&ch,1,0xffff);
	return (ch);
}




