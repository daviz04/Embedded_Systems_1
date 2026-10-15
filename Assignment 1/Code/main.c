#include <msp430.h> 
#include "adc_lib.h"
int main(void)
{
    WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer

    //Initiate variables
    long P0_result;
    int high_tmpt = 215; //Result of conversion of 21°C into ADC value;
    char temp_chars[5]; // 2 spaces for temperature, 2 for °C chars and 1 for "\n" symbol
    long temp;
    int i;

    // Configure P1.0
    P1DIR = 0xFE; //Everything else will be output

    P1SEL = 0x00; // no special functions for P1 port lines
    P1IE = 0x00; // no interrupts for P1 port lines

    //Initiate stepper motor
    stepper_motor_init();

    //Initiate LCD Screen
    init_LCD();

    while (1)
    {
        //Start conversion
        P0_result = conversion(0);

        // Prepare Screen
        clean_screen(); //Reset Screen
        print_tag(); // Print "Temp: "

        //Calculate temperature in real time
        temp = (P0_result * 100) / 1023;

        // Show temperatures in the LCD Screen
        digit_separation(temp, temp_chars);
        i = 0;
        while (temp_chars[i] != '\n')
        {
            send_LCD_char(temp_chars[i], 1);
            i++;
        }

        if (P0_result > high_tmpt)
        {
            // funcion de abrir air duct
        }
        else
        {
            // funcion de cerrar air duct
        }

        __delay_cycles(10000);
    }
}
