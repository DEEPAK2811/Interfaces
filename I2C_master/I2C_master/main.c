/*
 * I2C_master.c
 *
 * Tested on : Atmega8
 * Author : DeepakPrakash
 */ 

#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>


void TWI_Init()
{
	TWBR = 0x00; //Clear Status Reg.
	TWBR = 0x0C; //Set Bit Rate
}

void TWI_Start()
{
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTA); // Clear TWI interrupt flag, Enable TWI, Put start condition on SDA
	while((TWCR&(1<<TWINT))==0);  // Wait till start condition is transmitted
	while((TWSR & (0xF8)) != 0x08); // Check for the acknowledgment (start transmitted)
}

void TWI_Write_Addr(unsigned char Addr)
{
	TWDR = Addr;
	TWCR = (1<<TWINT)|(1<<TWEN);    // Clear TWI interrupt flag,Enable TWI
	while((TWCR & (1<<TWINT)) == 0);  // Wait till complete TWDR byte transmitted
	while((TWSR & (0xF8)) != 0x18);   // Check for the acknowledgment (SLA+W transmitted)
}

void TWI_Write_Data(unsigned char Data)
{
	TWDR = Data;
	TWCR = (1<<TWINT)|(1<<TWEN);   // Clear TWI interrupt flag,Enable TWI
	while((TWCR & (1<<TWINT)) == 0);  // Wait till complete TWDR byte transmitted
	while((TWSR & (0xF8)) != 0x28);    // Check for the acknowledgment (Data written)
	PORTB = 0x01;
}
void TWI_Stop()
{
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO); // Clear TWI interrupt flag, Enable TWI, Put stop condition on SDA
}


int main(void)
{
    TWI_Init();
	
    while (1) 
    {
		TWI_Start();
		_delay_ms(1000);
		TWI_Write_Addr(0x20);
		_delay_ms(1000);
		TWI_Write_Data('D');
		_delay_ms(1000);
		TWI_Stop();
		_delay_ms(1000);
    }
}

