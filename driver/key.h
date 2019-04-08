#ifndef __key_h
#define __key_h
/*------------------------------------------------------------------------------------*/

#include "STM32F3XX.H"
#include "main.h"
#include "stdio.h"
/*------------------------------------------------------------------------------------*/

typedef enum {

	mode1,
	mode2,

}key_mode;

/*------------------------------------------------------------------------------------*/

#define key0_port				GPIOA
#define key1_port				GPIOA
#define key2_port				GPIOA

#define key0 					GPIO_PIN_4
#define key1					GPIO_PIN_3
#define key2					GPIO_PIN_2

#define key0_read				HAL_GPIO_ReadPin(key0_port, key0)
#define key1_read				HAL_GPIO_ReadPin(key1_port, key1)
#define key2_read				HAL_GPIO_ReadPin(key2_port, key2)

#define key0_push				(uint8_t)1
#define key1_push				(uint8_t)2
#define key2_push				(uint8_t)3
#define key_nopush				(uint8_t)0


/*------------------------------------------------------------------------------------*/

void key_init(void);
uint8_t key_scanf(void);
/*------------------------------------------------------------------------------------*/


#endif  /* __key_h */
/*------------------------------------------------------------------------------------*/

