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

    ADC10AE0 = 1 << channel_selected; // allow an analogue signal inputted on channel selected to be converted (move 1 to the left)
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

    // Let the lcd screen turn on
    __delay_cycles(50000);

    // 3. Secuencia de Despertar (Aún en modo 8 bits, enviamos solo nibbles directos)
    send_Command_LCD(0x03);
    __delay_cycles(5000);
    send_Command_LCD(0x03);
    __delay_cycles(200);
    send_Command_LCD(0x03);
    __delay_cycles(200);

    // 4. Cambiar oficialmente a modo 4 bits
    send_Command_LCD(0x02);
    __delay_cycles(200);

    // 5. Ahora que está en 4 bits, enviamos los comandos completos de 8 bits
    send_LCD_char(0x28, 0); // Function set: Interfaz 4-bit, 2 líneas, fuente 5x7
    send_LCD_char(0x0C, 0); // Display On/Off: Enciende la pantalla, apaga el cursor
    send_LCD_char(0x01, 0); // Clear display: Borra la memoria y vuelve al inicio
    __delay_cycles(2000); // Clear display tarda 1.64ms, requiere una pausa más larga
    send_LCD_char(0x06, 0); // Entry mode set: El cursor se moverá hacia la derecha

}

// Función para imprimir una letra completa (8 bits)
void send_LCD_char(char letra, int is_data)
{

    switch (is_data)
    {

    case 0:
        // 1. Aislar y enviar la primera mitad (High Nibble)
        // Desplazamos los 4 bits de la izquierda hacia la derecha para que la función los acepte
        send_Command_LCD(letra >> 4);

        // 2. Aislar y enviar la segunda mitad (Low Nibble)
        // Usamos una máscara lógica para ignorar la parte alta y enviar solo los 4 bits de la derecha
        send_Command_LCD(letra & 0x0F);
        break;

    case 1:
        // Same but sending data
        send_Data_LCD(letra >> 4);
        send_Data_LCD(letra & 0x0F);
        break;

    default:
        break;
    }
}

void send_Command_LCD(char info)
{
    P2OUT = 0x00; //Reset P2OUT
    __delay_cycles(200);
    P2OUT &= 0xFE; //Desactivate RS bit (low)
    __delay_cycles(200);
    P2OUT |= 0x02; //Activate EN bit high -> Sends the info
    __delay_cycles(200);
    P2OUT |= (info << 2); // Place  the data HiGH NIBBLE  for the display on the data lines
    __delay_cycles(100); // 1 ms

    P2OUT &= 0xFD; //Desactivate EN bit with mask 0xFD
    __delay_cycles(200); //2 ms
}

void send_Data_LCD(char info)
{
    P2OUT = 0x00; //Reset P2OUT
    __delay_cycles(200);
    P2OUT |= 0x01; //Activate RS bit high -> Sends the info
    __delay_cycles(200);
    P2OUT |= 0x02; //Activate EN bit high
    __delay_cycles(200);
    P2OUT |= (info << 2); //Place  the data HiGH NIBBLE  for the display on the data lines
    __delay_cycles(100); // 1 ms

    P2OUT &= 0xFD; //Desactivate EN bit with mask 0xFD
    __delay_cycles(200); //2 ms
}

void digit_separation(int temp, char *temp_chars)
{

    //Variables
    int temp_1;
    int temp_2;
    char char_temp_1;
    char char_temp_2;
    char degree_1 = 0xDF; // '°' in ASCII
    char degree_2 = 0x43; // 'C in ASCII
    char end = '\n';

    if (temp > 9)
    {
        //Logic
        temp_1 = temp / 10; // Get first digit
        char_temp_1 = temp_1 + 0x30; // Transform into a char character adding 0x30

        temp_2 = temp % 10; // Get second digit
        char_temp_2 = temp_2 + 0x30; // Transform into a char character adding 0x30

        // Save chars in the array
        temp_chars[0] = char_temp_1;
        temp_chars[1] = char_temp_2;
        temp_chars[2] = degree_1;
        temp_chars[3] = degree_2;
        temp_chars[4] = end;
    }
    else
    {
        //Logic
        char_temp_1 = temp + 0x30; // Transform into a char character adding 0x30

        //Save chars in the array
        temp_chars[0] = char_temp_1;
        temp_chars[1] = degree_1;
        temp_chars[2] = degree_2;
        temp_chars[3] = end;
    }
}

void clean_screen()
{
    send_LCD_char(0x01, 0); // Comand to clean screen
    __delay_cycles(2000);   // delay
}

void print_tag()
{
    send_LCD_char('T', 1);
    send_LCD_char('e', 1);
    send_LCD_char('m', 1);
    send_LCD_char('p', 1);
    send_LCD_char(':', 1);
    send_LCD_char(' ', 1);
}

void stepper_motor_init(){
    P1DIR = 0x0E;  // P2.0 (direction), P2.1 (enable) and  and P2.3 (Step) as outputs
    TA0CCR0 |= 500 - 1; // Timer 0 to count 499 pulses
    TA0CCTL0 |= CCIE; // Enable Timer Interrupt
    TA0CTL |= 0x0220; // Input correct configuration of TASSEL(SMCLK) and MC1 (continuous mode) TA0CTL
    _BIS_SR(GIE);
}
