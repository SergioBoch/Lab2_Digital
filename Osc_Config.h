/*
 * Archivo: Osc_Config.h
 * Dispositivo: PIC16F887
 * Compilador:  XC8, MPLABX v5.40
 * Autor: Sergio Alejandro Boch Ixén
 * Programa: Librería de configuración del oscilador interno 
 * 
 * Creado: 20/07/22
 * Última modificación: 20/07/22
 */


// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef Osc_Config
#define	Osc_Config

#pragma config FOSC = INTRC_NOCLKOUT // Oscillator Selection bits

#include <xc.h> // include processor files - each processor file is guarded.
#include <stdint.h>
#include "Osc_Config.h"

void init_osc_MHz (uint8_t freq);  // Prototipos de funciones

#endif

