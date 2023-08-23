#include <stdio.h>
#include <math.h>
#include "stm32f1xx.h"
#include "bsp.h"


int main()
{
  uint8_t addresses[256] = {0};
  SystemClock_Config();
  BSP_Console_Init();

  BSP_I2c_Init();

  printf("--- Demarrage \r\n");

	  BSP_I2c_Scan(addresses);

	  for (uint8_t i = 0; i < 255; i++) {
		if (addresses[i] != 0) {
		  printf("Found I2C Slave on: %X\r\n", addresses[i]);
		  }
		}

  while (1) {

    // Do something with the ADC value
  }
}
