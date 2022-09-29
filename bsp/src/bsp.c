#include <stdlib.h>
#include "bsp.h"
#include "stm32f1xx.h"

void BSP_LED_Init(){
    // Enable PortC clock
	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
	// Configure PC13 as output push/pull
    GPIOC->CRH |= GPIO_CRH_MODE13_Msk ;
    GPIOC->CRH &= ~GPIO_CRH_CNF13_Msk ;
}

void BSP_LED_On(){
    GPIOC->BSRR = GPIO_BSRR_BR13 ;
}

void BSP_LED_Off(){
    GPIOC->BSRR = GPIO_BSRR_BS13;
}

void BSP_LED_Toggle(){
    GPIOC->ODR ^= GPIO_ODR_ODR13;
}


unsigned char* memseb[50] ;

void *malloc ( size_t size )
{
	return memseb ;
}





int _write(int fd, char * ptr, int len)
{
	int i ;
	for (i=0; i<len; i++ ) {	
		while ((USART2->SR & USART_SR_TC) != USART_SR_TC);
		USART2->DR = ptr[i];
	}
    return len ;
}


void BSP_Console_Init() {

	// Enable GPIOA clock
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;

	// Configure PA2 and PA3 as Alternate function
	GPIOA->CRL &= ~GPIO_CRL_MODE3_Msk ;		// PA3 as Input
	GPIOA->CRL &= ~GPIO_CRL_MODE2_Msk ;
	GPIOA->CRL |= GPIO_CRL_MODE2_1 ;		// PA2 as Output ( 2Mhz )
    GPIOA->CRL &= ~GPIO_CRL_CNF2_Msk ;
    GPIOA->CRL |= GPIO_CRL_CNF2_1 ;			// PA2 AF push/pull
    GPIOA->CRL &= ~GPIO_CRL_CNF3_Msk ;
    GPIOA->CRL |= GPIO_CRL_CNF3_0 ;			// PA3 Floating input

	// Enable USART2 clock
	RCC -> APB1ENR |= RCC_APB1ENR_USART2EN;

	// Clear USART2 configuration (reset state)
	// 8-bit, 1 start, 1 stop, CTS/RTS disabled
	USART2->CR1 = 0x00000000;
	USART2->CR2 = 0x00000000;
	USART2->CR3 = 0x00000000;

	// Baud Rate = 9600 bauds
	// With Fck=24MHz, USARTDIV = 156.25
	// DIV_Fraction = 16*0.25 = 4
    // DIV_Mantissa = 156 = 0x9C
    // Hence USART_BRR = 0x9c4

	USART2->BRR = 0x9C4;

	// Enable both Transmitter and Receiver
	USART2->CR1 |= USART_CR1_TE | USART_CR1_RE;

	// Enable USART2
	USART2->CR1 |= USART_CR1_UE;
}
