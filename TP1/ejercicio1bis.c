#define _XTAL_FREQ 4000000

#pragma config FOSC = INTRCIO
#pragma config WDTE = OFF 
#pragma config PWRTE = OFF 
#pragma config MCLRE = OFF 
#pragma config BOREN = OFF 
#pragma config CP = OFF 
#pragma config CPD = OFF 

#include <xc.h>

void main()
{
    CMCON   = 0x07; // Disable comparators
    ADCON0  = 0;    // Disable analog converter
    ANSEL   = 0;    // Disable analog signal
    VRCON   = 0;    // Disable voltaje reference
    TRISIO  = 0x3E; // PIN0 output 
    GPIO    = 0;    // All output to low
    
    while (1)
    {
	    if (GP1 == 1)
	    {
	        __delay_ms(10);
            if (GP1 == 1)
            {
                GP0 = 1;
            }
            while (GP1 == 1);
            GP0 = 0;
	    }
    }
}
