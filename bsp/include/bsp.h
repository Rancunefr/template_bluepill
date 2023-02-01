#ifndef BSP_H
#define BSP_H

#include <stdint.h>

/*
 * LED driver functions
 */

void BSP_LED_Init();
void BSP_LED_On();
void BSP_LED_Off();
void BSP_LED_Toggle();

void BSP_DELAY_TIMER_Init() ;
void BSP_DELAY_TIMER_ms( uint16_t ms ) ;

#endif
