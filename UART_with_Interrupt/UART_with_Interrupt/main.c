/*
 * UART_with_Interrupt.c
 *
 * Tested on: Atmega8
 * Author : DeepakPrakash
 */ 

#include <avr/io.h>
#define F_CPU 1000000UL    // 1MHz frequency
#include <util/delay.h>
#include <avr/interrupt.h>

char received =0 , msg[50];
int count_char;

void UART_init();
void UART_TransmitChar(unsigned char data);
void UART_TransmitString(char *p);
char UART_ReceiveChar();
char *UART_ReceiveString(char *buffer);


int main(void)
{
	DDRB = 0xFF;
	UART_init();
	while (1)
	{
	}
}



void UART_init(){
	UCSRA = (1<<U2X);
	UCSRB = (1<<RXEN)|(1<<TXEN)|(RXCIE);  //ENABLE RECEIVER AND TRANSMITTER
	UCSRC = (1<<URSEL)|(1<<UCSZ1)|(1<<UCSZ0) ; 
    sei(); //global interrupt enable
	UBRRL= 12;   // BAUD RATE 9600 AS PER ATMEGA8 DATASHEET
	UBRRH = 0x00;
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
	} while (*(buffer-1)!= '\r');  //Enter or carriage return
	*buffer = '\0';
	return p;
	}

ISR(USART_RXC_vect)  //ISR for receiver
 {
	
	received = UDR;
	if(received == '\r') //if enter is received
	{ 
		msg[count_char] = '\0';
		count_char=0;	
	}
	else{
		msg[count_char] = received ;
		count_char++;
	}
			}

