#include <msp430.h> 
#include "adc_lib.h"
#include <stdbool.h>
int main(void)
{
    WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer

    //Initiate variables
    long P0_result;
    int high_tmpt = 215; //Result of conversion of 21°C into ADC value;
    char temp_chars[6]; // 3 spaces for temperature, 2 for °C chars and 1 for "\n" symbol
    long temp;
    int i;
    bool air_duct_flag = false;

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

        // Calibrate to 100 the potentiometer
        temp = (P0_result * 100) / 960; // A little bit under the theorical value because it just reach 94
        if (temp >= 100)
        {
            temp = 100; // Max 100 degrees
        }

        // Show temperatures in the LCD Screen
        digit_separation(temp, temp_chars);
        i = 0;
        while (temp_chars[i] != '\n')
        {
            send_LCD_char(temp_chars[i], 1);
            i++;
        }

        if (P0_result > high_tmpt && air_duct_flag == false)
        {
            open_air_duct();

            air_duct_flag = true;

        }
        else if (P0_result <= high_tmpt && air_duct_flag == true)
        {

            close_air_duct();
            air_duct_flag = false;
        }
        else
        {
        }

        __delay_cycles(90000); // Time tested to work fine with the motor, screen and logic
    }
}

