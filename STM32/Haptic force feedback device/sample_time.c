#include "stm32f4xx.h"           
#include "sample_time.h"
#include "var.h"

void timer10_init(void)
{
	RCC->APB2ENR|=RCC_APB2ENR_TIM10EN;
	TIM10->PSC = 0;
	TIM10->ARR = 159;	// 150us      // 200us : 0 vs 3199
	TIM10->DIER|=(1<<0);
  NVIC_SetPriority(TIM1_UP_TIM10_IRQn,1); 
  NVIC_EnableIRQ(TIM1_UP_TIM10_IRQn);  
}
void timer10_enabled(void)
{
	TIM10->CR1|=(1<<0);
}
void timer10_start(void)
{
	timer10_init();
	timer10_enabled();
}
void timer9_init(void)
{
	RCC->APB2ENR|=RCC_APB2ENR_TIM9EN;
	TIM9->PSC = 0;
	TIM9->ARR = 1599;	// 200us : 0 vs 3199
	TIM9->DIER|=(1<<0);
  //NVIC_SetPriority(TIM1_UP_TIM10_IRQn,1); 
  NVIC_EnableIRQ(TIM1_BRK_TIM9_IRQn);  
}
void timer9_enabled(void)
{
	TIM9->CR1|=(1<<0);
}
void timer9_start(void)
{
	timer9_init();
	timer9_enabled();
}
void TIM1_BRK_TIM9_IRQHandler(void)
{
	TIM9->SR&=~(1<<0);
	
	analog_array[analog_index] = analog_rx[0];
	analog_array_1[analog_index] = analog_rx[1];
	analog_array_2[analog_index] = analog_rx[2];
	
	if (analog_index==999)
	{
		analog_index = 0;
		analog_sum = 0;
		analog_sum_1 = 0;
		analog_sum_2 = 0;
		
		for (int i=0;i<1000;i++)
		{
			analog_sum += analog_array[i];
			analog_sum_1 += analog_array_1[i];
			analog_sum_2 += analog_array_2[i];
		}
		analog_average = analog_sum/1000.0;
		analog_average_1 = analog_sum_1/1000.0;
		analog_average_2 = analog_sum_2/1000.0;
		
		for(float calib = 2.4000; calib < 2.6000; calib+=0.0001)
		{
			current_mA[0] = (850*((float)analog_average/4096.0*3.3 - calib)/0.185);//1.584 
			current_mA[1] = (2050*((float)analog_average_1/4096.0*3.3 - calib)/0.185);//1.584 
			current_mA[2] = (1300*((float)analog_average_2/4096.0*3.3 - calib)/0.185);//1.584 
			
			if((-3<current_mA[0])&&(current_mA[0]<-2))
			{
				vol_calib[0] = calib - 0.01;
			}
			if((0<current_mA[1])&&(current_mA[1]<1))
			{
				vol_calib[1] = calib -0.005;
			}
			if((-1<current_mA[2])&&(current_mA[2]<0))
			{
				vol_calib[2] = calib ;
			}
			if((vol_calib[0]!= 0)&&(vol_calib[1]!= 0)&&(vol_calib[2]!= 0))
			{
				TIM9->CR1&=~(1<<0);
				timer10_enabled();
			}
		}
	}
	else analog_index++;
}

