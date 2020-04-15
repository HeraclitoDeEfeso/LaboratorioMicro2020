/*
 * File:   ejercicio 2.c
 * Author: matia
 *
 * Created on 11 de abril de 2020, 16:53
 */

#define _XTAL_FREQ 4000000

#pragma config FOSC = EXTRCIO
#pragma config WDTE = OFF // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF // Power-Up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF // GP3/MCLR pin function select (GP3/MCLR pin function is digital I/O, MCLR internally tied to VDD)
#pragma config BOREN = OFF // Brown-out Detect Enable bit (BOD disabled)
#pragma config CP = OFF // Code Protection bit (Program Memory code protection is disabled)
#pragma config CPD = OFF // Data Code Protection bit (Data memory code protection is disabled)

#include <xc.h>

void init() 
{
    CMCON = 0b00000111;
    ANSEL = 0;
    TRISIO = 0b11111110; //bit en 1 es input, en 0 es output. Seteo GP0 como OUTPUT y los demás como INPUT.
    GPIO = 0; //clear GPbits.
}

void test()
{
    GP1 = 1;
    __delay_ms(5000);
    GP1 = 0;
    __delay_ms(500);
}
void main()
{
    init();
    while(1)
    {
        GP0 = 0;
        GP1 = 0;
        while (GP1 == 1)
        {
            GP0 = 1;
             __delay_ms(1000);
            GP0 = 0;
            __delay_ms(1000); //Por alguna razón hay que darle un delay, no sé si es por el emulador, o por alguna especificación que no conozco del manejador de eventos del pic.
        }
       
        if (GP1 == 0)
        {
        GP0 = 0;   
        __delay_ms(1000);
        }
    }
}