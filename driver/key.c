#include "key.h"

/**************************************************************************************
*@function 	:key_init
*@input		:none
*@return	:none
*@author	:sola
*@time		:2019/2/15
**************************************************************************************/

void key_init(void) {

	GPIO_InitTypeDef  GPIO_Init;

	/* 开启时钟 */
	__HAL_RCC_GPIOB_CLK_ENABLE();

	/* 配置IO口 */
	GPIO_Init.Mode = GPIO_MODE_INPUT;
	GPIO_Init.Pull = GPIO_NOPULL;
	GPIO_Init.Speed = GPIO_SPEED_FREQ_HIGH; 
	/* 初始化对应的IO口 */
	GPIO_Init.Pin = key1;
	HAL_GPIO_Init(key1_port, &GPIO_Init);

	GPIO_Init.Pin = key2;
	HAL_GPIO_Init(key2_port, &GPIO_Init);
	
}

/**************************************************************************************
*@function 	:key_scanf
*@input		:none
*@return	:none
*@author	:sola
*@time		:2019/2/15
**************************************************************************************/
uint8_t key_scanf(void) {

	uint8_t key_up=1;
	if(key_up && (key1_read==0 || key2_read==0)) {
		
		HAL_Delay(10);
		key_up=0;
        
		if		(key1_read==key_on)	return key1_push;
		else if	(key2_read==key_on)	return key2_push;
		
	}   else if (key1_read==key_off && key2_read==key_off) {

        
	}
    
	return 0;
}










