#include <stdio.h>
#include <math.h>
#include "stm32f1xx.h"
#include "bsp.h"

uint16_t adc_value ;

int main()
{
	adc_value = 0 ;

    SystemClock_Config() ;
	ADC_Init();

	while(1)
	{
		adc_value = ADC_Read();
    	// Do something with the ADC value		
	}
}
