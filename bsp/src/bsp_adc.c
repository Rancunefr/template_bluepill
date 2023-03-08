#include <stdlib.h>
#include "bsp.h"
#include "stm32f1xx.h"

void ADC_Init(void) {
  // Enable GPIOA clock
  RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;

  // Configure the ADC pin as analog input
  GPIOA->CRL &= ~GPIO_CRL_CNF0;
  GPIOA->CRL &= ~GPIO_CRL_MODE0;

  // Enable ADC1 clock
  RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;

  // Configure ADC1
  ADC1->CR1 &= ~ADC_CR1_SCAN;
  ADC1->CR1 &= ~ADC_CR1_DUALMOD;
  ADC1->CR1 &= ~ADC_CR1_DUALMOD_0;
  ADC1->CR1 &= ~ADC_CR1_DUALMOD_1;
  ADC1->CR2 &= ~ADC_CR2_CONT;
  ADC1->CR2 &= ~ADC_CR2_ALIGN;
  ADC1->CR2 &= ~ADC_CR2_EXTSEL;
  ADC1->SMPR2 |= ADC_SMPR2_SMP0_1 | ADC_SMPR2_SMP0_0;

  // Enable ADC1 and wait for it to be ready
  ADC1->CR2 |= ADC_CR2_ADON;
  // while(!(ADC1->SR & ADC_SR_ADONS));   // FIXME ??

  // Calibrate ADC1 and wait for calibration to complete
  // ADC1->CR2 |= ADC_CR2_CAL;
  // while(ADC1->CR2 & ADC_CR2_CAL);
}

uint16_t ADC_Read(void) {
  uint16_t adc_value;

  // Start ADC conversion
  ADC1->CR2 |= ADC_CR2_ADON | ADC_CR2_SWSTART;

  // Wait for conversion to complete
  while(!(ADC1->SR & ADC_SR_EOC));

  // Read ADC value
  adc_value = ADC1->DR;

  return adc_value;
}
