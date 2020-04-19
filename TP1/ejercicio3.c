#define _XTAL_FREQ 4000000

#pragma config FOSC = INTRCIO
#pragma config WDTE = OFF 
#pragma config PWRTE = OFF 
#pragma config MCLRE = OFF 
#pragma config BOREN = OFF 
#pragma config CP = OFF 
#pragma config CPD = OFF 

#include <xc.h>

// devuelve 1 si se debe cambiar el estado
int wait(){ 
    int entradaanterior = GP1;
    int contador = 0;

    // el ciclo tardara un segundo 
    // salvo que se apriete y se suelte el pulsador
    while(contador < 1000){ 
        __delay_ms(1);
        if(entradaanterior == 1 && GP1 == 0){//solte el boton
            return 1;
        }
        entradaanterior = GP1;
        contador++;
    }
    return 0;
}

void main(){
    CMCON = 0b00000111;
    ANSEL = 0;
    TRISIO = 0b11111110; // Seteo GP0 como OUTPUT y los demás como INPUT.
    GPIO = 0; //clear GPbits.
    int estado = 0;

    while(1){
        switch(estado){
            case 0://inicial(llego aca con el led apagado) 
                if(wait() == 1){
                   estado = 1; 
                }
            break;
            case 1://encendido(llego aca con el led apagado)
                GP0 = ~GP0;
                if(wait() == 1){
                   estado = 2;
                   break;
                }              
            break; 
            case 2://apagado(llego aca con el parpadeo activo)
                GP0 = 0;
                estado = 0;
                break;
        }           
    }
}