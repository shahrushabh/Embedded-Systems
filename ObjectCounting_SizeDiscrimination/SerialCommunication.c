/*
 * SerialCommunication.c
 *
 * Created: 2/20/2015 1:13:36 PM
 *  Author: rvshah
 */ 

//#define MYUBRR 51 // value attained for baud rate 38400 from pg 192 in manual

#include <avr/io.h>
#include <string.h>
#include "lcd.h"
#include "util.h"
#include "SerialCommunication.h"

#define BAUD 57600
#define MYUBRR 34 //51	// Value will be switched to 34 when performing the blutooth operation.


/* Initializes the USART*/
void USART_Init()
{
	
	/* Set baud rate */
	UBRR0H = (unsigned char)(MYUBRR>>8);
	UBRR0L = (unsigned char) MYUBRR;
	// Enable The transmitter
	UCSR0B = (1<<TXEN0);
	// Set frame format: 8data bits, 2stop bit
	UCSR0C = (1<<USBS)|(3<<UCSZ0);	
	// Doubles the speed
	UCSR0A = (0b00000010);
	
}

// Returns the string according to the button being pressed.
void send_string(char* s)
{
	int i = 0;
	//Sends string to putty.
	int length = strlen(s);
	for(i=0; i <= length; i++)
	{
		//POLLING CONDITION
		while(! ( UCSR0A & (1<<UDRE0) ) ) ;
		UDR0 = s[i];
		//wait 10 milli secs between each char sent.
		wait_ms(1);
	}
	UDR0 = 10;
	wait_ms(1);
	UDR0 = 13;
}