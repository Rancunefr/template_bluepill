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

void attente_ms( uint32_t delai ) ;		// Attente en ms
void timer_init() ;

#endif
