#include "open_interface.h"
#include "movement.h"
#include "util.h"

void move_robot(oi_t *sensor, int centimeteres){
	int run = 0;
	sensor_type currentStatus;
	if(centimeteres > 0)
	{
		oi_set_wheels(150,150);
		while (run < centimeteres)
		{
			currentStatus = sensor_check(sensor);
			
			//do this if obstacle encountered
			if((currentStatus != NONE))
			{
				oi_set_wheels(0,0);
//				char toPrint[100];
//				sprintf(toPrint,"The robot stopped at %d", (run/10));
//				send_string(toPrint);
				oi_update(sensor);
				break;
			}
			oi_update(sensor);
			run += sensor->distance;
		}
		if(currentStatus == NONE)
		{
			send_string("NONE");
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



void turn_wheels(oi_t *sensor, int degrees)
{
	oi_update(sensor);
	int _angle = 0;
	int anglecorrection = (degrees*(360/370));
	
	if(degrees > 0) //turn counterclockwise if negative degrees(ve)
	{
		oi_set_wheels(100,-100);
		while (_angle < degrees - anglecorrection){
			oi_update(sensor);
			_angle += sensor->angle;
		}
	}
	else // move clockwise if degrees parameter is positive
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


// This function is going to check the bumper and the cliff flags of the sensor return values accordingly.
sensor_type sensor_check(oi_t *sensor)
{

	if((sensor->bumper_left) || (sensor->bumper_right))
	{
		if((sensor->bumper_left))
		{
/*			send_string("LEFT BUMPER HIT");*/
			send_string("B L");
		}
		if((sensor->bumper_right))
		{
/*			send_string("RIGHT BUMPER HIT");*/
			send_string("B R");
		}
		//move back away from the obstacle hit
		move_robot(sensor,-50);
		return BUMPER;
		
	}
	else if((sensor->cliff_frontleft) || (sensor->cliff_frontright) || (sensor->cliff_left) || (sensor->cliff_right))
	{
		if(sensor->cliff_frontleft)
		{
/*			send_string("CLIFF TO THE LEFT WATCH OUT");*/
			send_string("F L CL");
		}
		else if(sensor->cliff_left)
		{
			send_string("L CL");
		}
		else if(sensor->cliff_frontright)
		{
/*			send_string("CLIFF TO THE RIGHT WATCH OUT");*/
			send_string("F R CL");
		}
		else if(sensor->cliff_right)
		{
			send_string("R CL");
		}
		move_robot(sensor,-50);
		return CLIFF;
	}
	else
	{
		return light_check(sensor);
	}
}

//TO DO
/* Light Sensor calibration robot 12

	White tape:
	Left : 900+
	Front Left: 950+
	Front Right: 450+
	Right: 900+
	
	Black tape:
	Left : 200-
	Front Left: 90-
	Front Right: 90-
	Right: 200 - 150-
	
	Gray Tiles:
	Left: 115
	Left Front: 290
	Right Front: 100
	Right: 215
*/	
// This function is going to check the cliff flags of the sensor for light checks and return values accordingly.
sensor_type light_check(oi_t *sensor)
{
	if(((sensor->cliff_frontleft_signal) < 45) || ((sensor->cliff_frontright_signal) < 25) || ((sensor->cliff_left_signal) < 25) || ((sensor->cliff_right_signal) < 45))
	{
		
		if((sensor->cliff_frontleft_signal) < 45)
		{
/*			send_string("Goal Reached at Front Left. BLACK");*/
			send_string("F L BLACK");
		}
		else if((sensor->cliff_frontright_signal) < 25)
		{
/*			send_string("Goal Reached at Front Right. BLACK");*/
			send_string("F R BLACK");
		}
		else if((sensor->cliff_left_signal) < 25)
		{
/*			send_string("Goal Reached at Left. BLACK");*/
			send_string("L BLACK");
		}
		else if((sensor->cliff_right_signal) < 45)
		{
/*			send_string2("Goal Reached at Right. BLACK");*/
			send_string("R BLACK");
		}
		//move over the goal
		return BLACK;
	}
	else if(((sensor->cliff_frontleft_signal) > 472) || ((sensor->cliff_frontright_signal) > 212) || ((sensor->cliff_left_signal) > 200) || ((sensor->cliff_right_signal) > 370))
	{
		
		//tell us where the white line is
		if(((sensor->cliff_frontleft_signal) > 472) || ((sensor->cliff_frontright_signal) > 212))
		{
/*			send_string("WHITE LINE IN FRONT");*/
			send_string("F W");
		}
		else if(((sensor->cliff_left_signal) > 200))
		{
/*			send_string("WHITE LINE TO THE LEFT");*/
			send_string("L W");
		}
		else if(((sensor->cliff_right_signal) > 370))
		{
/*			send_string("WHITE LINE TO THE RIGHT");*/
			send_string("R W");
		}
		return WHITE;
	}
	else
	{
		return NONE;
	}
}

//	ROBOT 10 ROBOT 10 ROBOT 10 ROBOT 10
// 	if(((sensor->cliff_frontleft_signal) > 900) || ((sensor->cliff_frontright_signal) > 300) || ((sensor->cliff_left_signal) > 450) || ((sensor->cliff_right_signal) > 700))
// 	{
// 		
// 		if((sensor->cliff_frontleft_signal) > 900)
// 		{
// 			send_string("Goal Reached at Front Left");
// 		}
// 		else if((sensor->cliff_frontright_signal) > 300)
// 		{
// 			send_string("Goal Reached at Front Right");
// 		}
// 		else if((sensor->cliff_left_signal) > 450)
// 		{
// 			send_string("Goal Reached at Left");
// 		}
// 		else if((sensor->cliff_right_signal) > 700)
// 		{
// 			send_string("Goal Reached at Right");
// 		}
// 		//move over the goal
// 		return BLACK;
// 	}
// 	else if(((sensor->cliff_frontleft_signal) > 650 )|| ((sensor->cliff_frontright_signal) > 172) || ((sensor->cliff_left_signal) > 300) || ((sensor->cliff_right_signal) > 530))
// 	{
// 		
// 		//tell us where the white line is
// 		if(((sensor->cliff_frontleft_signal) > 650) || ((sensor->cliff_frontright_signal) > 172))
// 		{
// 			send_string("WHITE LINE IN FRONT");
// 		}
// 		else if(((sensor->cliff_left_signal) > 300))
// 		{
// 			send_string("WHITE LINE TO THE LEFT");
// 		}
// 		else if(((sensor->cliff_right_signal) > 530))
// 		{
// 			send_string("WHITE LINE TO THE RIGHT");
// 		}
// 		return WHITE;
// 	}
// 	else
// 	{
// 		return NONE;
// 	}
// }
// ROBOT 10 ENDS ROBOT 10 ENDS ROBOT 10 ENDS

//moves the robot 10 cm
void move_robot_without_sensor(oi_t *sensor)
{
	int run = 0;
		oi_set_wheels(150,150);
		while (run < 100)
		{
			oi_update(sensor);
			run += sensor->distance;
		}
		oi_set_wheels(0,0);
}