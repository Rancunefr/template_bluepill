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

void attente_ms( uint32_t delai ) {
	uint32_t i ;
	for (i=0; i<(delai*2500); i++) ;   // 2500 tours pour une 1ms @ 48MHz
}

void timer_init() {
	// Enable clock
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN ;

	// Reset TIM5 config
	TIM2->CR1 = 0x0000 ;
	TIM2->CR2 = 0x0000 ;

	// Prescaler
	
	TIM2->PSC = (uint16_t) 48000 - 1 ;

	// Auto-reload
	
	TIM2->ARR = (uint16_t) 1000 - 1 ;
	TIM2->CR1  |= TIM_CR1_ARPE ;

	// Start the timer
	
	TIM2->CR1 |= TIM_CR1_CEN ;

}
