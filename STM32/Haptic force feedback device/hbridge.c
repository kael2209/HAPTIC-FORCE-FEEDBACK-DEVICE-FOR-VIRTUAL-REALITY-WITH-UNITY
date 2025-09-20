#include "stm32f4xx.h"         
#include "hbridge.h"

void timer1_pwm_init(void)
{
	// TIMER 1 Channel 1 2 3 4 PA8,PA9,PA10,PA11
	RCC->AHB1ENR|=RCC_AHB1ENR_GPIOAEN;
	GPIOA->MODER|=(2<<16)|(2<<18)|(2<<20)|(2<<22);
	GPIOA->OSPEEDR|=(2<<16)|(2<<18)|(2<<20)|(2<<22);
	GPIOA->AFR[1]|=(1<<0)|(1<<4)|(1<<8)|(1<<12);
	RCC->APB2ENR|=RCC_APB2ENR_TIM1EN;
	TIM1->PSC=0;
	TIM1->ARR=640;	// 25kHz
	TIM1->CCR1 = 0;
	TIM1->CCR2 = 0;
	TIM1->CCR3 = 0;
	TIM1->CCR4 = 0;
	TIM1->CCMR1|=(6<<4)|(6<<12);
	TIM1->CCMR2|=(6<<4)|(6<<12);
	TIM1->CCER|=(1<<0)|(1<<4)|(1<<8)|(1<<12);
	TIM1->BDTR |= (1 << 15);
	TIM1->CR1|=TIM_CR1_CEN;
}
void timer3_pwm_init(void)
{
	// TIMER 3 Channel 3 4  PB0,PB1
	RCC->AHB1ENR|=RCC_AHB1ENR_GPIOBEN;
	GPIOB->MODER|=(2<<0)|(2<<2);
	GPIOB->OSPEEDR|=(2<<0)|(2<<2);
	GPIOB->AFR[0]|=(2<<0)|(2<<4);
	RCC->APB1ENR|=RCC_APB1ENR_TIM3EN;
	TIM3->PSC=0;
	TIM3->ARR=640;	// 25kHz
	TIM3->CCR3 = 0;
	TIM3->CCR4 = 0;
	TIM3->CCMR2|=(6<<4)|(6<<12);
	TIM3->CCER|=(1<<8)|(1<<12);
	TIM3->BDTR |= (1 << 15);
	TIM3->CR1|=TIM_CR1_CEN;
}
void pwm_start(void)
{
	timer1_pwm_init();
	timer3_pwm_init();
}
void pwm_channel1_set(uint8_t duty1)
{
	TIM1->CCR1 =(int)(6.4*duty1);
}
void pwm_channel2_set(uint8_t duty2)
{
	TIM1->CCR2 = (int)(6.4*duty2);
}
void pwm_channel3_set(uint8_t duty3)
{
	TIM1->CCR3 = (int)(6.4*duty3);
}
void pwm_channel4_set(uint8_t duty4)
{
	TIM1->CCR4 = (int)(6.4*duty4);
}
void pwm_channel5_set(uint8_t duty5)
{
	TIM3->CCR3 = (int)(6.4*duty5);
}
void pwm_channel6_set(uint8_t duty6)
{
	TIM3->CCR4 = (int)(6.4*duty6);
}
void pwm_set_all(uint8_t duty[6])
{
	pwm_channel1_set(duty[0]);
	pwm_channel2_set(duty[1]);
	pwm_channel3_set(duty[2]);
	pwm_channel4_set(duty[3]);
	pwm_channel5_set(duty[4]);
	pwm_channel6_set(duty[5]);
}



