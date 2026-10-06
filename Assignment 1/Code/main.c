#include <msp430.h> 
#include "adc_lib.h"

/**
 * main.c
 */
int main(void)
{
    WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer

    //Initiate variables
    int P0_result;
    int high_tmpt = 215 //Result of conversion of 21°C into Nout;


    // Configure P1.0
    P1DIR = 0xFE //Everything else will be output

    P1SEL = 0x00; // no special functions for P1 port lines
    P1IE = 0x00; // no interrupts for P1 port lines

    while (1)
    {
        //Start conversion
        P0_result = conversion(0);

        //Turn off both LEDs (P1.0 y P1.6)
        P1OUT &= 0xBE;

        if (P4_result > high_tmpt){
            // funcion de abrir air duct
        } else {
            // funcion de cerrar air duct
        }
    }
}
