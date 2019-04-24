#include "tim.h"


TIM_HandleTypeDef tim6_htim;
float ad_conv1;
float ad_conv1_old = 0;

void tim6_init(uint16_t period,uint16_t prescaler) {

	

	tim6_htim.Instance = TIM6;
	tim6_htim.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	tim6_htim.Init.CounterMode = TIM_COUNTERMODE_UP;
	tim6_htim.Init.Period = period;
	tim6_htim.Init.Prescaler = prescaler;
    HAL_TIM_Base_Init(&tim6_htim);

	HAL_TIM_Base_Start_IT(&tim6_htim);
}

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef * htim) {


	__HAL_RCC_TIM6_CLK_ENABLE();
	HAL_NVIC_SetPriority(TIM6_DAC_IRQn, 1,3);
	HAL_NVIC_EnableIRQ(TIM6_DAC_IRQn);
}

void TIM6_DAC1_IRQHandler(void) {

	HAL_TIM_IRQHandler(&tim6_htim);
}


static float chuli(float num) {

    int a,c;
    float b,d;
    
    a = (int)num;
   // printf("1  a=%d\n",a);
    
    b = num-(float)a;
    b = b*100;
   // printf("2  b=%f\n",b);
        
    c = (int)b;
    //printf("3  c=%d\n",c);
    
    d = (float)a + ((float)c)/100; 
    //printf("4  d=%f\n",d);
    return d;
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef * htim) {

    float num = 0.01;
    
	if(htim==(&tim6_htim)) {

		ad_conv1 = (3.3/4096)*get_ad_val();
        
        ad_conv1 = chuli(ad_conv1);
      
        if(((ad_conv1 - ad_conv1_old)>num) || ((ad_conv1_old - ad_conv1)>num)) {
            
            printf("ad_vlude = %.2f\n",ad_conv1);
        }
        else {
            
        }
       ad_conv1_old = ad_conv1;
	}
}



