/*
*                                       LoopaModule Project
*
*@auchor:R&D->sola
			
*@data  :2019.3.13(����ʱ��)
*@desc  : 
          1��nandflash -------------->TOSHIBA-TC58BVG1S3HTA00 
          
          2��debug_usart------------->USART2/
                                            /RX-->PA3   |LED1
                                            /TX-->PA2  	|LED2
                                      
          4��SystemClock------------->72MHz
          
          5��CORE-------------------->CORTEX_M4  
          
          6��USE_Lib----------------->USE_HAL    
*/

/*#INCLUDE--------------------------------------------------------------------*/
#include "main.h"
#include "STM32F3XX.H"
/*#DEFINE---------------------------------------------------------------------*/
#define USE_USART                                                            1
#define USE_LED                                                              0
/*FUNCTION--------------------------------------------------------------------*/
static void SystemClock_Config(void);

extern UART_HandleTypeDef debug_uart2;
/*STRING----------------------------------------------------------------------*/

uint8_t nand_flash_read_str[255];
uint8_t nand_flash_ecc_str[255];

uint32_t data_write[255];
uint32_t data_read[255];


/*----------------------------------------------------------------------------*/
int main(void)
{
 
    HAL_Init();
    /* ����ʱ��Ϊ72MHz */
    SystemClock_Config();
    
    debug_usart_init(115200);
    
    adc_init(); 
    
    ak4556_init();
    ak4556_mode(0); //���ģʽ
    
    nandflash_init();
    
    #if USE_LED
        led_init();
    #endif 
    
    Info_Printf("Ӳ����ʼ�����");
/*----------------------------------------------------------------------------*/     
    uint8_t ID_buff[8];//ID�洢������
    float ad_save[8];  // adc�ɼ��洢��
    //float ad_conv;
/*----------------------------------------------------------------------------*/    
    HAL_Delay(1000);   //�ȴ�����
/*----------------------------------------------------------------------------*/  
    Info_Printf("��ʼ���Գ���");
    
    Info_Printf("nandflash  ��ʼ��λ....");
    nandflash_reset();
    Info_Printf("nandflash  ��λ���");
    Info_Printf("��ȡnandflash-ID....");
    nandflash_read_id(ID_buff); 
    Info_Printf("NAND FLASH ID = %x%x%x%x%x",ID_buff[0],
                                             ID_buff[1],
                                             ID_buff[2],
                                             ID_buff[3],
                                             ID_buff[4]);
    
    Info_Printf("nandflash-ID��ȡ�ɹ�");
    
    
  /* Infinite loop */
    while(1) {

       
       
    }
}

/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow : 
  *            System Clock source            = PLL (HSE)
  *            SYSCLK(Hz)                     = 72000000
  *            HCLK(Hz)                       = 72000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 2
  *            APB2 Prescaler                 = 1
  *            HSE Frequency(Hz)              = 8000000
  *            HSE PREDIV                     = 1
  *            PLLMUL                         = RCC_PLL_MUL9 (9)
  *            Flash Latency(WS)              = 2
  * @param  None
  * @retval None
  */
static void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;
  
  /* Enable HSE Oscillator and activate PLL with HSE as source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct)!= HAL_OK)
  {
    /* ʱ�ӳ�ʼ��ʧ�� */
  }
  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 
     clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK |
                                 RCC_CLOCKTYPE_HCLK   | 
                                 RCC_CLOCKTYPE_PCLK1  | 
                                 RCC_CLOCKTYPE_PCLK2);
  
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;  
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2)!= HAL_OK)
  {
    /* ʱ�ӳ�ʼ��ʧ�� */
  }
}

/*END-------------------------------------------------------------------------*/
