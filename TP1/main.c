#define _XTAL_FREQ 4000000

#pragma config FOSC = EXTRCIO
#pragma config WDTE = OFF // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF // Power-Up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF // GP3/MCLR pin function select (GP3/MCLR pin function is digital I/O, MCLR internally tied to VDD)
#pragma config BOREN = OFF // Brown-out Detect Enable bit (BOD disabled)
#pragma config CP = OFF // Code Protection bit (Program Memory code protection is disabled)
#pragma config CPD = OFF // Data Code Protection bit (Data memory code protection is disabled)

#define LED GPIObits.GP0
#define BUT GPIObits.GP1

#include <xc.h>

void init() 
{
    CMCON = 0b00000111;
    ANSEL = 0;
    TRISIO=0b11111110; //bit en 1 es input, en 0 es output. Seteo GP0 como OUTPUT y los dem�s como INPUT.
    GPIO = 0;
}

void test()
{
    GP0 = 1;
    __delay_ms(500);
    GP0 = 0;
    __delay_ms(500);
}

void main()
{
    init();
    GP0 = 1;
    while(1)
    {
	GP0 = 0;
	if (GP1 == 1)
	{
	    GP0 = ~GP0;
	    __delay_ms(100); //Por alguna raz�n hay que darle un delay, no s� si es por el emulador, o por alguna especificaci�n que no conozco del manejador de eventos del pic.
	}
    }
}