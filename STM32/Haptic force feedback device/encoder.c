#include "stm32f4xx.h"
#include "encoder.h"

void timer5_encoder_init(void)
{
	// TIMER 5 CHANNEL 1 2:  PA0 PA1
	RCC->AHB1ENR|=RCC_AHB1ENR_GPIOAEN;
	GPIOA->MODER|=(2<<0)|(2<<2);
	GPIOA->AFR[0]|=(2<<0)|(2<<4);// AF2: TIM3_CH1, TIM3_CH2
	GPIOA->PUPDR|=(1<<0)|(1<<2);
	
	RCC->APB1ENR|=(1<<3);
	TIM5->PSC=0;
	TIM5->ARR = 0xFFFE;
	TIM5->SMCR|=(3<<0); // Encoder mode 3
	TIM5->CCMR1|=(1<<0)|(1<<8);
	TIM5->CCMR1&=~(1<<2)&~(1<<10);		// No prescale
	TIM5->CCMR1&=~(1<<4)&~(1<<12);		// No filter
	TIM5->CCER|=(1<<0)|(1<<4);				// Capture enabled
	TIM5->CCER|=(1<<1)|(1<<5);				// Falling edge
	TIM5->DIER|=(1<<9)|(1<<10);  // DMA
	TIM5->CR1|=(1<<0);
}
void timer5_encoder_dma_init(int16_t* counter1)
{
	RCC->AHB1ENR|=RCC_AHB1ENR_DMA1EN;
	DMA1_Stream4->CR = 0;
  while (DMA1_Stream4->CR & DMA_SxCR_EN);
	DMA1_Stream4->PAR = (uint32_t)&TIM5->CNT;
	DMA1_Stream4->M0AR = (uint32_t)counter1;
	DMA1_Stream4->NDTR = 2; // 2 byte
	DMA1_Stream4->CR|=(6<<25);		// CHannel 2
	DMA1_Stream4->CR|=(1<<11)|(1<<13);		// 3 bit
	DMA1_Stream4->CR|=(1<<8);		// CIcurlar mode
	DMA1_Stream4->CR&=~(1<<6);		// Peripheral to memory
	DMA1_Stream4->CR|=(1<<0);	// Enable
	DMA1_Stream2->CR|=(1<<0);	// Enable
}
void timer2_encoder_init(void)
{
	// TIMER 2 CHANNEL 1 2:  PA15 PB3
	RCC->AHB1ENR|=RCC_AHB1ENR_GPIOAEN|RCC_AHB1ENR_GPIOBEN;
	GPIOA->MODER&=~(3<<30);
	GPIOA->MODER|=(2<<30);
	GPIOA->AFR[1]|=(1<<28);
	GPIOA->PUPDR|=(1<<30);
	GPIOB->MODER&=~(3<<6);
	GPIOB->MODER|=(2<<6);
	GPIOB->AFR[0]|=(1<<12);
	GPIOB->PUPDR|=(1<<6);
	RCC->APB1ENR|=(1<<0);
	TIM2->PSC=0;
	TIM2->ARR = 0xFFFE;
	TIM2->SMCR|=(3<<0); // Encoder mode 3
	TIM2->CCMR1|=(1<<0)|(1<<8);
	TIM2->CCMR1&=~(1<<2)&~(1<<10);		// No prescale
	TIM2->CCMR1&=~(1<<4)&~(1<<12);		// No filter
	TIM2->CCER|=(1<<0)|(1<<4);				// Capture enabled
	TIM2->CCER|=(1<<1)|(1<<5);				// Falling edge
	TIM2->DIER|=(1<<9)|(1<<10);  // DMA	
	TIM2->CR1|=(1<<0);
}
void timer2_encoder_dma_init(int16_t* counter2)
{
	RCC->AHB1ENR|=RCC_AHB1ENR_DMA1EN;
	DMA1_Stream6->CR = 0;
  while (DMA1_Stream6->CR & DMA_SxCR_EN);
	DMA1_Stream6->PAR = (uint32_t)&TIM2->CNT;
	DMA1_Stream6->M0AR = (uint32_t)counter2;
	DMA1_Stream6->NDTR = 2; // 2 byte
	DMA1_Stream6->CR|=(3<<25);		// CHannel 2
	DMA1_Stream6->CR|=(1<<11)|(1<<13);		// 3 bit
	DMA1_Stream6->CR|=(1<<8);		// CIcurlar mode
	DMA1_Stream6->CR&=~(1<<6);		// Peripheral to memory
	DMA1_Stream6->CR|=(1<<0);	// Enable
	DMA1_Stream5->CR|=(1<<0);	// Enable
}
void timer4_encoder_init(void)
{
	// TIMER 4 CHANNEL 1 2:  PB6 PB7
	RCC->AHB1ENR|=RCC_AHB1ENR_GPIOBEN;
	GPIOB->MODER|=(2<<12)|(2<<14);
	GPIOB->AFR[0]|=(2<<24)|(2<<28);// AF2: TIM4_CH1, TIM4_CH2
	GPIOB->PUPDR|=(1<<12)|(1<<14);
	
	RCC->APB1ENR|=(1<<2);
	TIM4->PSC=0;
	TIM4->ARR = 0xFFFE;
	TIM4->SMCR|=(3<<0); // Encoder mode 3
	TIM4->CCMR1|=(1<<0)|(1<<8);
	TIM4->CCMR1&=~(1<<2)&~(1<<10);		// No prescale
	TIM4->CCMR1&=~(1<<4)&~(1<<12);		// No filter
	TIM4->CCER|=(1<<0)|(1<<4);				// Capture enabled
	TIM4->CCER|=(1<<1)|(1<<5);				// Falling edge
	TIM4->DIER|=(1<<9)|(1<<10);  // DMA	
	TIM4->CR1|=(1<<0);
}
void timer4_encoder_dma_init(int16_t* counter3)
{
	RCC->AHB1ENR|=RCC_AHB1ENR_DMA1EN;
	DMA1_Stream3->CR = 0;
  while (DMA1_Stream3->CR & DMA_SxCR_EN);
	DMA1_Stream3->PAR = (uint32_t)&TIM4->CNT;
	DMA1_Stream3->M0AR = (uint32_t)counter3;
	DMA1_Stream3->NDTR = 2; // 2 byte
	DMA1_Stream3->CR|=(2<<25);		// CHannel 2
	DMA1_Stream3->CR|=(1<<11)|(1<<13);		// 3 bit
	DMA1_Stream3->CR|=(1<<8);		// CIcurlar mode
	DMA1_Stream3->CR&=~(1<<6);		// Peripheral to memory
	DMA1_Stream3->CR|=(1<<0);	// Enable
	DMA1_Stream0->CR|=(1<<0);	// Enable
}
void timer_encoder_start(int16_t counter[3])
{
	timer2_encoder_init();
	timer2_encoder_dma_init(counter);
	
	timer5_encoder_init();
	timer5_encoder_dma_init(counter+1);
	
	timer4_encoder_init();
	timer4_encoder_dma_init(counter+2);
}
