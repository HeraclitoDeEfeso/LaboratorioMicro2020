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
    CMCON   = 0x1D; // Enable comparison AN0 > VREF to GP2 
    ANSEL   = 0x01; // Enable analog signal AN0
    TRISIO  = 0x09; // GP0 input. Others output 
    GPIO    = 0;    // All output to low
    VRCON   = 0x8F; // Enable 3.59VREF for 5VDD

    while (1);      
}