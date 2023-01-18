#include <stdio.h>
#include "stm32f1xx.h"
#include "bsp.h"

static void SystemClock_Config() ;

uint16_t flag ;
uint16_t compteur ;	


int main()
{
    SystemClock_Config() ;

    BSP_LED_Init() ;

	timer_init() ;
	flag = 0 ;

    BSP_LED_On() ;
    
	while(1)
	{
		if (( TIM2->SR & TIM_SR_UIF ) == TIM_SR_UIF )
		{
				flag ^= ( 0x01 << 10U ) ;
				compteur = TIM2->CNT ;

				// Reset UIF
				TIM2->SR &= ~TIM_SR_UIF ;

				BSP_LED_Toggle() ;
		}
        
	}
}

void SystemClock_Config(void)
{

    uint32_t	HSE_Status;
	uint32_t	PLL_Status;
	uint32_t	SW_Status;
	uint32_t	timeout = 0;

	timeout = 1000000;

	// Start HSE 
	RCC->CR &= ~RCC_CR_HSEBYP;
	RCC->CR |= RCC_CR_HSEON;

	// Wait until HSE is ready
	do
	{
		HSE_Status = RCC->CR & RCC_CR_HSERDY_Msk;
		timeout--;
	} while ((HSE_Status == 0) && (timeout > 0));

	// Select HSE as PLL input source
	RCC->CFGR &= ~RCC_CFGR_PLLSRC_Msk;
	RCC->CFGR |= (0x01<< RCC_CFGR_PLLSRC_Pos);


	// Set PLL MUL to x6
	RCC->CFGR &= ~RCC_CFGR_PLLMULL_Msk;
	RCC->CFGR |= RCC_CFGR_PLLMULL6_Msk;

	// Enable the main PLL
	RCC-> CR |= RCC_CR_PLLON;

	// Wait until PLL is ready
	do
	{
		PLL_Status = RCC->CR & RCC_CR_PLLRDY_Msk;
		timeout--;
	} while ((PLL_Status == 0) && (timeout > 0));

    // Set AHB prescaler to /1
	RCC->CFGR &= ~RCC_CFGR_HPRE_Msk;
	RCC->CFGR |= RCC_CFGR_HPRE_DIV1;

	// Set APB1 prescaler to /2
	RCC->CFGR &= ~RCC_CFGR_PPRE1_Msk;
	RCC->CFGR |= RCC_CFGR_PPRE1_DIV2;

	// Enable FLASH Prefetch Buffer and set Flash Latency
	FLASH->ACR = FLASH_ACR_PRFTBE | FLASH_ACR_LATENCY;

	// --- Until this point, MCU was still clocked by HSI at 8MHz ---
	// --- Switching to PLL at 48MHz Now!  Fasten your seat belt! ---

	// Select the main PLL as system clock source
	RCC->CFGR &= ~RCC_CFGR_SW;
	RCC->CFGR |= RCC_CFGR_SW_PLL;

	// Wait until PLL becomes main switch input
	do
	{
		SW_Status = (RCC->CFGR & RCC_CFGR_SWS_Msk);
		timeout--;
	} while ((SW_Status != RCC_CFGR_SWS_PLL) && (timeout > 0));


	//--- Use PA8 as MCO output 

	// Set MCO source as SYSCLK (48MHz)
	// RCC->CFGR &= ~RCC_CFGR_MCO_Msk;
	// RCC->CFGR |=  RCC_CFGR_MCOSEL_SYSCLK;


	// Enable GPIOA clock
	// RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;

	// Configure PA8 as high speed (50Mhz) 
	// GPIOA->CRH &= ~GPIO_CRH_MODE8_Msk;
	// GPIOA->CRH |=  GPIO_CRH_MODE8_1 | GPIO_CRH_MODE8_0;

    // Configure PA8 as alternate function push/pull
    // GPIOA->CRH &= ~GPIO_CRH_CNF8_Msk ;
    // GPIOA->CRH |= GPIO_CRH_CNF8_1 ;

	// Update SystemCoreClock global variable
	SystemCoreClockUpdate();

}
