#include "adc_b45k.h"

ADC_HandleTypeDef  hadc;

void adc_init(void) {
	
	GPIO_InitTypeDef GPIO_ADC_Init;

	__HAL_RCC_ADC1_CLK_ENABLE();


	GPIO_ADC_Init.Mode = GPIO_MODE_ANALOG;
	GPIO_ADC_Init.Pin = GPIO_PIN_1;
	GPIO_ADC_Init.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOA, &GPIO_ADC_Init);

	hadc.Instance = ADC1;     //ѡ��ADC1
	hadc.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4; //ADCʱ�ӷ�Ƶ��ѡ��4��Ƶ
	hadc.Init.Resolution = ADC_RESOLUTION_12B; //ADCģʽ��12λ
	hadc.Init.DataAlign  = ADC_DATAALIGN_RIGHT; //ѡ���Ҷ���
	hadc.Init.ScanConvMode = DISABLE;    //����ɨ��ģʽ
	hadc.Init.EOCSelection = DISABLE;    //�ر�EOC�ж�
	hadc.Init.ContinuousConvMode = DISABLE;  //�ر�����ת��
	hadc.Init.NbrOfConversion = 1;   //1��ת���ڹ���������
	hadc.Init.DiscontinuousConvMode = DISABLE; //���ò���������ģʽ��������������������αƽ�
	hadc.Init.NbrOfConversion = 0; //������������ͨ����Ϊ0
	hadc.Init.ExternalTrigConv = ADC_SOFTWARE_START; // ʹ���������
	hadc.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
	hadc.Init.DMAContinuousRequests = DISABLE; //����DMA
	HAL_ADC_Init(&hadc);
}

uint16_t get_ad_val(void) {

	ADC_ChannelConfTypeDef  sConfig;

	sConfig.Channel = ADC_CHANNEL_2;
	sConfig.Offset = 0;
	sConfig.Rank = 1;
    sConfig.SamplingTime = ADC_SAMPLETIME_61CYCLES_5;
	HAL_ADC_ConfigChannel(&hadc, &sConfig);

	HAL_ADC_Start(&hadc);
	HAL_ADC_PollForConversion(&hadc,10);
	
	return (uint16_t)HAL_ADC_GetValue(&hadc);
}


