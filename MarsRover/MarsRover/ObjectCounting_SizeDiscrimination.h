//Scans the area in front of the robot.
void scanArea();
//Contains the computation part of scanning. Updates variables as necessary after the scanning of area is complete.
void getObjects();
//Computes the linear width of the object.
float computeLinearWidth(char width, int ObjDist);
