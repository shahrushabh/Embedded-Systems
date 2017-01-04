/*
 * ServoPositionControl.c
 *
 * Created: 3/9/2015 1:40:39 PM
 *  Author: rvshah
 */ 


#include <avr/io.h>
#include "lcd.h"
#include "util.h"
#include "ServoPositionControl.h"
#define pulse_period  43001;

int currentAngle = 0;				//currentAngle
unsigned pulse_width;			//length of the pulse
signed char direction = 1;		//direction to move 0 is CCW
signed char movement;			//how much to move 

void internal_move_servo(char degree)
{
	pulse_width = 1000+(degree*18.53);	//Compute the pulse_width. 18.7 780 robot 12
	OCR3B = pulse_width-1; // set pulse width
	currentAngle = degree;
}

void servo_init()
{
	OCR3A = pulse_period-1; // number of cycles in the interval
	TCCR3A = (1<<COM3B1) | 3; // set COM set WGM (bits 1 and 0)
	TCCR3B = (3<<WGM32) | 2; // set WGM (bits 1 and 0) and CS bits for pre-scale
	DDRE |= (1<<PE4);	// COnfigure the PE4 pin as the output.
	move_servo(0);
}

void move_servo(char degree)
{	
	//Keep the currentAngle between 180 and 0	
	if(currentAngle > 180)
	{
		internal_move_servo(180);
	}
	else if(currentAngle < 0)
	{
		internal_move_servo(0);
	}
	else
	{
		currentAngle += degree;
		internal_move_servo(currentAngle);
	}

}

int getAngle()
{
	return currentAngle;
}