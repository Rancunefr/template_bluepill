#include <stdlib.h>
#include "bsp.h"
#include "stm32f1xx.h"

void BSP_Console_Init() {   

	// USART2 sur PA2/PA3

	// Enable GPIOA clock
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	
	// Configure pins (AF)
	GPIOA->CRL &= ~GPIO_CRL_MODE3_Msk ;		// RAZ
	GPIOA->CRL &= ~GPIO_CRL_MODE2_Msk ;		// RAZ
	GPIOA->CRL |= GPIO_CRL_MODE2_1 ;		// reglage PA2 ( PA3 c'est zero )
	
	GPIOA->CRL &= ~GPIO_CRL_CNF3_Msk ;		// RAZ
	GPIOA->CRL &= ~GPIO_CRL_CNF2_Msk ;		// RAZ
	GPIOA->CRL |= GPIO_CRL_CNF2_1 ;		// Reglage PA2
	GPIOA->CRL |= GPIO_CRL_CNF3_0 ;		// Reglage PA3

	// Enable USART clock
	
	RCC->APB1ENR |= RCC_APB1ENR_USART2EN ;

	// Configure USART

	USART2->CR1 = 0x00000000 ;     // 8bits data 1 start 1 stop
	USART2->CR2 = 0x00000000 ;			// pas de CTS RTS
	USART2->CR3 = 0x00000000 ;

	// Fraction : 16*0.25 = 4 
	// Mantisse : 156
	
	USART2->BRR = 0x9C4 ;

	// Enable
	
	USART2->CR1 |= USART_CR1_TE | USART_CR1_RE ;
	USART2->CR1 |= USART_CR1_UE ;
}

int _write( int fd, char* ptr, int len ) {
	int i ;
	for (i=0; i<len; i++ ) {
		while ((USART2->SR & USART_SR_TC) != USART_SR_TC ) ;
		USART2->DR = ptr[i] ;
	}
	return len ;
}
