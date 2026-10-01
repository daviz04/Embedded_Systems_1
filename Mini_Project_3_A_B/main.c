#include <msp430.h> 
#include "adc_lib.h"

/**
 * main.c
 */
int main(void)
{
    WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer

    //Initiate variables
    int P4_result;
    int P5_result;

    // Configure P1.4 and P1.5 at the same time
    P1DIR = 0xCF; //Everything else will be output

    P1SEL = 0x00; // no special functions for P1 port lines
    P1IE = 0x00; // no interrupts for P1 port lines

    while (1)
    {
        //Start conversions
        P4_result = conversion(4);
        P5_result = conversion(5);

        //Turn off both LEDs (P1.0 y P1.6)
        P1OUT &= 0xBE;

        if ((abs(P5_result - P4_result)) <= 10)
        { //Voltages almost equal --> Turn on both LEDs
            P1OUT |= 0x41; // Enciende ambos (P1.0 y P1.6)
        }
        else if (P4_result > P5_result)
        {
            P1OUT |= 0x01; // Enciende solo el verde (P1.0)
        }
        else if (P4_result < P5_result)
        {
            P1OUT |= 0x40; // Enciende solo el rojo (P1.6)
        }
    }
}
