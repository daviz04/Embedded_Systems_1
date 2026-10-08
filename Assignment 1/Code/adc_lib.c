/*
 * adc_lib.c
 *
 *  Created on: 1 Oct 2026
 *      Author: DAVIDROBERTOTAPIACAI
 */
#include "adc_lib.h"
#include <msp430.h>

int conversion(int channel_selected)
{
    ADC10CTL0 &= 0xFFFD; // enc set to 0 to allow the 16 bit registers to be set

    ADC10AE0 = channel_selected << 1; // allow an analogue signal inputted on channel selected to be converted (move 1 to the left)
    ADC10CTL1 = (channel_selected << 12) | 0x0018; // Select Channel selected (INCHx), Clock Source as SMCLK (AC10SSELx), everything else is not important to us for now
    ADC10CTL0 = 0x0010; // (supply voltage as V+ref (SREFx), fastest sconversion rate (ADC10SHTx), fastest sampling rate (ADC10SR), and turn ADC10 on(ADC10ON)
    ADC10CTL0 |= 0x0002; //enc set to 1 to allow conversion
    int result;

    ADC10CTL0 = ADC10CTL0 | 0x0001; //START CONVERSION ON ADC10
    while ((ADC10CTL1 & 0x0001) == 1) // WAIT FOR CONVERSION TO COMPLETE
    {
    }
    result = ADC10MEM; // Get the result from the appropriate register

    return result;
}

void init_LCD()
{
    // Configure entire P2 as outputs
    P2DIR = 0xFF;

    P2SEL = 0x00; // no special functions for P2 port lines
    P2IE = 0x00; // no interrupts for P2 port lines

    //Initiate P2OUT to 0's
    P2OUT = 0x00;
}
// Función para imprimir una letra completa (8 bits)
void send_LCD_char(char letra){
    // 1. Aislar y enviar la primera mitad (High Nibble)
    // Desplazamos los 4 bits de la izquierda hacia la derecha para que la función los acepte
    send_LCD(letra >> 4);

    // 2. Aislar y enviar la segunda mitad (Low Nibble)
    // Usamos una máscara lógica para ignorar la parte alta y enviar solo los 4 bits de la derecha
    send_LCD(letra & 0x0F);
}

void send_LCD(int info){
    P2OUT |= 0x01; //Activate RS bit high
    P2OUT |= 0x02; //Activate EN bit with mask 0x02
    P2OUT &= 0x03; //Every bus is low and the first 2 bits remain their state
    P2OUT |= (info << 2);
    __delay_cycles(100); //1 ms

    P2OUT &= 0xFD; //Desactivate EN bit with mask 0xFD
    __delay_cycles(200); //2 ms
}
