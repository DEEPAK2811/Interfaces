/*
 * UART_Communication.c
 *
 * Tested on: Atmega8
 * Author : DeepakPrakash
 */ 

#include <avr/io.h>
#define F_CPU 8000000UL    // 8MHz frequency
#include <util/delay.h>

void UART_init(){
	UCSRB = (1<<RXEN)|(1<<TXEN);  //ENABLE RECEIVER AND TRANSMITTER
	UCSRC = (1<<URSEL)|(1<<UCSZ1)|(1<<UCSZ0) ; 
	UBRRL= 51;   // BAUD RATE 9600 AS PER ATMEGA8 DATASHEET
	//UBRRH = 0;
	}

void UART_TransmitChar(unsigned char data){
	UDR = data;   //data register
	while((UCSRA &(1<<TXC))==0);  //wait for transmission
}

void UART_TransmitString(char *p){
	while(*p){
	UART_TransmitChar(*(p++));
	_delay_ms(100);
	}
}

char UART_ReceiveChar(){
	while((UCSRA &(1<<RXC))==0);
	return UDR;
}

char *UART_ReceiveString(char *buffer){
	char *p = buffer;
	do 
	{
		*(buffer++) = UART_ReceiveChar();
	} while (*(buffer-1)!= '\r');  //Enter or carrige return
	*buffer = '\0';
	return p;
	
}


int main(void)
{
	char received[20];
	char *data;
	DDRB = 0xFF;
	UART_init();
    while (1) 
    {
		UART_TransmitString("Enter : ");
		_delay_ms(1);
		data = UART_ReceiveString(received);
		
    }
}

