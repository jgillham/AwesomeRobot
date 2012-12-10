#include <Servo.h> 
//#define NDEBUG // Uncomment to turn off debugging mode.
Servo myservo;  // create servo object to control a servo 
 
int potpin = 0;  // analog pin used to connect the potentiometer
int val;    // variable to read the value from the analog pin 

#define BODY_WIDTH 4.515625
#define BODY_LENGTH 3.6875
#define WHEEL_ANGLE_RESOLUTION 180
enum {
  XPOSITION,
  THETA,
  WHEEL_THETA_FL,  
  WHEEL_THETA_FR,
  WHEEL_THETA_BL,
  WHEEL_THETA_BR,
  MOTOR_SPEED_FL,
  MOTOR_SPEED_FR,
  MOTOR_SPEED_BL,
  MOTOR_SPEED_BR,
  WHEEL_DATA_TYPE_COUNT
};
double ackermanLookup[ WHEEL_DATA_TYPE_COUNT ][ WHEEL_ANGLE_RESOLUTION ];


void setup() 
{ 
  #ifndef NDEBUG
  Serial.begin( 9600 );
  #endif
  generateTable();
  #ifndef NDEBUG
    int data[] = { 0, 1, 2, 45, 90, 135, 179 };
    for( int a = 0; a < sizeof( data ) / sizeof( int ); ++a ) {
      int angle = data[ a ];
      Serial.print( "index: " );
      Serial.println( angle );
      for( int t = 0; t < WHEEL_DATA_TYPE_COUNT; ++t ) {
        Serial.print( "    t: " );
        Serial.print( t );
        Serial.print( "::  " );
        switch (t ) {
          
        }
        double data = ackermanLookup[ t ][ angle ];
        if ( t >= WHEEL_THETA_FL && t <= WHEEL_THETA_BR )
          data *= 180 / PI;
        Serial.println( data );
      }
    }
  #endif
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object 
}


double distance( double x, double y ) {
  return sqrt( x * x + y * y );
}
void generateTable() {
  for( int angle = 0; angle < WHEEL_ANGLE_RESOLUTION; ++angle ) {
    // Leaving theta in degrees because angle is in degrees.
    double theta = angle  - 90;
    // Use trig. to calculate the length along the x-axis to the center of the rotation.
    double xPos = BODY_LENGTH * tan( PI / 2 - theta / 180 * PI );
    ackermanLookup[ XPOSITION ][ angle ] = xPos;
    ackermanLookup[ THETA ][ angle ] = theta;
    // The wheel thetas, which are the calculated angle of the wheels in respect to the point of rotation.
    ackermanLookup[ WHEEL_THETA_FL ][ angle ] = PI / 2 - atan( PI / 2 - ( xPos + BODY_WIDTH ) / BODY_LENGTH );
    ackermanLookup[ WHEEL_THETA_FR ][ angle ] = PI / 2 - atan( PI / 2 - ( xPos - BODY_WIDTH ) / BODY_LENGTH );
    ackermanLookup[ WHEEL_THETA_BL ][ angle ] = PI / 2 - atan( PI / 2 - ( xPos + BODY_WIDTH ) / -BODY_LENGTH );
    ackermanLookup[ WHEEL_THETA_BR ][ angle ] = PI / 2 - atan( PI / 2 - ( xPos - BODY_WIDTH ) / -BODY_LENGTH );
    // The speed of the wheels, which is the ratios between the outer arc length and the inner arc length.
    ackermanLookup[ MOTOR_SPEED_FL ][ angle ] = distance( xPos + BODY_WIDTH, BODY_LENGTH );
    ackermanLookup[ MOTOR_SPEED_FR ][ angle ] = distance( xPos - BODY_WIDTH, BODY_LENGTH );
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
