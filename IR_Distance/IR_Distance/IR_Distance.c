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

void ADC_init();
unsigned ADC_read(char channel);

int main(void)
{
	// Initialize lcd and adc.
	lcd_init();
	ADC_init();
	
	int values = 0;
	char i = 0;
    while(1)
    {
	   values += ADC_read(0x02);			//reading the Quantization values
	   if(i == 5)		//counting to 5 values
	   {
		   double avg_value = values / 5.0; //averaging the quantization values
		   float distance = (float)(32179/pow(avg_value,1.175)); //Using the function derived from excel to calculate distance
		   lprintf("%d  %.3fcm",(int)avg_value,distance); //printing the result
	   
		   //reset the values
		   i = 0; 
		   values = 0;
	   }
	   wait_ms(50);				// All the readings are done after an interval of 50ms.
	   i++; 
    }
}

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