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
