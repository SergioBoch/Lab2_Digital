/*
 * Archivo: main02.c
 * Dispositivo: PIC16F887
 * Compilador:  XC8, MPLABX v5.40
 * Autor: Sergio Alejandro Boch Ixén
 * Programa: Control de pantalla LCD utilizando librerías
 * 
 * Hardware:  PIC16F887 con LCD display
 * 
 * Creado: 27/07/22
 * Última modificación: 2/08/22
 */

#pragma config FOSC = INTRC_NOCLKOUT // Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

#include <xc.h>
#include <stdint.h>

#include "Osc_Config.h"
#include "ADC.h"
#include "LCD.h"

#define _XTAL_FREQ 8000000  //Oscilador de 8 MHz

uint16_t ADC_lecture_val = 0;       // Variable para almacenar la conversión del ADC
uint8_t ADC_channel_flag = 0;       // Variable para intercambiar el canal de la conversión

uint16_t ADC_channel_00 = 0;         // Variable para almacenar el valor del canal 0
uint16_t ADC_channel_01 = 0;         // Variable para almacenar el valor del canal 1

uint8_t Digits_Voltage1 [4] = {0,0,0,0};    // Variables para almacenar los dígitos de los valores de voltaje - centenas, decenas, unidades, residuo
uint8_t Digits_Voltage2 [4] = {0,0,0,0};

void setup (void);                  // Prototipo de función SETUP
void Voltage_val(int ADC_val, int channel);          // Prototipo de función de conversión a voltaje

void __interrupt() isr (void)
{
    if (PIR1bits.ADIF)  // Interrupción del ADC
    {
        if (ADCON0bits.CHS == 0b0000)       //Si fue conversión del canal 0
        {    
            ADC_channel_00 = ADC_read();   // Almacenar lectura del ADC
            ADC_channel_00 =  (int) (ADC_channel_00*((float )5/1023)*(100));
        }
        else
        {   
            ADC_channel_01 = ADC_read();
            ADC_channel_01 =  (int) (ADC_channel_01*((float )5/1023)*(100));
        }
    PIR1bits.ADIF = 0;                      //Reiniciar ADC
    }
}
void main(void)
{
    setup();                              // Configuraciones de los módulos
    Lcd_Set_Cursor(1,1);                  // Iniciamos la escritura en la primera posición
    Lcd_Write_String("  S1        S2");   // Escribimos los datos deseados en el display
    
    while(1)            // Ciclo LOOP
    {

        ADC_start(0);                           // Realizar conversión ADC en cada ciclo
        __delay_ms(20);
        ADC_start(1);
        
        __delay_ms(20);
        
        Voltage_val (ADC_channel_00, 1);
        Voltage_val (ADC_channel_01, 2);
        
        Lcd_Set_Cursor(2,1);
        
        Lcd_Write_String(" ");
        Lcd_Write_Char(Digits_Voltage1 [0] + 48);
        Lcd_Write_Char(46);
        Lcd_Write_Char(Digits_Voltage1 [1] + 48);
        Lcd_Write_Char(Digits_Voltage1 [2] + 48);
        Lcd_Write_Char(86);
        Lcd_Write_String(" ");
        Lcd_Write_String(" ");
        Lcd_Write_String(" ");
        Lcd_Write_String(" ");       
        
        Lcd_Write_Char(Digits_Voltage2 [0] + 48);
        Lcd_Write_Char(46);
        Lcd_Write_Char(Digits_Voltage2 [1] + 48);
        Lcd_Write_Char(Digits_Voltage2 [2] + 48);
        Lcd_Write_Char(86);
        Lcd_Write_String(" ");
    }    
    return;
}

void setup(void){
 
    TRISA = 0b00000011;         // PORTA como salida, RA0 & RA1 como entradas
    PORTA = 0;                  // Limpiamos PORTA 
    
    ANSEL = 0b00000011;          //AN0 & AN1 como entradas analógicas
    ANSELH = 0;                
    
    TRISD = 0;          //PORTD & PORTC como salidas
    PORTD = 0;
    
    TRISC = 0;
    PORTC = 0;
  
    init_osc_MHz (8);
    init_ADC (8,0,0);
    Lcd_Init();
  
    INTCONbits.PEIE = 1;    // Habilitamos int. de perifericos
    INTCONbits.GIE = 1;     // Habilitamos int. globales
    return;
}
void Voltage_val (int ADC_val, int channel)
{
    if (channel == 1)
    {    
        Digits_Voltage1 [0] =  (uint8_t)(ADC_val/100);
        Digits_Voltage1 [3] =   ADC_val%100;

        Digits_Voltage1 [1] =   Digits_Voltage1 [3]/10;
        Digits_Voltage1 [3] =   Digits_Voltage1 [3]%10;

        Digits_Voltage1 [2] =  Digits_Voltage1 [3];
    }
    else if (channel == 2)
    {
        Digits_Voltage2 [0] =  (uint8_t)(ADC_val/100);
        Digits_Voltage2 [3] =   ADC_val%100;

        Digits_Voltage2 [1] =   Digits_Voltage2 [3]/10;
        Digits_Voltage2 [3] =   Digits_Voltage2 [3]%10;
        Digits_Voltage2 [2] =  Digits_Voltage2 [3];
    }    
    return;
}