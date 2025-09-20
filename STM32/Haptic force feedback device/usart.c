#include "stm32f4xx.h"                  
#include "usart.h"

void usart_init(void)
{
	// USART2 TX:PA2 RX:PA3
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	GPIOA->MODER|=(2<<4)|(2<<6);
	GPIOA->OSPEEDR|=(2<<4)|(2<<6);
	GPIOA->AFR[0]|=(7<<8)|(7<<12);
	RCC->APB1ENR|= RCC_APB1ENR_USART2EN;
	USART2->BRR =(8<<4)|11;
	USART2->CR1|=(1<<5);
	NVIC_SetPriority(USART2_IRQn, 0);    
	NVIC_EnableIRQ(USART2_IRQn); // Cho phép ng?t USART2  
	//NVIC->ISER[1]|=(1<<6);	
}
void usart_enabled(void)
{
	USART2->CR1|=(1<<2)|(1<<3)|(1<<13);
}
void usart_start()
{
	usart_init();
	usart_enabled();
}




