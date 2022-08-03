/*
 * Archivo: ADC.h
 * Dispositivo: PIC16F887
 * Compilador:  XC8, MPLABX v5.40
 * Autor: Sergio Alejandro Boch
 * Programa: Librería de control del ADC
 * 
 * Creado: 20/07/22
 * Última modificación: 20/07/22
 */


// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef ADC
#define	ADC

#include <xc.h> // include processor files - each processor file is guarded.
#include <stdint.h>
#include "ADC.h"

// Prototipos de funciones 

void init_ADC(uint8_t adc_cs, uint8_t vref_plus, uint8_t vref_minus);   
void ADC_start(uint8_t channel);
uint16_t ADC_read(void);

#endif

