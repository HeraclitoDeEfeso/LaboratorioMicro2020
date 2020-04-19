/*
 * File:   ejercicio 3.C
 * Author: matias
 *
 * Created on 11 de abril de 2020, 16:53
 */

#define _XTAL_FREQ 4000000

#pragma config FOSC = EXTRCIO
#pragma config WDTE = OFF 
#pragma config PWRTE = OFF 
#pragma config MCLRE = OFF 
#pragma config BOREN = OFF 
#pragma config CP = OFF 
#pragma config CPD = OFF 

#include <xc.h>

// Funcion wait: devuelve 1 si se debe cambiar el estado
int wait(){ 
    int entradaanterior = GP1;
    int contador = 0;
    int botonpulsado = 0;
    
    // El ciclo tardara un segundo.
    // Salvo que se apriete y se suelte el pulsador.
    while(contador < 1000)
    { 
        __delay_ms(1);
        if(entradaanterior != GP1)
        {
            if(botonpulsado == 0)   // Se esta apretando el pulsador
            { 
                botonpulsado = 1;
            } 
            else 
            {
                return 1;           // Solto pulsador. Cambiar de estado
            }    
        }
        entradaanterior = GP1;
        contador++;
    }
    return 0;
}

void main(){
    CMCON = 0b00000111;
    ANSEL = 0;
    TRISIO = 0b11111110;            // GP0 como OUTPUT, el resto INPUT
    GPIO = 0;                       // Clear GPbits.
    int estado = 0;
    
    while(1){
        switch(estado){
            case 0:                 // Inicial, llego con led apagado 
                if(wait() == 1){
                   estado = 1; 
                }
            break;
            case 1:                 // Encendido, llego con led apagado
                GP0 = ~GP0;
                if(wait() == 1){
                   estado = 2;
                   break;
                }              
            break; 
            case 2:                 // Apagado, llego con parpadeo activo
                GP0 = 0;
                estado = 0;
                break;
        }           
    }
}