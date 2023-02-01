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

void BSP_DELAY_TIMER_Init() {
	
	// Enable clock
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN ;

	// Reset TIM2 config
	TIM2->CR1 = 0x0000 ;		// CR = Control Register
	TIM2->CR2 = 0x0000 ;

	// Prescaler
	
	// Frequence d'horloge d'entree de 48 Mhz
	TIM2->PSC = (uint16_t) 48000 - 1 ;		// PSC = Prescaler register (16 bits)
											// Comptage 1ms

	// Auto-reload
	
	TIM2->ARR = (uint16_t) 0xFFFF;   		// ARR = Auto Reload Register
}

void BSP_DELAY_TIMER_ms( uint16_t ms ) {
	
	// Reset le timer

	TIM2->EGR |= TIM_EGR_UG ;

	// Demarre le timer

	TIM2->CR1 |= TIM_CR1_CEN ;

	// Attendre

	while( TIM2->CNT < ms ) ;

	// Arreter le timer
	
	TIM2->CR1 &= ~TIM_CR1_CEN ;
}

