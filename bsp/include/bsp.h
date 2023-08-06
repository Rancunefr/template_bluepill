#ifndef BSP_H
#define BSP_H

#include <stdint.h>

void SystemClock_Config() ;

void BSP_LED_Init();
void BSP_LED_On();
void BSP_LED_Off();
void BSP_LED_Toggle();

void BSP_DELAY_TIMER_Init() ;
void BSP_DELAY_TIMER_ms( uint16_t ms ) ;

void BSP_PWM_TIMER_Init() ;

void ADC_Init(void) ;
uint16_t ADC_Read(void) ;

void BSP_Console_Init() ;

void BSP_I2c_Init() ;
void BSP_I2c_Start() ;
void BSP_I2c_Stop() ;
uint8_t BSP_I2c_Read() ;
void BSP_I2c_Write( uint8_t data ) ;
void BSP_I2c_Scan(uint8_t *addresses);


#endif
