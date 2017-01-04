/*
 * MarsRover.c
 *
 * Created: 4/10/2015 12:16:08 PM
 *  Author: rvshah
 */ 


#include <avr/io.h>
#include "open_interface.h"
#include "lcd.h"
#include "util.h"
#include "movement.h"
#include "IR_Distance.h"
#include "USS_distance.h"
#include "SerialCommunication.h"
#include "ServoPositionControl.h"
#include "ObjectCounting_SizeDiscrimination.h"

// Initialization of io interface, lcd, adc, usart and sonar.
void initializations(oi_t *Sensor);
//Perform actions depending on the command received.
void perform(oi_t *Sensor, char letter);
//Play song
void playSong();


char songNotes[2] = {40,50,0};
char noteDurations[2]= {25,10,0};
	
	
//ROBOT 10
int s = 0;
int main(void)
{
	oi_t *sensor = oi_alloc();
	// Initialization of io interface, lcd, adc, usart and sonar.
	initializations(sensor);
	while(1)
	{
// 		if(s == 1)
// 		{
// 			scanArea();
// 		} 
// 		else
// 		{
// 			scanObjects();
// 		}
//		send_string("R-right, L-left, F-forward, B-backward, D-OBJ Scan, G - Position on goal");
		perform(sensor,commandReceived());	
		oi_update(sensor);
	}
}


// Initialization of io interface, lcd, adc, usart, sonar, and servo.
void initializations(oi_t *Sensor)
{
	oi_init(Sensor);
	lcd_init();
	ADC_init();
	USART_Init();
	servo_init();
	iCapture_init();
}

//Perform actions depending on the command received.
void perform(oi_t *Sensor, char letter)
{
	switch (letter)
	{
		//Turn Right.
		case 'r':
			turn_wheels(Sensor,(-1 * getValue()));
			break;
		//Turn Left.
		case 'l':
			turn_wheels(Sensor,getValue());
			break;
		//Move Forward.
		case 'f':
			move_robot(Sensor,getValue()*10);
			break;
		//Move Backwards.
		case 'b':
			move_robot(Sensor,(-1*getValue()*10));
			break;
		//Scan area.
		case 's':
			scanArea();
			break;
		//Park Robot.
		case 'p':
			move_robot_without_sensor(Sensor);
			break;
		//Play Music.
		case 'm':
		lprintf("I MADE IT!!");
			while(1)
			{
				playSong();
			}
	}
}


int getValue()
{
//	char toPrint1[3];
/*	send_string2("Enter a Value :");*/
	char temp1 = commandReceived();
/*	sprintf(toPrint1,"%d", temp1);
	send_string2(toPrint1);*/
	
	char temp2 = commandReceived();
/*
	sprintf(toPrint1,"%d", temp2);
	send_string2(toPrint1);
	send_string("");
*/
	int value = (temp1 *10) + temp2;
	
	return value;
}


void playSong()
{
	oi_load_song(2,2,songNotes,noteDurations);
	oi_play_song(2);
}