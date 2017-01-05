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

signed angle = 0;				//current angle
unsigned pulse_width;			//length of the pulse
signed char direction = 1;		//direction to move 0 is CCW
signed char movement;			//how much to move 

void internal_move_servo(signed degree)
{
	pulse_width = 1000+(degree*18.53);	//Compute the pulse_width.
	OCR3B = pulse_width-1; // set pulse width
}

void servo_init()
{
	OCR3A = pulse_period-1; // number of cycles in the interval
	TCCR3A = (1<<COM3B1) | 3; // set COM set WGM (bits 1 and 0)
	TCCR3B = (3<<WGM32) | 2; // set WGM (bits 1 and 0) and CS bits for pre-scale
	DDRE |= (1<<PE4);	// COnfigure the PE4 pin as the output.
	move_servo(0);
}

void move_servo(signed degree)
{	
	//Keep the angle between 180 and 0	
	if(angle > 180)
	{
		internal_move_servo(180);
	}
	else if(angle < 0)
	{
		internal_move_servo(0);
	}
	else
	{
		angle += degree;
		internal_move_servo(angle);
	}

}

signed getAngle()
{
	return angle;
}