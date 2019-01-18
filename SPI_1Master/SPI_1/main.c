/*
 * SPI_1.c
 * Author : DeepakPrakash
 * Tested on: Atmega8
 */ 

//SPI Master Code


#include <avr/io.h>
#include <util/delay.h>
#define F_CPU 1000000UL

//Pins as per ATMEGA8

#define MOSI 3
#define MISO 4
#define SS 2
#define SCK 5


int main(void)
{
	int i=0;
    //Defining Output
	DDRB = (1<<MOSI) | (1<<SCK) | (1<<SS) ; 
	DDRC = DDRD = 0xFF ;
	
	//SPI Control Registers : SPI_enable , master select , data rate select
	SPCR = (1<<SPE) | (1<<MSTR) | (1<<SPR0);
	
    while (1) 
    {
	    PORTC = SPDR = i ; // WRITE 1
	    while((SPSR && (1<<SPIF)) == 0); //Checking SPIF flag
	    PORTD = SPDR ; //PRINTING RECEIVED DATA ON PARTD
		_delay_ms(1000);
		i++;
		if (i>8)
		{i=0;
		}
		
    }
}

