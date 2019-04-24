#include "adc_b45k.h"

ADC_HandleTypeDef  hadc;

void adc_init(void) {
	
	GPIO_InitTypeDef GPIO_ADC_Init;

	__HAL_RCC_ADC1_CLK_ENABLE();


	GPIO_ADC_Init.Mode = GPIO_MODE_ANALOG;
	GPIO_ADC_Init.Pin = GPIO_PIN_1;
	GPIO_ADC_Init.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOA, &GPIO_ADC_Init);

	hadc.Instance = ADC1;     //选择ADC1
	hadc.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4; //ADC时钟分频，选择4分频
	hadc.Init.Resolution = ADC_RESOLUTION_12B; //ADC模式，12位
	hadc.Init.DataAlign  = ADC_DATAALIGN_RIGHT; //选择右对齐
	hadc.Init.ScanConvMode = DISABLE;    //禁用扫描模式
	hadc.Init.EOCSelection = DISABLE;    //关闭EOC中断
	hadc.Init.ContinuousConvMode = DISABLE;  //关闭连续转换
	hadc.Init.NbrOfConversion = 1;   //1个转换在规则序列中
	hadc.Init.DiscontinuousConvMode = DISABLE; //禁用不连续采样模式，即开启连续采样，逐次逼近
	hadc.Init.NbrOfConversion = 0; //不连续采样的通道数为0
	hadc.Init.ExternalTrigConv = ADC_SOFTWARE_START; // 使用软件触发
	hadc.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
	hadc.Init.DMAContinuousRequests = DISABLE; //禁用DMA
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


