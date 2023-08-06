#include <stdio.h>
#include <math.h>
#include "stm32f1xx.h"
#include "bsp.h"

uint16_t adc_value ;
int volts ;

int main()
{
  uint8_t addresses[128] = {0};
  adc_value = 0;
  uint8_t found_accel_MMA8452 = 0;

  SystemClock_Config();
  BSP_Console_Init();

  BSP_I2c_Init();

  printf("coucou \r\n");

  BSP_I2c_Scan(addresses);
  for (uint8_t i = 0; i < 128; i++) {
    if (addresses[i] != 0) {
      printf("Found I2C Slave on: %X\r\n", addresses[i]);
      if (addresses[i] == 0x1E) {
	found_accel_MMA8452 = 1;
      }
    }
  }


  while (1) {

    // Do something with the ADC value
  }
}
