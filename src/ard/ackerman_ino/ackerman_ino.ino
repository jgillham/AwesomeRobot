// Controlling a servo position using a potentiometer (variable resistor) 
// by Michal Rinott <http://people.interaction-ivrea.it/m.rinott> 

#include <Servo.h> 
 
Servo myservo;  // create servo object to control a servo 
 
int potpin = 0;  // analog pin used to connect the potentiometer
int val;    // variable to read the value from the analog pin 
 
void setup() 
{ 
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object 
}
#define BODY_WIDTH 4.52D
#define BODY_LENGTH 3.6875D
#define WHEEL_ANGLE_RESOLUTION 180
typedef enum {
  XPOSITION,
  THETA,
  WHEEL_THETA_TL,
  WHEEL_THETA_TR,
  WHEEL_THETA_BL,
  WHEEL_THETA_BR,
  MOTOR_SPEED_TL,
  MOTOR_SPEED_TR,
  MOTOR_SPEED_BL,
  MOTOR_SPEED_BR,
  WHEEL_DATA_TYPE_COUNT
} wheelDataType;
double ackermanLookup[ WHEEL_DATA_TYPE_COUNT ][ WHEEL_ANGLE_RESOLUTION ];

double distance( double x, double y ) [
  return sqrt( x * x + y * y );
}
void generateTable() {
  
  for( int angle = 0; angle < WHEEL_ANGLE_RESOLUTION; ++angle ) {
    double theta = angle - 90;
    double xPos = BODY_LENGTH * tan( 90 - theta );
    ackermanLookup[ XPOSITION ][ angle ] = xPos;
    ackermanLookup[ THETA ][ angle ] = theta;
    // The wheel thetas.
    ackermanLookup[ WHEEL_THETA_TL ][ angle ] = tan( PI / 2 - ( xPos + BODY_WIDTH ) / BODY_LENGTH );
    ackermanLookup[ WHEEL_THETA_TR ][ angle ] = tan( PI / 2 - ( xPos - BODY_WIDTH ) / BODY_LENGTH );
    ackermanLookup[ WHEEL_THETA_BL ][ angle ] = tan( PI / 2 - ( xPos + BODY_WIDTH ) / -BODY_LENGTH );
    ackermanLookup[ WHEEL_THETA_BR ][ angle ] = tan( PI / 2 - ( xPos - BODY_WIDTH ) / -BODY_LENGTH );
    // The speed of the wheels.
    ackermanLookup[ MOTOR_SPEED_TL ][ angle ] = distance( xPos + BODY_WIDTH, BODY_LENGTH );
    ackermanLookup[ MOTOR_SPEED_TR ][ angle ] = distance( xPos - BODY_WIDTH, BODY_LENGTH );
    ackermanLookup[ MOTOR_SPEED_BL ][ angle ] = distance( xPos + BODY_WIDTH, BODY_LENGTH );
    ackermanLookup[ MOTOR_SPEED_BR ][ angle ] = distance( xPos - BODY_WIDTH, BODY_LENGTH );
  }
}
 
void loop() 
{ 
  val = analogRead(potpin);            // reads the value of the potentiometer (value between 0 and 1023) 
  val = map(val, 0, 1023, 0, 179);     // scale it to use it with the servo (value between 0 and 180) 
  myservo.write(val);                  // sets the servo position according to the scaled value 
  delay(15);                           // waits for the servo to get there 
} 
