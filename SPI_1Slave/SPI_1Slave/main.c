/*
 * SPI_1Slave.c
 * Tested on :Atmega8 
 * Author : DeepakPrakash
 */ 

#include <avr/io.h>
#define F_CPU 1000000UL
#include <util/delay.h>

#define MOSI 3   //Input
#define MISO 4  //Output
#define SCK 5   //Input
#define SS 2   //Input


int main(void)
{
	int i = 8;
    DDRC = DDRD = 0xFF ;
	DDRB = (1<<MISO);
	
	//Enable SPI , master slave(MSTR) to 0 and , SCK drived by MSTR
	SPCR = (1<<SPE);
		
    while (1) 
    {
		PORTC = SPDR = i;
		while((SPSR &&(1<<SPIF))==0);
		PORTD = SPDR ;
		_delay_ms(1000);
		i--;
		if (i<0)
		{i=8;
		}
    }
}

