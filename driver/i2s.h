#ifndef __i2s_h
#define __i2s_h

/*----------------------------------------------------------------------------*/
#include "STM32F3XX.H"
/*----------------------------------------------------------------------------*/
/*
*@I2S2 GPIO Configuration    
  PB12     ------> I2S2_WS       LRCK
  PB13     ------> I2S2_CK       BCLK
  PB14     ------> I2S2_ext_SD   SDTO
  PB15     ------> I2S2_SD       SDTI
  PA8     ------> I2S2_MCK       MCLK
    */
#define TC_SDTI_PIN                         GPIO_PIN_15
#define TC_SDTI_PORT                        GPIOB

#define TC_SDTO_PIN                         GPIO_PIN_14
#define TC_SDTO_PORT                        GPIOB

#define TC_LRCK_PIN                         GPIO_PIN_12
#define TC_LRCK_PORT                        GPIOB

#define TC_BCLK_PIN                         GPIO_PIN_13
#define TC_BCLK_PORT                        GPIOB

#define TC_MCLK_PIN                         GPIO_PIN_8
#define TC_MCLK_PORT                        GPIOA

#define TC_PAN_PIN                          GPIO_PIN_15
#define TC_PAN_PORT                         GPIOA
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
void ak4556_init(void) ;
void ak4556_mode(uint8_t mode);
void ak4556_out(uint16_t * pData, uint16_t Size);
void ak4556_in(uint16_t * pData, uint16_t Size);
/*----------------------------------------------------------------------------*/
#endif
