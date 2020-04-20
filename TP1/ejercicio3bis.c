#define _XTAL_FREQ 4000000

#pragma config FOSC = INTRCIO
#pragma config WDTE = OFF 
#pragma config PWRTE = OFF 
#pragma config MCLRE = OFF 
#pragma config BOREN = OFF 
#pragma config CP = OFF 
#pragma config CPD = OFF 

#include <xc.h>

unsigned char blink = 0;// Blinking state
unsigned int count = 0; // Blinking time counter

void main()
{
    CMCON   = 0x07;     // Disable comparators
    ADCON0  = 0;        // Disable analog converter
    ANSEL   = 0;        // Disable analog signal
    VRCON   = 0;        // Disable voltage reference
    TRISIO  = 0x3E;     // PIN0 output 
    GPIO    = 0;        // All output to low
    OPTION_REG = 0xC7;  // Set Timer0 prescaler to 256 clocks
    T0IE = 1;           // Enable Timer0 interrupt
    GIE = 1;            // Enable global interrupt

    while (1)
    {
	    if (GP1 == 1)
	    {
	        __delay_ms(10);
            if (GP1 == 1)
            {
                GP0 = ~blink;
                blink = ~blink;
            }
            while (GP1 == 1);
	    }
    }
}

void interrupt ISR(void)
{
    if(T0IF)
    {
        count++;
        if (count >= 10 && blink)
        {
            GP0 = ~GP0;
            count = 0;
        }
        T0IF = 0;
    }
}
