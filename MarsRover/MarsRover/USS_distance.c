/*
 * USS_distance.c
 *
 * Created: 3/5/2015 12:05:38 PM
 *  Author: rvshah
 */ 

	
#include <avr/io.h>
#include <avr/interrupt.h>
#include "lcd.h"
#include "util.h"
#include "USS_distance.h"

volatile int rising_clk = 0;				// Stores the time of rising edge.
volatile int falling_clk = 0;				// Stores the time of falling edge.
volatile unsigned char rising_edge = 1;		// Flag to check the rising edge of the pulse, which initially is 1.
volatile unsigned char falling_edge = 0;	// Flag to check the falling edge of the pulse.
volatile unsigned char event_occured = 0;	// Flag to determine whether an entire event has occurred.

int sonarDistance()
{
	send_pulse();			//Send pulse.
	while(!event_occured);		//waiting till event occurs
	float scaling_factor = (1024.0/16000000)*17000;
	unsigned time = falling_clk - rising_clk;
	time = abs(time);
	event_occured = 0;
	return time*scaling_factor;
}

// Sends a pulse. Output on port D.
void send_pulse()
{
	TIMSK ^= (1<<TICIE1);
	DDRD |= 0x10;
	PORTD |= 0x10;
	wait_ms(1); 
	PORTD &= 0xEF;
	DDRD &= 0xEF;
	TIFR |= (0x20);
	TIMSK ^= (1<<TICIE1);
}

// Initialize and configure the registers to capture the rising edge and other functions described below.
void iCapture_init()
{
	TCCR1A = 0;			// Sets all the COM bits to 0 as directed.
	TCCR1B = (1<<ICNC1) | (1<<ICES1) | 5;	// Enables the Input Capture Noise Canceler, Initially capturing the rising edge and sets the preschooler to 8.
	TIMSK = (1<<TICIE1) ;		// Enables the input capture interrupt for Timer/Counter 1 
}

//This ISR occurs whenever an edge is detected that is defined by input capture edge selector in TCCR1B register.
ISR(TIMER1_CAPT_vect)
{

	if(rising_edge)
	{	
		rising_clk = ICR1;		// Read the time when the falling edge occurred.
		falling_edge = 1;		//falling edge is detected.
		rising_edge = 0;
		TCCR1B ^= (1<<ICES1);	// Configure to detect rising edge
	}
	else if(falling_edge)
	{
		falling_clk = ICR1;		// Read the time when the rising edge occurred.
		rising_edge = 1;
		falling_edge= 0;
		event_occured = 1;		// Event has occurred as soon as the falling edge is detected. 
		TCCR1B ^= (1<<ICES1);	// Configure to detect falling edge
	}
}