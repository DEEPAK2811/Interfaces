/*
 * I2C_slave.c
 *
 * Tested on :Atmega8
 * Author : DeepakPrakash
 */ 

#include <avr/io.h>

#define F_CPU 8000000UL
#include <util/delay.h>

void TWI_Init(unsigned char Slave_Address)
{
	TWAR = Slave_Address;   //set slave address
}

unsigned char TWI_Read_Data()
{
	unsigned char x;
	TWCR = (1<<TWINT)|(1<<TWEA)|(1<<TWEN);  //clear interrupt,get ack bit and enable bit
	while((TWCR & (1<<TWINT)) == 0);
	while((TWSR & (0xF8)) != 0x80);  // wait for ack
	x = TWDR;
	return x;
}
void TWI_Match_ACK()    //wait while data ack not received
{
	while((TWSR & (0xF8))!= 0x60)  //loop till correct ack received
	{
		TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWEA); // Get acknowlegement, Enable TWI, Clear TWI interrupt flag
		while((TWCR & (1<<TWINT)) == 0);  // Wait for TWINT flag
	}
}


int main(void)
{  
	char x;
	DDRB = 0xFF;
	
	TWI_Init(0x20);  //putting slave address
	
	while(1)
	{
		TWI_Match_ACK();  //wait for ack to receive
		x = TWI_Read_Data();  //received data		
	}

}

