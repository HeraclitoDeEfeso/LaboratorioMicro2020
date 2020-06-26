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
	GO_nDONE = 1;					// Enable Go/Done
	while(GO_nDONE);				// Wait for completion
	return ADRESH;					// No need for precision
}
void main()
{
	CMCON   = 0x07; 				// Shutdown comparison.
	ANSEL   = 0x18;					// AN3 analog input.
	TRISIO 	= 0x38; 				// GPIO 5, 4, 3 input.
	ADCON0  = 0x0D;					// Convert AN3. Left align
	GPIO 	= 0x00;					// Output to zero.
	unsigned int sensor_value = 0; 	// Coparison buffer
	while(1)
	{
		if (GP5 == 1) 				// Filling command
		{
			__delay_ms(10);
			if (GP5 == 1)
			{
				GP1 = 1;				
				sensor_value = GetADCValue();	
				while (sensor_value < 128)
				{
					sensor_value = GetADCValue();
				}				
				GP1 = 0;
				GP5 = 0;
			}
		}
		else if (GP3 == 1)			// Draining command
		{
			__delay_ms(10);
			if (GP3 == 1)
			{	
				sensor_value = GetADCValue();
				if (sensor_value > 32) 
				{
					GP0 = 1;
					do {
						sensor_value = GetADCValue();
					} while (sensor_value > 32);
				}
				else
				{
					GP2 = 1;
					__delay_ms(2000);
					GP2 = 0;
				}
				GP0 = 0;
				GP3 = 0;
			}
		}
	}
}
