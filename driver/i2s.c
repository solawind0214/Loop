/*
*@I2S2 GPIO Configuration    
  PB12     ------> I2S2_WS       LRCK
  PB13     ------> I2S2_CK       BCLK
  PB14     ------> I2S2_ext_SD   SDTO
  PB15     ------> I2S2_SD       SDTI
  PA8     ------> I2S2_MCK       MCLK
    */


#include "i2s.h"

I2S_HandleTypeDef hi2s;
DMA_HandleTypeDef hdma_spi2_rx;


uint32_t loop_rec[255];


static void ak4556_gpio_init() {

    GPIO_InitTypeDef  GPIO_Init;

    /*使能GPIO时钟*/
    __HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();

    GPIO_Init.Alternate = GPIO_AF5_SPI2;
    GPIO_Init.Mode = GPIO_MODE_AF_PP;
    GPIO_Init.Pull = GPIO_NOPULL;
    GPIO_Init.Speed = GPIO_SPEED_FREQ_HIGH;
	
    GPIO_Init.Pin = TC_SDTI_PIN;
    HAL_GPIO_Init(TC_SDTI_PORT, &GPIO_Init);

    GPIO_Init.Pin = TC_SDTO_PIN;
    HAL_GPIO_Init(TC_SDTO_PORT, &GPIO_Init);

    GPIO_Init.Pin = TC_BCLK_PIN;
    HAL_GPIO_Init(TC_BCLK_PORT, &GPIO_Init);

    GPIO_Init.Pin = TC_LRCK_PIN;
    HAL_GPIO_Init(TC_LRCK_PORT, &GPIO_Init);

    GPIO_Init.Pin = TC_MCLK_PIN;
    HAL_GPIO_Init(TC_MCLK_PORT,&GPIO_Init);

    GPIO_Init.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_Init.Pull = GPIO_NOPULL;
    GPIO_Init.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_Init.Pin = TC_PAN_PIN;
    HAL_GPIO_Init(TC_PAN_PORT, &GPIO_Init);

}

static void ak4556_i2s_init(void) {

    __HAL_RCC_SPI2_CLK_ENABLE();                           //开启SPI2时钟
	
    hi2s.Instance = SPI2;                                  //寄存器基地址从SPI2开始
    hi2s.Init.Mode = I2S_MODE_MASTER_TX;                   //使用主机发送模式
    hi2s.Init.AudioFreq = I2S_AUDIOFREQ_48K;               //声音频率使用48KHz  
    hi2s.Init.ClockSource = I2S_CLOCK_SYSCLK;              //使用系统时钟作为时钟源
    hi2s.Init.CPOL = I2S_CPOL_LOW;                         //低电平空闲时间
    hi2s.Init.DataFormat = I2S_DATAFORMAT_24B;             //使用24Bit的数据位
    hi2s.Init.FullDuplexMode = I2S_FULLDUPLEXMODE_ENABLE;  //使用全双工模式
    hi2s.Init.Standard = I2S_STANDARD_MSB;                 //使用左对齐标准
    HAL_I2S_Init(&hi2s);
    __HAL_I2S_ENABLE(&hi2s);
}

static void ak4556_dma_init(void) {
 
    __HAL_RCC_DMA1_CLK_ENABLE();
    
    hdma_spi2_rx.Instance = DMA1_Channel4;
    hdma_spi2_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
    hdma_spi2_rx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_spi2_rx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_spi2_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_spi2_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_spi2_rx.Init.Mode = DMA_NORMAL;
    hdma_spi2_rx.Init.Priority = DMA_PRIORITY_MEDIUM;
    
    HAL_DMA_Init(&hdma_spi2_rx);
    
    __HAL_LINKDMA(&hi2s,hdmarx,hdma_spi2_rx);
    
    HAL_NVIC_SetPriority(DMA1_Channel4_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(DMA1_Channel4_IRQn);
}

void ak4556_init(void) {

    ak4556_gpio_init();
    ak4556_i2s_init();
    ak4556_dma_init();
}

void ak4556_mode(uint8_t mode) {    //mode = 0 输出模式，mode = 1 输入模式

    if(mode==0) {
       hi2s.Instance = SPI2;                                  //寄存器基地址从SPI2开始
       hi2s.Init.Mode = I2S_MODE_SLAVE_RX;                    //使用从机接收模式
       hi2s.Init.AudioFreq = I2S_AUDIOFREQ_48K;               //声音频率使用48KHz  
       hi2s.Init.ClockSource = I2S_CLOCK_SYSCLK;              //使用系统时钟作为时钟源
       hi2s.Init.CPOL = I2S_CPOL_LOW;                         //低电平空闲时间
       hi2s.Init.DataFormat = I2S_DATAFORMAT_24B;             //使用24Bit的数据位
       hi2s.Init.FullDuplexMode = I2S_FULLDUPLEXMODE_ENABLE;  //使用全双工模式
       hi2s.Init.Standard = I2S_STANDARD_MSB;                 //使用左对齐标准
       HAL_I2S_Init(&hi2s);
    }
}

void ak4556_out(uint16_t * pData, uint16_t Size) {

    HAL_I2S_Transmit(&hi2s, pData, Size, 1000);
}

void ak4556_in(uint16_t * pData, uint16_t Size) {

    HAL_I2S_Receive(&hi2s, pData, Size, 1000);
}







