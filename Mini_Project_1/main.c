//********************************************************************
// Student Name:David Tapia Caicedo
// Student No:L00213709
// Mini Project 1 Part A Question Number: 1
//********************************************************************
#include "msp430G2553.h"
void main(void)
{
    WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer
    P1DIR = 0xFE; //Configure P1.0 as an input (rest of P1 is an output)
    P1SEL=0x00;// no special functions for P1 port lines
    P1IE=0x00;// no interrupts for P1 port lines
// Port 2 is unused - we'll configure it as an output and put zeros on the lines
    P2DIR = 0xff; //Configure P2 as output lines
    P2SEL = 0x00; // no special functions for P2 port lines
    P2IE = 0x00; // no interrupts for P2 port lines
    P2OUT = 0x00; // 0 on un-used lines
    ADC10AE0 = 0x01; // allow an analogue signal inputted on P1.0 to be converted
    ADC10CTL0= ADC10CTL0 & 0xFFFD;// enc set to 0 to allow the 16 bit registers to be set
    ADC10CTL1 = 0x0018;// Select Channel A0 (INCHx), Clock Source as SMCLK (AC10SSELx), everything else is not important to us for now
    ADC10CTL0 = 0x0010;// (supply voltage as V+ref (SREFx), fastest sconversion rate (ADC10SHTx), fastest sampling rate (ADC10SR), and turn ADC10 on(ADC10ON)
    ADC10CTL0= ADC10CTL0 | 0x0002; //enc set to 1 to allow conversion
    int result;
    while (1)
    {
    ADC10CTL0 = ADC10CTL0 | 0x0001; //START CONVERSION ON ADC10
    while((ADC10CTL1 & 0x0001) == 1)// WAIT FOR CONVERSION TO COMPLETE
    {
    }
    result = ADC10MEM; // Get the result from the appropriate register
//PROCESS THE RESULT
    if(result>???)// if the input voltage exceeds 1.65V ,(Floor of ((1.65*1024)/3.3)+0.5 = 310)
    {
        P1OUT= P1OUT | 0x??; // Make P1.6 go HIGH - LED will go ON
    }
    else
    {
        P1OUT= P1OUT & 0x??; // Make P1.6 go LOW - LED will go OFF
    }
//Wait 1 second
    __delay_cycles(1000000);
}
}
