#include <stdio.h>
#include <math.h>
#include "stm32f1xx.h"
#include "bsp.h"

uint16_t adc_value ;
int volts ;

int main()
{
	adc_value = 0 ;

    SystemClock_Config() ;
	BSP_Console_Init() ;

	BSP_I2c_Init() ;

	printf("coucou \n" );

	// Generate Start Condition
	
	I2C1->CR1 |= I2C_CR1_START ;


	while(1)
	{

    	// Do something with the ADC value		
	}
}
