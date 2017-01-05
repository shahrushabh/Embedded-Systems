/*
 * iRobotMovement.c
 *
 * Created: 1/29/2015 12:04:32 PM
 *  Author: rvshah
 */ 


#include <avr/io.h>
#include "open_interface.h"
#include "lcd.h"
#include "util.h"
#include "movement.h"

int main(void)
{
	oi_t *sensor_data = oi_alloc();
	oi_init(sensor_data);
	int sum = 0;
	while(sum < 200)
	{
		oi_set_wheels(200,200);
		oi_update(sensor_data); // get current state of all sensors
		sum += sensor_data->distance;
		if (sensor_data->bumper_left || sensor_data->bumper_right ) 
		{
			obstacle_encountered(sensor_data);
			sum -= 150;
		}
	}
	oi_set_wheels(0,0);
	oi_free(sensor_data);
}