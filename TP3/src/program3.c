#define _XTAL_FREQ 4000000

#pragma config FOSC     = INTRCIO
#pragma config WDTE     = OFF 
#pragma config PWRTE    = OFF 
#pragma config MCLRE    = OFF 
#pragma config BOREN    = OFF 
#pragma config CP       = OFF 
#pragma config CPD      = OFF 

#include <xc.h>

unsigned int GetADCValue()
{
	__delay_ms(10);
	GO_nDONE = 1;	// Enable Go/Done
	//NOP();
	while(GO_nDONE);// Wait for conversion completion
	return ADRESH;
	//return ((ADRESH << 8) + ADRESL); no necesitamos precisión
}

void main()
{
	/*
	+Niveles de llenado del tanque:
		-Menos nivel minimo: 0.312835vol
		-Nivel Minimo: 0.469253vol
		-Nivel 2: 0.625669vol
		-Nivel 3: 1.877vol
		-Nivel Maximo: 4.37967vol
	*/
	
	CMCON   = 0x07; // Deshabilito los comparadores.
    ANSEL   = 0x18; // Selecciono AN3 como entrada analógica.
	TRISIO 	= 0x38; // Seteo GPIO 5,4,3 como entradas.
	GPIO 	= 0x00;	// NULL.
	//ADCON0	= 0b00001101;
	ADCON0 = 0x0D;
	//ADIE = 1;
	
	unsigned int sensor_value = 0; //El registro del que vamos a tomar es en realidad es un int de 10bits unsigned.
	
	while(1)
	{
		if (GP5 == 1)
		{
			__delay_ms(10);
			if (GP5 == 1)
			{
				GP1 = 1;
				
				sensor_value = GetADCValue();
				while (sensor_value < 128) //Llenando.
				{
					sensor_value = GetADCValue();
				}
				
				GP1 = 0;
				GP5 = 0;
			}
		}
		else if (GP3 == 1)
		{
			__delay_ms(10);
			if (GP3 == 1)
			{
				GP0 = 1;
				
				sensor_value = GetADCValue();
				while (sensor_value > 32) //Vaciando.
				{
					sensor_value = GetADCValue();
				}
				
				GP0 = 0;
				GP3 = 0;
			}
		}
	}
}

/*void __interrupt () interrup_handler (void)
{
       if (ADIF)
       {
            GetADCValue();
            ADIF = 0;
       }

}*/