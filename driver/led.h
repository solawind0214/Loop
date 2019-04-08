#ifndef __led_h
#define __led_h

#include "STM32F3XX.H"

/*------------------------------------------------------------------------------------*/


#define led1_clk()                  __HAL_RCC_GPIOA_CLK_ENABLE()
#define led2_clk()                  __HAL_RCC_GPIOA_CLK_ENABLE()

#define led1_port					GPIOA					
#define led2_port					GPIOA

#define led1						GPIO_PIN_2
#define led2						GPIO_PIN_3




/*------------------------------------------------------------------------------------*/
void led_init(void);
void led_on(uint16_t ledx);
void led_off(uint16_t ledx);
/*------------------------------------------------------------------------------------*/
#endif /*led_h*/
/*------------------------------------------------------------------------------------*/

