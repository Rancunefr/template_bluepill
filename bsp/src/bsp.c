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


