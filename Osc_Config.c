/*
 * Archivo: Osc_Config.c
 * Dispositivo: PIC16F887
 * Compilador:  XC8, MPLABX v5.40
 * Autor: Sergio Alejandro Boch Ixén
 * Programa: Source file de configuración del oscilador
 * 
 * Hardware:  PIC16F887 con led
 * 
 * Creado: 20/07/22
 * Última modificación: 20/07/22
 */

#include <xc.h>
#include "Osc_Config.h"

/*------------------------------------------------------------------------------
 * Funciones
------------------------------------------------------------------------------*/

void init_osc_MHz (uint8_t freq){   
    OSCCONbits.SCS = 1;                  // Oscilador interno
    
    switch(freq){
        case 1:
            OSCCONbits.IRCF = 0b100;    // IRCF <2:0> 100 -> 1 MHz
            break;
        
        case 2:
            OSCCONbits.IRCF = 0b101;    // IRCF <2:0> 101 -> 2 MHz
            break;
        
        case 4:
            OSCCONbits.IRCF = 0b110;    // IRCF <2:0> 110 -> 4 MHz
            break;
            
        case 8:
            OSCCONbits.IRCF = 0b111;    // IRCF <2:0> 111 -> 8 MHz
            break;
            
        default:
            OSCCONbits.IRCF = 0b110;    // IRCF <2:0> 110 -> 4 MHz
            break;
    }
    
    return;
}

