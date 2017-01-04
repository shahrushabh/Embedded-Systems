/*
 * IR_Distance.c
 *
 * Created: 2/27/2015 1:08:04 PM
 *  Author: rvshah
 */ 


#include <avr/io.h>
#include <math.h>
#include "lcd.h"
#include "util.h"
#include "IR_Distance.h"

// Function will initialize the ADC mode.
void ADC_init()
{
	// REFS=11, ADLAR=0, MUX don’t care
	ADMUX = (1<<REFS1) | (1<<REFS0);
	// Enables the ADC and sets the prescaler value.
	ADCSRA = (1<<ADEN) | (7<<ADPS0);
}
// Selects the channel from which the values will be read. Reads the value of ADC and returns it.
unsigned ADC_read(char channel)
{
	ADMUX |= (channel & 0x1F);		// Selection of the channel to read from.
	ADCSRA |= (1<<ADSC);			// Starting the conversion of currrent reading.
	while (ADCSRA & (1<<ADSC));		// Polling condition.
	return ADC;
}

int InfraDistance()
{
	int values = 0;
	char i = 0;
	char count = 3;
	//reading the Quantization values
	while(i<count)
	{
		values += ADC_read(0x02); //LOOK INTO WAIT MS.
		i++;
	}
	double avg_value = values / 3.0; //averaging the quantization values
	return (32179/pow(avg_value,1.175)); //Using the function derived from excel to calculate distance
}