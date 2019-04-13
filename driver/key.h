#ifndef __key_h
#define __key_h
/*------------------------------------------------------------------------------------*/

#include "STM32F3XX.H"
#include "main.h"
#include "stdio.h"
/*------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------*/


#define key1_port				GPIOC
#define key2_port				GPIOC

#define key1					GPIO_PIN_13
#define key2					GPIO_PIN_14

#define key1_read				HAL_GPIO_ReadPin(key1_port, key1)
#define key2_read				HAL_GPIO_ReadPin(key2_port, key2)

#define key1_push				(uint8_t)2
#define key2_push				(uint8_t)3
#define key_nopush				(uint8_t)0

#define key_on                  1
#define key_off                 0

/*------------------------------------------------------------------------------------*/

void key_init(void);
uint8_t key_scanf(void);
/*------------------------------------------------------------------------------------*/


#endif  /* __key_h */
/*------------------------------------------------------------------------------------*/

