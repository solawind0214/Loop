#include "nand_flash.h"

/**************************************************************************************
*@function 	:nand_flash_init
*@input		:none
*@return	:none
*@author	:sola
*@time		:2019/3/11
**************************************************************************************/

void nandflash_init(void) {
        
    GPIO_InitTypeDef GPIO_InitStruct;

    /* GPIO Ports Clock Enable */
    __HAL_RCC_GPIOF_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(GPIOB, TC_CLE_Pin
                            |TC_ALE_Pin
                            |TC_CS_Pin
                            |TC_WP_Pin, 
                                GPIO_PIN_SET);

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(GPIOA, TC_WE_Pin
                            |TC_RE_Pin, 
                                GPIO_PIN_SET);

    /*Configure GPIO pins : PBPin PBPin PBPin PBPin 
                           PBPin PBPin PBPin PBPin */
    GPIO_InitStruct.Pin = TC_D0_Pin|TC_D1_Pin|TC_D2_Pin|TC_D3_Pin 
                          |TC_D4_Pin|TC_D5_Pin|TC_D6_Pin|TC_D7_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /*Configure GPIO pins : PBPin PBPin PBPin PBPin */
    GPIO_InitStruct.Pin = TC_CLE_Pin|TC_ALE_Pin|TC_CS_Pin|TC_WP_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /*Configure GPIO pins : PAPin PAPin */
    GPIO_InitStruct.Pin = TC_WE_Pin|TC_RE_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
  
  
    TC_CLE_CLR();
	TC_ALE_CLR();
	TC_WE_SET();
	TC_RE_SET();
	TC_CS_SET();
	TC_WP_SET();
}


/**************************************************************************************
*@function 	:nandflash_delay
*@input		:t
*@return	:none
*@author	:sola
*@time		:2019/3/11
**************************************************************************************/
void nandflash_delay(uint16_t t) {

	while(t--);
}

/**************************************************************************************
*@function 	:nandflash_io_dout
*@input		:none
*@return	:none
*@author	:sola
*@time		:2019/3/11

*@disp		:将数据端口设置为输出模式	
**************************************************************************************/
void nandflash_io_dout(void) {
    	GPIO_InitTypeDef GPIO_InitStruct;
	
  GPIO_InitStruct.Pin = TC_D0_Pin|TC_D1_Pin|TC_D2_Pin|TC_D3_Pin
												|TC_D4_Pin|TC_D5_Pin|TC_D6_Pin|TC_D7_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;		//输出
  GPIO_InitStruct.Pull = GPIO_PULLUP;						//上拉
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;	//低速
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  HAL_GPIO_WritePin(GPIOB, TC_D0_Pin|TC_D1_Pin|TC_D2_Pin			//输出高
                          |TC_D3_Pin|TC_D4_Pin|TC_D5_Pin 
                          |TC_D6_Pin|TC_D7_Pin, GPIO_PIN_SET);	                         	
}

/**************************************************************************************
*@function 	:nandflash_io_din
*@input		:none
*@return	:none
*@author	:sola
*@time		:2019/3/11
*@disp		:将数据端口设置为输入模式
**************************************************************************************/
void nandflash_io_din(void) {
    
    GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.Pin = TC_D0_Pin|TC_D1_Pin|TC_D2_Pin|TC_D3_Pin 
                          |TC_D4_Pin|TC_D5_Pin|TC_D6_Pin|TC_D7_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;			//输入
  GPIO_InitStruct.Pull = GPIO_PULLUP;					//上拉
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}

/**************************************************************************************
*@function 	:nandflash_read_byte
*@input		:GPIOx
*@return	:none
*@author	:sola
*@time		:2019/3/11
*@disp		:读取8位数据
**************************************************************************************/
//读取端口低8位数据
uint8_t nandflash_read_byte(GPIO_TypeDef* GPIOx)
{
	uint16_t temp;
	temp = GPIOx->IDR;	
	return (uint8_t)(temp&0x00ff);
}

/**************************************************************************************
*@function 	:nandflash_write_byte
*@input		:GPIOx  ，  dat
*@return	:none
*@author	:sola
*@time		:2019/3/11
*@disp		:向GPIO写入8位数据
**************************************************************************************/
//写入端口低8位数据
void nandflash_write_byte(GPIO_TypeDef* GPIOx,uint8_t dat)
{
	uint16_t temp;
	temp = GPIOx->ODR;
	temp &= 0xff00;
	temp |= dat;
	GPIOx->ODR = temp;
}

/**************************************************************************************
*@function 	:nand_flash_read_id
*@input		:*buffer
*@return	:none
*@author	:sola
*@time		:2019/3/11
**************************************************************************************/
void nandflash_read_id(uint8_t *buffer) {

	uint8_t i;	
	nandflash_io_dout();	//数据口配置为输出
	TC_RE_SET();            //拉高RE状态
	TC_CS_CLR();            //片选选中
	TC_CLE_SET();			//指令锁存有效	
	TC_WE_CLR();            //拉低开始写入锁存
	nandflash_write_byte(GPIOB,RCOM_ID);	//输出读ID指令	RCOM_ID=0x90
	nandflash_delay(5);
	TC_WE_SET();										//写使能上升沿锁存
	TC_CLE_CLR();
	nandflash_delay(5);
	TC_ALE_SET();			//地址锁存有效
	TC_WE_CLR();
	nandflash_write_byte(GPIOB,ADDR_ID);	//输出ID地址     ADDR_ID=0x00
	nandflash_delay(5);
	TC_WE_SET();			//写使能上升沿锁存
	TC_ALE_CLR();
	nandflash_io_din();		//数据口配置为输入
	
	//读取5个字节数据
	for(i=0;i<5;i++)	
	{
		TC_RE_CLR();		//读使能下降沿移出数据
		nandflash_delay(5);
		buffer[i] = nandflash_read_byte(GPIOB);	//读取数据
		nandflash_delay(5);
		TC_RE_SET();		//读使能上升沿指向下个数据
		nandflash_delay(5);
	}
	TC_CS_SET();
}

/**************************************************************************************
*@function 	:nand_flash_reset
*@input		:*buffer
*@return	:none
*@author	:sola
*@time		:2019/3/11
**************************************************************************************/
void nandflash_reset(void) {

	nandflash_write_byte(GPIOB, NANDFLASH_RESET);
}

/**************************************************************************************
*@function 	:nand_flash_add_write
*@input		:*buffer
*@return	:none
*@author	:sola
*@time		:2019/4/18
*@disp		:向nandflash中写入地址
**************************************************************************************/
void nand_flash_add_write(uint32_t addr) {

    nandflash_io_dout();            //数据口配置为输出模式、
    //uint8_t num;

	TC_WE_SET();                    //初始WE状态 
	TC_CS_CLR();                    //拉低片选选中
	TC_CLE_CLR();                   //使能写命令
	nandflash_delay(5);             //给出反应时间

	/*first cycle*/
    TC_WE_CLR();                    //拉低WE口，开始写入数据
    nandflash_write_byte(GPIOB, addr&0xff);
	nandflash_delay(5);
	TC_WE_SET();                    //拉高WE口，开始写入数据
    nandflash_delay(5);
	/*second cycle*/
    TC_WE_CLR();                    //拉低WE口，开始写入数据
    nandflash_write_byte(GPIOB, (addr>>8)&0x0f);
	nandflash_delay(5);
	TC_WE_SET();                    //拉高WE口，开始写入数据
    nandflash_delay(5);
    /*third cycle*/
	TC_WE_CLR();                    //拉低WE口，开始写入数据
    nandflash_write_byte(GPIOB, (addr>>16)&0xff);
	nandflash_delay(5);
	TC_WE_SET();                    //拉高WE口，开始写入数据
    nandflash_delay(5);
    /*fourth cycle*/
    TC_WE_CLR();                    //拉低WE口，开始写入数据
    nandflash_write_byte(GPIOB, (addr>>16)&0xff);
	nandflash_delay(5);
	TC_WE_SET();                    //拉高WE口，开始写入数据
    nandflash_delay(5);
	/*fifth cycle*/
	TC_WE_CLR();                    //拉低WE口，开始写入数据
    nandflash_write_byte(GPIOB, (addr>>24)&0x01);
	nandflash_delay(5);
	TC_WE_SET();                    //拉高WE口，开始写入数据
    nandflash_delay(5);
    TC_CLE_SET();                   //拉高CLE，失能写
	TC_CS_SET();                    //片选拉高，时序结束
}

/**************************************************************************************
*@function 	:nandflash_data_input
*@input		:*buffer,length
*@return	:none
*@author	:sola
*@time		:2019/4/18
*@disp		:向nandflash中写入数据
**************************************************************************************/
void nandflash_data_input(uint8_t *buffer,uint32_t length) {

    uint32_t data_num;

    if(length>2111) length = 2111;
	
    TC_CLE_CLR();
    TC_CS_CLR();
    TC_ALE_CLR();
    nandflash_delay(5);
    /*开始写入数据*/
	for(data_num=0;data_num<length;data_num++) {

        TC_WE_CLR();                                   //使能写数据
        nandflash_write_byte(GPIOB,buffer[data_num]);  //将数据写入端口
        nandflash_delay(5);                            //给出缓冲时间
        TC_WE_SET();                                   //拉高WE,失能写数据
        TC_CS_SET();                                   //拉高片选，开始数据缓冲
        nandflash_delay(1);                            //延时
        TC_CS_CLR();                                   //拉低片选
	} 
	    TC_CS_SET();                                   //拉低片选
}

/**************************************************************************************
*@function 	:nandflash_serial_read
*@input		:*buffer,length
*@return	:none
*@author	:sola
*@time		:2019/4/18
*@disp		:串行数据读取
**************************************************************************************/
void nandflash_serial_read(uint8_t *buffer,uint32_t length) {

    uint8_t data_num;
    nandflash_io_din();             //配置为IO输入
   
    TC_CS_CLR();                    //拉低片选

	
    //TC_RE_CLR();                    //使能读功能  

	for(data_num=0;data_num<length;data_num++) {

	    
        TC_RE_CLR();					                   //使能读功能  
        buffer[data_num] = nandflash_read_byte(GPIOB);     //将数据保存到buffer数组中
        nandflash_delay(5);
		TC_RE_SET();
        nandflash_delay(5);
	}
	TC_CS_SET();                                           //拉高片选，失能，结束时序
}


