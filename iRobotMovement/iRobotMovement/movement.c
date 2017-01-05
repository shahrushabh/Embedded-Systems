#include "open_interface.h"

void move_forward(oi_t *sensor, int centimeteres){
	int run = 0;
	if(centimeteres > 0)
	{
		oi_set_wheels(200,200);
		while (run < centimeteres)
		{
			oi_update(sensor);
			run += sensor->distance;
		}
	}
	else if (centimeteres < 0 )
	{
		oi_set_wheels(-200,-200);
		while (run > centimeteres)
		{
			oi_update(sensor);
			run += sensor->distance;
		}
	}

	oi_set_wheels(0,0);
	oi_update(sensor);
	wait_ms(50);
}

void turn_wheels(oi_t *sensor, int degrees){
	oi_update(sensor);
	int _angle = 0;
	int anglecorrection = (degrees*(360/370));
	
	if(degrees > 0) //turn counterclockwise (ve)
	{
		oi_set_wheels(100,-100);
		while (_angle < degrees - anglecorrection){
			oi_update(sensor);
			_angle += sensor->angle;
		}
	}
	else // move clockwise
	{
		oi_set_wheels(-100,100);
		while (_angle > degrees + anglecorrection){
			oi_update(sensor);
			_angle += sensor->angle;
		}
	}
	
	oi_set_wheels(0,0);
	oi_update(sensor);
	wait_ms(50);
	
	
}
// this method will end up -15mm of where you bumped in. 
void obstacle_encountered(oi_t *sensor){
	oi_update(sensor);
	if(sensor->bumper_left) 
	{
		oi_set_wheels(0,0);
		move_forward(sensor,-150);
		turn_wheels(sensor,-90);
		move_forward(sensor,250);
		turn_wheels(sensor,90);
		
			
	} else if(sensor->bumper_right){
		oi_set_wheels(0,0);
		move_forward(sensor,-150);
		turn_wheels(sensor,90);
		move_forward(sensor,250);
		turn_wheels(sensor,-90);
	}
}