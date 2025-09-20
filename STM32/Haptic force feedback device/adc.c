#include "stm32f4xx.h"               
#include "adc.h"

void adc_init(void)
{
	RCC->AHB1ENR|= RCC_AHB1ENR_GPIOAEN; 
	RCC->APB2ENR|= RCC_APB2ENR_ADC1EN; 
	GPIOA->MODER|=(3<<8)|(3<<10)|(3<<12);
	ADC1->CR1 = 0;
	ADC1->CR1 |= (1 << 8); // Scan mode
	ADC1->CR2 = 0;
	ADC1->CR2 |= (1 << 1); // Continuous mode
	ADC1->CR2 |= (1 << 8); // DMA enable
	ADC1->CR2 |= (1 << 9); // DDS (DMA requests liên t?c)
	ADC1->SMPR2 &=~ (1 << 9);  // Channel 3: 56 chu k?
	ADC1->SMPR2 &=~ (1 << 12); // Channel 4: 56 chu k?
	ADC1->SMPR2 &=~ (1 << 15); // Channel 5: 56 chu k?
	ADC1->SQR1|=(2<<20);  // L=3
	ADC1->SQR3|=(4<<0)|(5<<5)|(6<<10); // Channel 456
	ADC1->CR2 |= (1 << 0); // ADON
	for (volatile int i = 0; i < 1000; i++); // Ch? ADC ?n d?nh
}
void adc_enabled(void)
{
	ADC1->CR2 |= (1 << 30); // SWSTART
}
void adc_dma_init(uint16_t* analog)
{
	RCC->AHB1ENR|= RCC_AHB1ENR_DMA2EN;  
	DMA2_Stream0->CR = 0; // Xóa c?u hình
	while (DMA2_Stream0->CR & DMA_SxCR_EN); // Ð?i DMA t?t
	DMA2_Stream0->PAR =(uint32_t)&ADC1->DR; // Ð?a ch? ngu?n (ADC1->DR)
	DMA2_Stream0->M0AR =(uint32_t)analog; // Ð?a ch? dích (analog_rx)
	DMA2_Stream0->NDTR = 3; // S? lu?ng d? li?u: 3 (cho 3 kênh)
	DMA2_Stream0->CR|=(0<<25); // Channel 0 (ADC1)
	DMA2_Stream0->CR|=(1<<10); // Memory increment mode (MINC)
	DMA2_Stream0->CR|=(1<<8);  // Circular mode (CIRC)
	DMA2_Stream0->CR|=(1<<11)|(1<<13); // Kích thu?c d? li?u: 16-bit (MSIZE, PSIZE)
	DMA2_Stream0->CR&=~(1<<6); // Peripheral to Memory
}
void adc_dma_enabled(void)
{
	DMA2_Stream0->CR|=(1<<0); 
}
void adc_start(uint16_t *analog)
{
	adc_init();
	adc_enabled();
	adc_dma_init(analog);
	adc_dma_enabled();
}
