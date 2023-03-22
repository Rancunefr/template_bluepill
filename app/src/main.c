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
	ADC_Init();

	while(1)
	{
		adc_value = ADC_Read();
		volts = adc_value * 315 / 4095 ;
		printf("ADC: %d (%d) \n", adc_value, volts );

    	// Do something with the ADC value		
	}
}
