
/**
 * main.c
 */
int main(void)
{
    return 0;
}

int conversion(int channel_select)
{
    ADC10AE0 = channel_selected; // allow an analogue signal inputted on channel selected to be converted
    ADC10CTL0 &= 0xFFFD; // enc set to 0 to allow the 16 bit registers to be set
    ADC10CTL1 = (12 << channel_selected) | 0x1018; // Select Channel selected (INCHx), Clock Source as SMCLK (AC10SSELx), everything else is not important to us for now
    ADC10CTL0 = 0x0010; // (supply voltage as V+ref (SREFx), fastest sconversion rate (ADC10SHTx), fastest sampling rate (ADC10SR), and turn ADC10 on(ADC10ON)
    ADC10CTL0 |=0x0002; //enc set to 1 to allow conversion
    int result;

    while (1)
       {
       ADC10CTL0 = ADC10CTL0 | 0x0001; //START CONVERSION ON ADC10
       while((ADC10CTL1 & 0x0001) == 1)// WAIT FOR CONVERSION TO COMPLETE
       {
       }
       result = ADC10MEM; // Get the result from the appropriate register
   //PROCESS THE RESULT
       if(result>512)// if the input voltage exceeds 1.65V ,(Floor of ((1.65*1024)/3.3)+0.5 = 512)
       {
           P1OUT= P1OUT | 0x40; // Make P1.6 go HIGH - LED will go ON
       }
       else
       {
           P1OUT= P1OUT & 0xBF; // Make P1.6 go LOW - LED will go OFF
       }
   //Wait 1 second
       __delay_cycles(1000000);
   }
}
