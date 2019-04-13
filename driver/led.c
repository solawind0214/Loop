#include "led.h"


/*******************************************************************************************************
*@function	:led_init
*@input		:none
*@return	:none
*@author	:sola
*@time		:2019/2/14
*******************************************************************************************************/
void led_init(void) {

    /* GPIO�ṹ��������� */
    GPIO_InitTypeDef  GPIO_Init;
	
    /* ����GPIOʱ�� */
    led1_clk();

    /*GPIO  ���� */
    GPIO_Init.Mode = GPIO_MODE_OUTPUT_PP; 	
    GPIO_Init.Pin = led1;				    
    GPIO_Init.Pull = GPIO_NOPULL;			
    GPIO_Init.Speed = GPIO_SPEED_FREQ_HIGH;		
    HAL_GPIO_Init(led1_port, &GPIO_Init);		

    GPIO_Init.Pin = led2;				   
    HAL_GPIO_Init(led2_port,&GPIO_Init);
    
    led_off(led1);
    led_off(led2);
    
}

/*******************************************************************************************************
*@function	:led_on
*@input		:ledx
*@return	:none
*@author	:sola
*@time		:2019/2/14
*******************************************************************************************************/

void led_on(uint16_t ledx) {

    if(ledx==led1) { 					//选择LED1

        HAL_GPIO_WritePin(led1_port, ledx, GPIO_PIN_RESET );
	
    }
    else if(ledx==led2) {
        HAL_GPIO_WritePin(led2_port, ledx, GPIO_PIN_RESET);
    }
    else {
		
    }
}


/*******************************************************************************************************
*@function	:led_off
*@input		:ledx
*@return	:none
*@author	:sola
*@time		:2019/2/14
*******************************************************************************************************/

void led_off(uint16_t ledx) {

	if(ledx==led1) { 					//选择LED1

		HAL_GPIO_WritePin(led1_port, led1, GPIO_PIN_SET );
	
	}
	else if(ledx==led2) {


		HAL_GPIO_WritePin(led2_port, led2, GPIO_PIN_SET);
	}
	else {
		
	}
}





