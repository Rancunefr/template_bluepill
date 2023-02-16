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

void BSP_PWM_TIMER_Init() {

	// Enable clock

	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN ;
	RCC->APB2ENR |= RCC_APB2ENR_TIM1EN ;

	// PA8 - Output / Push-Pull

	GPIOA->CRH |= GPIO_CRH_MODE8_Msk ;  // MODE : 11 (50 MMHz)
	GPIOA->CRH |= GPIO_CRH_CNF8_1 ;		// CNF : 10  (Alernate PushPull)
	GPIOA->CRH &= ~GPIO_CRH_CNF8_0 ;

	GPIOA->CRH |= GPIO_CRH_MODE9_Msk ;  // MODE : 11 (50 MMHz)
	GPIOA->CRH |= GPIO_CRH_CNF9_1 ;		// CNF : 10  (Alernate PushPull)
	GPIOA->CRH &= ~GPIO_CRH_CNF9_0 ;

	GPIOA->CRH |= GPIO_CRH_MODE10_Msk ;  // MODE : 11 (50 MMHz)
	GPIOA->CRH |= GPIO_CRH_CNF10_1 ;		// CNF : 10  (Alernate PushPull)
	GPIOA->CRH &= ~GPIO_CRH_CNF10_0 ;

	// Reset Config
	
	TIM1->CR1 = 0x0000 ;
	TIM1->CR2 = 0x0000 ;
	TIM1->CCER = 0x0000 ;

	// Frequence d'horloge d'entree de 48 Mhz
	TIM1->PSC = (uint16_t) 48 - 1 ;		// PSC = Prescaler register (16 bits)
										// Frequence 1 Mhz
	
	// Auto reload register

	TIM1->ARR = (uint16_t) 20000 ;		// Periode de 20 ms
	TIM1->CR1 |= TIM_CR1_ARPE ;

	TIM1->CCMR1 = 0x0000 ;

	// Setup PWM Mode 1
	
	TIM1->CCMR1 |= ( 0x06 << TIM_CCMR1_OC1M_Pos ) | TIM_CCMR1_OC1PE ;
	TIM1->CCMR1 |= ( 0x06 << TIM_CCMR1_OC2M_Pos ) | TIM_CCMR1_OC2PE ;
	TIM1->CCMR2 |= ( 0x06 << TIM_CCMR2_OC3M_Pos ) | TIM_CCMR2_OC3PE ;

	// Set PWM value
	
	TIM1->CCR1 = (uint16_t) 0 ;		// Red
	TIM1->CCR2 = (uint16_t) 0 ;		// Green
	TIM1->CCR3 = (uint16_t) 0 ;		// Blue

	// Enable outputs
	
	TIM1->CCER |= TIM_CCER_CC1E ;
	TIM1->CCER |= TIM_CCER_CC2E ;
	TIM1->CCER |= TIM_CCER_CC3E ;

	// Enable main output
	
	TIM1->BDTR |= TIM_BDTR_MOE ;

	// Enable Timer
	
	TIM1->CR1 |= TIM_CR1_CEN ;

}
