/*
 * ObjectCounting_SizeDiscrimination.c
 *
 * Created: 3/27/2015 1:25:32 PM
 *  Author: rvshah
 */ 


#include <avr/io.h>
#include <stdio.h>
#include "lcd.h"
#include "util.h"
#include "ServoPositionControl.h"
#include "IR_Distance.h"
#include "USS_distance.h"
#include "SerialCommunication.h"

void getObjects(char currentAngle);

char initial_angle = 0;
char smallestAngularWidth = 80;
char smallestObjectDistance = 80;
char smallestObjectIndex = 0;
char currentIndex = 0;
int previousDistance;
int sd, id;

char testAngle = 0;

int main(void)
{
    //Initialization of USART, ADC, Input capture, Servo and lcd.
	USART_Init();
	ADC_init();
	iCapture_init();
	servo_init();
	lcd_init();
	
	char str[100];
	char angle = getAngle();
	
	wait_ms(625);	// Wait needed for servo to move to the starting position which is at 0 degrees.
	send_string("Degree		IR Distance(cm)		Sonar Distance(cm)");
	while(angle <= 180)
	{
		move_servo(1);
		sd = sonarDistance();
		id = InfraDistance();
		sprintf(str, "%d		%d			%d",angle, id, sd);
		send_string(str);
		angle = getAngle();
		getObjects(angle);
//		wait_ms(10);
	}
	internal_move_servo(90);
	lprintf("Angular_Width: %d\nIndex: %d\nSonar Distance: %d\nAngle: %d",smallestAngularWidth,smallestObjectIndex,smallestObjectDistance,testAngle);
}

//Check for the objects that are discovered while scanning with servo and also computing the distance and the angular with for the smallest object.
void getObjects(char currentAngle)
{
	//Flag to indicate whether it is the starting edge or the ending edge detection.
	static char startObject = 1;
	// The difference between the precious distances measured by IR sensor. 
	int difference = abs(id-previousDistance);
	// Threshold to check whether an object is encountered.
	if(difference>500) //object detection
	{
		char angularWidth = currentAngle - initial_angle;	//Computing the angular width.
		//Starting edge of the object is encountered.
		if(startObject)
		{
			startObject = 0;
		}
		//Ending edge of the object is encountered and we make sure it is not the sensor error by forcing the object width to be greater than 6.
		//If its not an error, this block computes updates angular width of this object.
		else if(angularWidth > 6)
		{
			if((angularWidth < smallestAngularWidth) && (sd < smallestObjectDistance))
			{
				currentIndex++;
				smallestAngularWidth = angularWidth;
				smallestObjectDistance = sd;
				testAngle = currentAngle;
				smallestObjectIndex = currentIndex;
			}
			startObject = 1;
		}
	}
	else
	{
		//Keep updating the current angle until we encounter the starting edge of an object.
		if(startObject)
		{
			initial_angle = currentAngle;
		}
	}
	previousDistance = id;
}