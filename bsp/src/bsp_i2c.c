#include <stdlib.h>
#include "bsp.h"
#include "stm32f1xx.h"

int BSP_I2c_write_adress( uint8_t data ) ;

void BSP_I2c_Scan(uint8_t *addresses) { // Adresse écrite sur 7 bits (sans le R/W)
  uint8_t addr = 1;
  for( addr = 2; (addr<255)&&(addr>1) ; addr+=2) {    // FIXME
	BSP_I2c_Start() ;
	if ( BSP_I2c_write_adress( addr ) ) {
      addresses[addr] = addr;
	} 
	BSP_I2c_Stop(); 
  }
}

void BSP_I2c_Init() {
	// PB6 -> i2c1 / scl
	// PB7 -> i2c1 / sda

	// Activer la clock 
	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN ;
	RCC->APB1ENR |= RCC_APB1ENR_I2C1EN ;
	
	// Configurer les pins ( Alternate Function )
	
	GPIOB->CRL &= ~GPIO_CRL_MODE6_Msk ;		// RAZ
	GPIOB->CRL &= ~GPIO_CRL_MODE7_Msk ;		// RAZ
	GPIOB->CRL &= ~GPIO_CRL_CNF6_Msk ;		// RAZ
	GPIOB->CRL &= ~GPIO_CRL_CNF7_Msk ;		// RAZ

	GPIOB->CRL |= GPIO_CRL_MODE6_Msk ;		// reglage Pb6  ( Output mode 50 MHz )
	GPIOB->CRL |= GPIO_CRL_MODE7_Msk ;		// reglage Pb7  ( Output mode 50 Mhz ) 
	
	GPIOB->CRL |= GPIO_CRL_CNF6_Msk ;		// Pb6 Alternate Function Open Drain
	GPIOB->CRL |= GPIO_CRL_CNF7_Msk ;		// Pb7 Alternate Function Open Drain
	
	// Registres de config
	
	I2C1->CR1 = 0 ;
	// Program the peripheral input clock in I2C_CR2 register in order to generate correct timings
	I2C1->CR2 = 0 ;
	I2C1->CCR = 0 ;

		// Program the peripheral input clock 
		// in I2C_CR2 register in order to 
		// generate correct timings

		// APB Clock Freq Value

		I2C1->CR2 |= 24 ; 

		// Configure the clock control registers

		I2C1->CCR |= 0x78 ;

		// Configure the rise time register

		I2C1->TRISE = 25 ;

		// Program the I2C_CR1 register to enable 
		// the peripheral
		
		I2C1->CR1 |= I2C_CR1_PE ;

}

void BSP_I2c_Start() {
    // reset SR1 and SR2
    I2C1->SR1 = 0;
    I2C1->SR2 = 0;
    I2C1->CR1 |= I2C_CR1_START;
    // wait for Start bit
    while ((I2C1->SR1 & I2C_SR1_SB) != I2C_SR1_SB)
      ;
}

void BSP_I2c_Stop() {
    I2C1->CR1 |= I2C_CR1_STOP;
    // wait for Start bit off
    while ((I2C1->SR1 & I2C_SR1_SB) != 0x00)
      ;
}

int BSP_I2c_write_adress( uint8_t data ) {
    volatile uint16_t SR1 = 0;
    volatile uint16_t SR2 = 0;
	uint16_t result ;
    // write data
    I2C1->DR = data ;
    // read SR1
    SR1 = I2C1->SR1;
    // read SR2
    SR2 = I2C1->SR2;
    //check if ACK/NACK
    return (SR1 & I2C_SR1_ADDR)  ; 
}
