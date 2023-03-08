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

void BSP_Console_Init() {   
#endif
