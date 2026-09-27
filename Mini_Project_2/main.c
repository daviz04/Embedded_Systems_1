#include <msp430.h> 

/**
 * main.c
 */
int main(void)
{
    WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer

    P1DIR = 0xFD; //Configure P1.1 as an input (Only needed P1.0 and P1.6 as outputs, but configured all unused pins as outputs)
    P1SEL = 0x00; // no special functions for P1 port lines
    P1IE = 0x00; // no interrupts for P1 port lines
    // Port 2 is unused - we'll configure it as an output and put zeros on the lines
    P2DIR = 0xff; //Configure P2 as output lines
    P2SEL = 0x00; // no special functions for P2 port lines
    P2IE = 0x00; // no interrupts for P2 port lines
    P2OUT = 0x00; // 0 on un-used lines

    ADC10AE0 = 0x02; // allow an analogue signal inputted on P1.1 to be converted
    ADC10CTL0 = ADC10CTL0 & 0xFFFD; // enc set to 0 to allow the 16 bit registers to be set
    ADC10CTL1 = 0x1018; // Select Channel A1 (INCHx), Clock Source as SMCLK (AC10SSELx), everything else is not important to us for now
    ADC10CTL0 = 0x0010; // (supply voltage as V+ref (SREFx), fastest sconversion rate (ADC10SHTx), fastest sampling rate (ADC10SR), and turn ADC10 on(ADC10ON)
    ADC10CTL0 = ADC10CTL0 | 0x0002; //enc set to 1 to allow conversion
    int result;

    while (1)
    {
        ADC10CTL0 = ADC10CTL0 | 0x0001; //START CONVERSION ON ADC10
        while ((ADC10CTL1 & 0x0001) == 1) // WAIT FOR CONVERSION TO COMPLETE
        {
        }
        result = ADC10MEM; // Get the result from the appropriate register
        //PROCESS THE RESULT
        if (result > 512) // if the input voltage exceeds 1.65V ,(Floor of ((1.65*1024)/3.3)+0.5 = 512)
        {
            P1OUT = P1OUT | 0x40; // Make P1.6 go HIGH - LED will go ON
        }
        else
        {
            P1OUT = P1OUT & 0xBF; // Make P1.6 go LOW - LED will go OFF
        }
        //Wait 1 second
        __delay_cycles(1000000);
    }
