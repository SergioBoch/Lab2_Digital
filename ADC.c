/*
 * Archivo: ADC.c
 * Dispositivo: PIC16F887 
 * Compilador:  XC8, MPLABX v5.40
 * Autor: Sergio Alejandro Boch Ixén
 * Programa: Source file de configuración y control del ADC
 * 
 * Hardware:  PIC16F887 con led
 * 
 * Creado: 20/07/22
 * Última modificación: 20/07/22
 */

#include <xc.h>
#include "ADC.h"

/*------------------------------------------------------------------------------
 * Funciones
------------------------------------------------------------------------------*/

void init_ADC(uint8_t adc_cs, uint8_t vref_plus, uint8_t vref_minus){
 
    switch(adc_cs){
        case 1:
            ADCON0bits.ADCS = 0b11;     // FRC
            break;
        
        case 2:
            ADCON0bits.ADCS = 0b00;     // Fosc/2
            break;
        
        case 8:
            ADCON0bits.ADCS = 0b01;     // Fosc/8
            break;
        
        case 32:
            ADCON0bits.ADCS = 0b10;     // Fosc/32
            break;
  
        default:
            ADCON0bits.ADCS = 0b01;     // Fosc/8
            break;
    }
    
    switch(vref_plus){
        case 0:
            ADCON1bits.VCFG0 = 0;       // VDD
            break;
        
        case 1:
            ADCON1bits.VCFG0 = 1;       // VREF+ pin
            break;
            
        default:
            ADCON1bits.VCFG0 = 0;       // VDD
            break;
    }
    
    switch(vref_minus){
        case 0:
            ADCON1bits.VCFG1 = 0;       // VSS
            break;
        
        case 1:
            ADCON1bits.VCFG1 = 1;       // VREF- pin
            break;
            
        default:
            ADCON1bits.VCFG1 = 0;       // VSS
            break;
    }
    
    ADCON1bits.ADFM = 1;        // Justificado a la derecha
    ADCON0bits.ADON = 1;        // Habilitamos modulo ADC
    
    PIR1bits.ADIF = 0;          // Limpiamos bandera de ADC
    PIE1bits.ADIE = 1;          // Habilitamos interrupcion de ADC
    return;
}

void ADC_start(uint8_t channel){
    if (ADCON0bits.GO == 0) {          // Verificar si se debe hacer una conversión
        switch (channel){              // Realizar conversión en el canal seleccionado
            case 0:
                 ADCON0bits.CHS = 0b0000;
                 break;
                 
            case 1:
                 ADCON0bits.CHS = 0b0001;
                 break;
                 
            case 2:
                 ADCON0bits.CHS = 0b0010;
                 break;     
                 
            case 3:
                 ADCON0bits.CHS = 0b0011;
                 break;
                 
            case 4:
                 ADCON0bits.CHS = 0b0100;
                 break;    
                 
            case 5:
                 ADCON0bits.CHS = 0b0101;
                 break;     
                 
            case 6:
                 ADCON0bits.CHS = 0b0110;
                 break;     
                 
            case 7:
                 ADCON0bits.CHS = 0b0111;
                 break;     
                 
            case 8:
                 ADCON0bits.CHS = 0b1000;
                 break;     
                 
            case 9:
                 ADCON0bits.CHS = 0b1001;
                 break;  
                 
            case 10:
                 ADCON0bits.CHS = 0b1010;
                 break;     
                 
            case 11:
                 ADCON0bits.CHS = 0b1011;
                 break;     
                 
            case 12:
                 ADCON0bits.CHS = 0b1100;
                 break;
                 
            case 13:
                 ADCON0bits.CHS = 0b1101;
                 break;     
                 
            default:
                 ADCON0bits.CHS = 0b0000;
                 break;
        }
        ADCON0bits.GO = 1;
    }
    return;
}

uint16_t ADC_read(void){        // Devolver el valor de la conversión en una variable "read" de 10 bits
    uint16_t read = 0;
    read = ADRESH;
    read = read << 8;
    read |= ADRESL;
    
    return read;
}

