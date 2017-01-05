// Move robot forward a certain degrees
void move_forward(oi_t *sensor, int centimeteres);
// Turn robot to the specified degrees
void turn_wheels(oi_t *sensor, int degrees);
// Turn the robot accordingly whenever it encounters an obstacle.
void obstacle_encountered(oi_t *sensor);