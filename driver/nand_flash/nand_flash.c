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

*@disp		:�����ݶ˿�����Ϊ���ģʽ	
**************************************************************************************/
void nandflash_io_dout(void) {
    	GPIO_InitTypeDef GPIO_InitStruct;
	
  GPIO_InitStruct.Pin = TC_D0_Pin|TC_D1_Pin|TC_D2_Pin|TC_D3_Pin
												|TC_D4_Pin|TC_D5_Pin|TC_D6_Pin|TC_D7_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;		//���
  GPIO_InitStruct.Pull = GPIO_PULLUP;						//����
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;	//����
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  HAL_GPIO_WritePin(GPIOB, TC_D0_Pin|TC_D1_Pin|TC_D2_Pin			//�����
                          |TC_D3_Pin|TC_D4_Pin|TC_D5_Pin 
                          |TC_D6_Pin|TC_D7_Pin, GPIO_PIN_SET);	                         	
}

/**************************************************************************************
*@function 	:nandflash_io_din
*@input		:none
*@return	:none
*@author	:sola
*@time		:2019/3/11
*@disp		:�����ݶ˿�����Ϊ����ģʽ
**************************************************************************************/
void nandflash_io_din(void) {
    
    GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.Pin = TC_D0_Pin|TC_D1_Pin|TC_D2_Pin|TC_D3_Pin 
                          |TC_D4_Pin|TC_D5_Pin|TC_D6_Pin|TC_D7_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;			//����
  GPIO_InitStruct.Pull = GPIO_PULLUP;					//����
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}

/**************************************************************************************
*@function 	:nandflash_read_byte
*@input		:GPIOx
*@return	:none
*@author	:sola
*@time		:2019/3/11
*@disp		:��ȡ8λ����
**************************************************************************************/
//��ȡ�˿ڵ�8λ����
uint8_t nandflash_read_byte(GPIO_TypeDef* GPIOx)
{
	uint16_t temp;
	temp = GPIOx->IDR;	
	return (uint8_t)(temp&0x00ff);
}

/**************************************************************************************
*@function 	:nandflash_write_byte
*@input		:GPIOx  ��  dat
*@return	:none
*@author	:sola
*@time		:2019/3/11
*@disp		:��GPIOд��8λ����
**************************************************************************************/
//д��˿ڵ�8λ����
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
	nandflash_io_dout();	//���ݿ�����Ϊ���
	TC_RE_SET();            //����RE״̬
	TC_CS_CLR();            //Ƭѡѡ��
	TC_CLE_SET();			//ָ��������Ч	
	TC_WE_CLR();            //���Ϳ�ʼд������
	nandflash_write_byte(GPIOB,RCOM_ID);	//�����IDָ��	RCOM_ID=0x90
	nandflash_delay(5);
	TC_WE_SET();										//дʹ������������
	TC_CLE_CLR();
	nandflash_delay(5);
	TC_ALE_SET();			//��ַ������Ч
	TC_WE_CLR();
	nandflash_write_byte(GPIOB,ADDR_ID);	//���ID��ַ     ADDR_ID=0x00
	nandflash_delay(5);
	TC_WE_SET();			//дʹ������������
	TC_ALE_CLR();
	nandflash_io_din();		//���ݿ�����Ϊ����
	
	//��ȡ5���ֽ�����
	for(i=0;i<5;i++)	
	{
		TC_RE_CLR();		//��ʹ���½����Ƴ�����
		nandflash_delay(5);
		buffer[i] = nandflash_read_byte(GPIOB);	//��ȡ����
		nandflash_delay(5);
		TC_RE_SET();		//��ʹ��������ָ���¸�����
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
*@disp		:��nandflash��д���ַ
**************************************************************************************/
void nand_flash_add_write(uint32_t addr) {

    nandflash_io_dout();            //���ݿ�����Ϊ���ģʽ��
    //uint8_t num;

	TC_WE_SET();                    //��ʼWE״̬ 
	TC_CS_CLR();                    //����Ƭѡѡ��
	TC_CLE_CLR();                   //ʹ��д����
	nandflash_delay(5);             //������Ӧʱ��

	/*first cycle*/
    TC_WE_CLR();                    //����WE�ڣ���ʼд������
    nandflash_write_byte(GPIOB, addr&0xff);
	nandflash_delay(5);
	TC_WE_SET();                    //����WE�ڣ���ʼд������
    nandflash_delay(5);
	/*second cycle*/
    TC_WE_CLR();                    //����WE�ڣ���ʼд������
    nandflash_write_byte(GPIOB, (addr>>8)&0x0f);
	nandflash_delay(5);
	TC_WE_SET();                    //����WE�ڣ���ʼд������
    nandflash_delay(5);
    /*third cycle*/
	TC_WE_CLR();                    //����WE�ڣ���ʼд������
    nandflash_write_byte(GPIOB, (addr>>16)&0xff);
	nandflash_delay(5);
	TC_WE_SET();                    //����WE�ڣ���ʼд������
    nandflash_delay(5);
    /*fourth cycle*/
    TC_WE_CLR();                    //����WE�ڣ���ʼд������
    nandflash_write_byte(GPIOB, (addr>>16)&0xff);
	nandflash_delay(5);
	TC_WE_SET();                    //����WE�ڣ���ʼд������
    nandflash_delay(5);
	/*fifth cycle*/
	TC_WE_CLR();                    //����WE�ڣ���ʼд������
    nandflash_write_byte(GPIOB, (addr>>24)&0x01);
	nandflash_delay(5);
	TC_WE_SET();                    //����WE�ڣ���ʼд������
    nandflash_delay(5);
    TC_CLE_SET();                   //����CLE��ʧ��д
	TC_CS_SET();                    //Ƭѡ���ߣ�ʱ�����
}

/**************************************************************************************
*@function 	:nandflash_data_input
*@input		:*buffer,length
*@return	:none
*@author	:sola
*@time		:2019/4/18
*@disp		:��nandflash��д������
**************************************************************************************/
void nandflash_data_input(uint8_t *buffer,uint32_t length) {

    uint32_t data_num;

    if(length>2111) length = 2111;
	
    TC_CLE_CLR();
    TC_CS_CLR();
    TC_ALE_CLR();
    nandflash_delay(5);
    /*��ʼд������*/
	for(data_num=0;data_num<length;data_num++) {

        TC_WE_CLR();                                   //ʹ��д����
        nandflash_write_byte(GPIOB,buffer[data_num]);  //������д��˿�
        nandflash_delay(5);                            //��������ʱ��
        TC_WE_SET();                                   //����WE,ʧ��д����
        TC_CS_SET();                                   //����Ƭѡ����ʼ���ݻ���
        nandflash_delay(1);                            //��ʱ
        TC_CS_CLR();                                   //����Ƭѡ
	} 
	    TC_CS_SET();                                   //����Ƭѡ
}

/**************************************************************************************
*@function 	:nandflash_serial_read
*@input		:*buffer,length
*@return	:none
*@author	:sola
*@time		:2019/4/18
*@disp		:�������ݶ�ȡ
**************************************************************************************/
void nandflash_serial_read(uint8_t *buffer,uint32_t length) {

    uint8_t data_num;
    nandflash_io_din();             //����ΪIO����
   
    TC_CS_CLR();                    //����Ƭѡ

	
    //TC_RE_CLR();                    //ʹ�ܶ�����  

	for(data_num=0;data_num<length;data_num++) {

	    
        TC_RE_CLR();					                   //ʹ�ܶ�����  
        buffer[data_num] = nandflash_read_byte(GPIOB);     //�����ݱ��浽buffer������
        nandflash_delay(5);
		TC_RE_SET();
        nandflash_delay(5);
	}
	TC_CS_SET();                                           //����Ƭѡ��ʧ�ܣ�����ʱ��
}


