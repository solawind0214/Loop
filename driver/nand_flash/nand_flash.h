#ifndef nand_flash_h
#define nand_flash_h
/*------------------------------------------------------------------------------------*/
#include "stm32f3xx.h"
#include "main.h"
#include "stdio.h"
/*------------------------------------------------------------------------------------*/                                            
#define TC_D0_Pin GPIO_PIN_0
#define TC_D0_GPIO_Port GPIOB

#define TC_D1_Pin GPIO_PIN_1
#define TC_D1_GPIO_Port GPIOB

#define TC_D2_Pin GPIO_PIN_2
#define TC_D2_GPIO_Port GPIOB

#define TC_CLE_Pin GPIO_PIN_10
#define TC_CLE_GPIO_Port GPIOB

#define TC_ALE_Pin GPIO_PIN_11
#define TC_ALE_GPIO_Port GPIOB

#define TC_WE_Pin GPIO_PIN_9
#define TC_WE_GPIO_Port GPIOA

#define TC_RE_Pin GPIO_PIN_10
#define TC_RE_GPIO_Port GPIOA

#define TC_D3_Pin GPIO_PIN_3
#define TC_D3_GPIO_Port GPIOB

#define TC_D4_Pin GPIO_PIN_4
#define TC_D4_GPIO_Port GPIOB

#define TC_D5_Pin GPIO_PIN_5
#define TC_D5_GPIO_Port GPIOB

#define TC_D6_Pin GPIO_PIN_6
#define TC_D6_GPIO_Port GPIOB

#define TC_D7_Pin GPIO_PIN_7
#define TC_D7_GPIO_Port GPIOB

#define TC_CS_Pin GPIO_PIN_8
#define TC_CS_GPIO_Port GPIOB

#define TC_WP_Pin GPIO_PIN_9
#define TC_WP_GPIO_Port GPIOB
/*------------------------------------------------------------------------------------*/
#define S_DATA_IN			0X80
#define READ1				0X00
#define READ2				0X30
#define	CAC_DATA_OUT_1		0X05
#define CAC_DATA_OUT_2		0XE0
#define	MPP_1_1				0X80
#define	MPP_1_2				0X11
#define	MPP_2_1				0X81
#define	MPP_2_2				0X10

#define NANDFLASH_RESET		0XFF

#define RCOM_ID				0X90		                                                            //读ID指令
#define ADDR_ID 			0X00                                                                    //ID寄存器地址
/*------------------------------------------------------------------------------------*/
//片选脚设置
#define TC_CS_SET()	HAL_GPIO_WritePin(TC_CS_GPIO_Port,TC_CS_Pin,GPIO_PIN_SET)
#define TC_CS_CLR()	HAL_GPIO_WritePin(TC_CS_GPIO_Port,TC_CS_Pin,GPIO_PIN_RESET)

//命令锁存脚设置
#define TC_CLE_SET()	HAL_GPIO_WritePin(TC_CLE_GPIO_Port,TC_CLE_Pin,GPIO_PIN_SET)
#define TC_CLE_CLR()	HAL_GPIO_WritePin(TC_CLE_GPIO_Port,TC_CLE_Pin,GPIO_PIN_RESET)

//地址所存脚设置
#define TC_ALE_SET()	HAL_GPIO_WritePin(TC_ALE_GPIO_Port,TC_ALE_Pin,GPIO_PIN_SET)
#define TC_ALE_CLR()	HAL_GPIO_WritePin(TC_ALE_GPIO_Port,TC_ALE_Pin,GPIO_PIN_RESET)

//读使能脚设置
#define TC_RE_SET()	HAL_GPIO_WritePin(TC_RE_GPIO_Port,TC_RE_Pin,GPIO_PIN_SET)
#define TC_RE_CLR()	HAL_GPIO_WritePin(TC_RE_GPIO_Port,TC_RE_Pin,GPIO_PIN_RESET)

//写使能脚设置
#define TC_WE_SET()	HAL_GPIO_WritePin(TC_WE_GPIO_Port,TC_WE_Pin,GPIO_PIN_SET)
#define TC_WE_CLR()	HAL_GPIO_WritePin(TC_WE_GPIO_Port,TC_WE_Pin,GPIO_PIN_RESET)

//写保护脚设置
#define TC_WP_SET()	HAL_GPIO_WritePin(TC_WP_GPIO_Port,TC_WP_Pin,GPIO_PIN_SET)
#define TC_WP_CLR()	HAL_GPIO_WritePin(TC_WP_GPIO_Port,TC_WP_Pin,GPIO_PIN_RESET)
/*------------------------------------------------------------------------------------*/
void nandflash_init(void);                    //初始化
void nandflash_delay(uint16_t t);
void nandflash_io_dout(void);
void nandflash_io_din(void);
void nandflash_write_byte(GPIO_TypeDef* GPIOx,uint8_t dat);
void nandflash_add_write(uint32_t addr);
void nandflash_read_id(uint8_t *buffer);
void nandflash_reset(void);
void nandflash_data_input(uint8_t *buffer,uint32_t length);
void nandflash_data_read(uint32_t *buffer,uint32_t length);

uint8_t nandflash_read_byte(GPIO_TypeDef* GPIOx);

/*------------------------------------------------------------------------------------*/
#endif  /* nand_flash_h */
/*------------------------------------------------------------------------------------*/

