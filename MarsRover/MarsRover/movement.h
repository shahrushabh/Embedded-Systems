//Enum definition of sensor_type.
typedef enum
{
	BUMPER, CLIFF, WHITE, BLACK, NONE
} sensor_type;
// Move robot forward a certain degrees
void move_robot(oi_t *sensor, int centimeteres);
// Turn robot to the specified degrees
void turn_wheels(oi_t *sensor, int degrees);
//Check for light sensors.
sensor_type light_check(oi_t *sensor);
//Check for all other sensors; such as cliff sensor as well as bumber sensor of the robot.
sensor_type sensor_check(oi_t *sensor);
void move_robot_without_sensor(oi_t *sensor);