#define _XTAL_FREQ 4000000

#pragma config FOSC     = INTRCIO
#pragma config WDTE     = OFF 
#pragma config PWRTE    = OFF 
#pragma config MCLRE    = OFF 
#pragma config BOREN    = OFF 
#pragma config CP       = OFF 
#pragma config CPD      = OFF 

#include <xc.h>

void main()
{
    CMCON       = 0x07;     // Disable comparators
    ANSEL       = 0;        // Disable analog signal
    TRISIO      = 0x3E;     // PIN0 output 
    GPIO        = 0;        // All output to low
    T1CON       = 0x31;     // Set Timer1 prescaler to 8 clocks
    PEIE        = 1;        // Enable peripherical interrupt
    GIE         = 1;        // Enable global interrupt

    while (1)
    {
	    if (GP1 == 1)
	    {
	        __delay_ms(10);
            if (GP1 == 1)
            {
                GP0 = ~T1IE;
                T1IE = ~T1IE;
            }
            while (GP1 == 1);
	    }
    }
}

void interrupt ISR(void)
{
    if(T1IF)
    {
        GP0 = ~GP0;
        T1IF = 0;
    }
}
