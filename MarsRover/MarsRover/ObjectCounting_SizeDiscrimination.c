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
#include "ObjectCounting_SizeDiscrimination.h"

// char smallestAngularWidth = 30;
// char smallestObjectDistance = 90;
// char smallestObjectIndex = 0;
// char smallesObjectAngle = 0;
float linearWidth = 0.0;
char currentIndex = 1;
int angle = 0;
int sd, id;
float widths[5] = {0.0,0.0,0.0,0.0,0.0};
char distances[5] = {0,0,0,0,0};
int angles[5] = {0,0,0,0,0};

void scanArea()
{	
	char str[100];
	angle = getAngle();

	while(angle < 180)
	{
		move_servo(1);
		sd = sonarDistance();
		id = InfraDistance();
		angle = getAngle();
		
		if(id > 100 || sd > 100)
		{
			sd = 100;
		}
		sprintf(str,"%d %d",angle,sd);
		send_string(str);
		getObjects();
		wait_ms(10);

	}
	
	//Sending object linear widths

	sprintf(str,"%.2f",widths[0]);
	send_string(str);
	sprintf(str,"%.2f",widths[1]);
	send_string(str);
	sprintf(str,"%.2f",widths[2]);
	send_string(str);
	sprintf(str,"%.2f",widths[3]);
	send_string(str);
	sprintf(str,"%.2f",widths[4]);
	send_string(str);

	//Sending Distances of objects.
		
	sprintf(str,"%d",distances[0]);
	send_string(str);
	sprintf(str,"%d",distances[1]);
	send_string(str);
	sprintf(str,"%d",distances[2]);
	send_string(str);
	sprintf(str,"%d",distances[3]);
	send_string(str);
	sprintf(str,"%d",distances[4]);
	send_string(str);
	
	//Sending angles of objects.
	
	sprintf(str,"%d",angles[0]);
	send_string(str);
	sprintf(str,"%d",angles[1]);
	send_string(str);
	sprintf(str,"%d",angles[2]);
	send_string(str);
	sprintf(str,"%d",angles[3]);
	send_string(str);
	sprintf(str,"%d",angles[4]);
	send_string(str);
	
	internal_move_servo(0);

	resetvalues();
}

// void scanObjects()
// {
// 	char str[100];
// 	angle = getAngle();
// 	
// //	send_string("Degree		IR Distance(cm)		Sonar Distance(cm)");
// 	while(angle < 180)
// 	{
// 		move_servo(1);
// 		sd = sonarDistance();
// 		id = InfraDistance();
// 		angle = getAngle();
// 		sprintf(str, "%d		%d			%d",angle, id, sd);
// 		if(id < 90 && sd < 90)
// 		{
// 			send_string(str);
// 		}
// 		getObjects();
// 		
// 		wait_ms(10);
// 	}
// 	char toPrint[100];
// 	sprintf(toPrint,"Small :Ang:%d ,Dis:%d, Width: %.2f ",smallesObjectAngle, smallestObjectDistance, linearWidth);
// 	send_string(toPrint);
// 	internal_move_servo(0);
// 
// 	resetvalues();
// }

//Check for the objects that are discovered while scanning with servo and also computing the distance and the angular with for the smallest object.
void getObjects()
{
	//The initial distance, from where the object was first detected.
	static int initial_distance = 0;
	//The initial angle, at which the object was first detected.
	static int initial_angle = 0;
	//The final distance, at which this object was last detected.
	static int final_distance = 0;
	//Flag to indicate whether it is the starting edge or the ending edge detection.
	static char startingEdge = 1;
	
	if(startingEdge != 0)	//Looking for the start of the object.
	{
		//If the distance is less then 100 cm, there is likely to be an object.
		if(id < 85)
		{
			startingEdge = 0;
		}
		//Keep updating the initial angle until the start edge of the object is encountered.
		initial_angle = angle;
		initial_distance = sd;
	}
	else	//If the ir sensor distance is greater than 90.
	{
		if(id > 85) // Detects the end edge of the object.
		{
			char angularWidth = angle - initial_angle;	//Computing the angular width.
			
			//Ending edge of the object is encountered and we make sure it is not the sensor error by forcing the object width to be greater than 6.
			//If its not an error, this block computes updates angular width of this object.
	/*		char booyah = 0;*/
			//Print Object Info here
//			char temp_Dist = (initial_distance - (abs(final_distance-initial_distance) / 2));
			int temp_Dist = (initial_distance + final_distance) / 2;
	// 		if(temp_Dist < 40)
	// 		{
	// 			 booyah = 1;
	// 		}
			float temp_lineaWidth = computeLinearWidth(angularWidth, temp_Dist);
	// 		sprintf(toPrint,"#%d    :Ang:%d ,Dis:%d, Width: %.2f,Quality:%d",currentIndex,initial_angle, temp_Dist, temp_lineaWidth, booyah );
	// 		send_string(toPrint);
			widths[currentIndex - 1] = temp_lineaWidth;
			distances[currentIndex - 1] = temp_Dist;
			angles[currentIndex - 1] = (initial_angle + angle) / 2;
			currentIndex++;
			startingEdge = 1;
		}
		final_distance = sd;
	}
}

//FUnction computes the linear width of the object.
float computeLinearWidth(char width, int ObjDist)
{
	return (tan((width/2.0) * (3.14/180)) * ObjDist * 2);
}

void resetvalues()
{
/*
	smallestAngularWidth = 30;
	smallestObjectDistance = 90;
	smallestObjectIndex = 0;
	smallesObjectAngle = 0;*/
	linearWidth = 0.0;
	currentIndex = 1;
	angle = 0;
	for(char i = 0; i < 5; i++)
	{
		widths[i] = 0.0;
		distances[i] = 0;
		angles[i] = 0;
	}
}