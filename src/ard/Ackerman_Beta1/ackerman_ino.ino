#include <Servo.h> 
#define NDEBUG // Uncomment to turn off debugging mode.
Servo servo_FL;  // create servo object to control a servo 
Servo servo_FR;
Servo servo_BL;
Servo servo_BR;
 
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
  Serial.begin(  9600);
  #endif
  Serial.begin(  9600);
  generateTable();
  #ifndef NDEBUG
    int data[] = { 0, 1, 2, 3, 4, 5, 6 };
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
  servo_FL.attach(8);  // attaches the servo on pin 9 to the servo object 
  servo_FR.attach(9);
  servo_BL.attach(10);
  servo_BR.attach(11);
}


double distance( double x, double y ) {
  return sqrt( x * x + y * y );
}
void generateTable() {
  for( int angle = 0; angle < WHEEL_ANGLE_RESOLUTION; ++angle ) {
    // Leaving theta in degrees because angle is in degrees.
    double theta = angle  - 90;
    // Use trig. to calculate the length along the x-axis to the center of the rotation.
    double xPos = BODY_LENGTH * tan(M_PI / 2 - theta * M_PI / 180);
    ackermanLookup[ XPOSITION ][ angle ] = xPos;
    ackermanLookup[ THETA ][ angle ] = theta;


    
    // The wheel thetas, which are the calculated angle of the wheels in respect to the point of rotation.

        ackermanLookup[ WHEEL_THETA_FL ][ angle ] = PI/2 - atan( ( xPos + BODY_WIDTH ) / BODY_LENGTH  );
        
        ackermanLookup[ WHEEL_THETA_FR ][ angle ] = PI/2 - atan( ( xPos - BODY_WIDTH ) / BODY_LENGTH  );
        ackermanLookup[ WHEEL_THETA_BL ][ angle ] = PI/2 - atan( ( xPos + BODY_WIDTH ) / -BODY_LENGTH );
        ackermanLookup[ WHEEL_THETA_BR ][ angle ] = PI/2 - atan( ( xPos - BODY_WIDTH ) / -BODY_LENGTH );

    // The speed of the wheels, which is the ratios between the outer arc length and the inner arc length.
    ackermanLookup[ MOTOR_SPEED_FL ][ angle ] = distance( xPos + BODY_WIDTH, BODY_LENGTH ) / distance( xPos - BODY_WIDTH, BODY_LENGTH ) ;
    ackermanLookup[ MOTOR_SPEED_FR ][ angle ] = 1/ackermanLookup[ MOTOR_SPEED_FL ][ angle ];
    ackermanLookup[ MOTOR_SPEED_BL ][ angle ] = ackermanLookup[ MOTOR_SPEED_FL ][ angle ];
    ackermanLookup[ MOTOR_SPEED_BR ][ angle ] = ackermanLookup[ MOTOR_SPEED_BR ][ angle ];
    
    //this rectifys the angles for the wheel(s) so they are correct
      if (ackermanLookup[ THETA ][ angle ] <= 0 )
      {
        ackermanLookup[ WHEEL_THETA_FL ][ angle ] = -PI/2 - atan( ( xPos + BODY_WIDTH ) / BODY_LENGTH  );
        ackermanLookup[ WHEEL_THETA_FR ][ angle ] = -PI/2 - atan( ( xPos - BODY_WIDTH ) / BODY_LENGTH  );
        ackermanLookup[ WHEEL_THETA_BL ][ angle ] = -PI/2 - atan( ( xPos + BODY_WIDTH ) / -BODY_LENGTH );
        ackermanLookup[ WHEEL_THETA_BR ][ angle ] = -PI/2 - atan( ( xPos - BODY_WIDTH ) / -BODY_LENGTH );
      }
      if (ackermanLookup[ WHEEL_THETA_FL ][ angle ] < -PI / 2)
      {
        ackermanLookup[ WHEEL_THETA_FL ][ angle ] = ackermanLookup[ WHEEL_THETA_FL ][ angle ] + PI;
        ackermanLookup[ MOTOR_SPEED_FL ][ angle ] = -ackermanLookup[ MOTOR_SPEED_FL ][ angle ];
      }
      if (ackermanLookup[ WHEEL_THETA_FL ][ angle ] > PI / 2)
      {
        ackermanLookup[ WHEEL_THETA_FL ][ angle ] = ackermanLookup[ WHEEL_THETA_FL ][ angle ] - PI;
        ackermanLookup[ MOTOR_SPEED_FL ][ angle ] = -ackermanLookup[ MOTOR_SPEED_FL ][ angle ];
      }
      if (ackermanLookup[ WHEEL_THETA_FR ][ angle ] < -PI / 2)
      {
        ackermanLookup[ WHEEL_THETA_FR ][ angle ] = ackermanLookup[ WHEEL_THETA_FR ][ angle ] + PI;
        ackermanLookup[ MOTOR_SPEED_FR ][ angle ] = -ackermanLookup[ MOTOR_SPEED_FR ][ angle ];
      }
      if (ackermanLookup[ WHEEL_THETA_FR ][ angle ] > PI / 2)
      {
        ackermanLookup[ WHEEL_THETA_FR ][ angle ] = ackermanLookup[ WHEEL_THETA_FR ][ angle ] - PI;
        ackermanLookup[ MOTOR_SPEED_FR ][ angle ] = -ackermanLookup[ MOTOR_SPEED_FR ][ angle ];
      }
      if (ackermanLookup[ WHEEL_THETA_BL ][ angle ] < -PI / 2)
      {
        ackermanLookup[ WHEEL_THETA_BL ][ angle ] = ackermanLookup[ WHEEL_THETA_BL ][ angle ] + PI;
        ackermanLookup[ MOTOR_SPEED_BL ][ angle ] = -ackermanLookup[ MOTOR_SPEED_BL ][ angle ];
      }
      if (ackermanLookup[ WHEEL_THETA_BL ][ angle ] > PI / 2)
      {
        ackermanLookup[ WHEEL_THETA_BL ][ angle ] = ackermanLookup[ WHEEL_THETA_BL ][ angle ] - PI;
        ackermanLookup[ MOTOR_SPEED_BL ][ angle ] = -ackermanLookup[ MOTOR_SPEED_BL ][ angle ];
      }
      if (ackermanLookup[ WHEEL_THETA_BR ][ angle ] < -PI / 2)
      {
        ackermanLookup[ WHEEL_THETA_BR ][ angle ] = ackermanLookup[ WHEEL_THETA_BR ][ angle ] + PI;
        ackermanLookup[ MOTOR_SPEED_BR ][ angle ] = -ackermanLookup[ MOTOR_SPEED_BR ][ angle ];
      }
      if (ackermanLookup[ WHEEL_THETA_BR ][ angle ] > PI / 2)
      {
        ackermanLookup[ WHEEL_THETA_BR ][ angle ] = ackermanLookup[ WHEEL_THETA_BR ][ angle ] - PI;
        ackermanLookup[ MOTOR_SPEED_BR ][ angle ] = -ackermanLookup[ MOTOR_SPEED_BR ][ angle ];
      }

    Serial.print ("   T: ");
    Serial.print (theta);
    Serial.print ("  FL:");
    Serial.println( ackermanLookup[ WHEEL_THETA_FL ][ angle ] * 180 / PI);
    //Serial.print ("  FLMS:");
   // Serial.println( ackermanLookup[ MOTOR_SPEED_FL ][ angle ]);

}
}
 
void loop() 
{ 
  val = analogRead(potpin);            // reads the value of the potentiometer (value between 0 and 1023) 
  val = map(val, 0, 1023, 179, 0);     // scale it to use it with the servo (value between 0 and 180) 
  servo_FL.write(ackermanLookup[ WHEEL_THETA_FL ][ val ]* 180 / PI+90);                  // sets the servo position according to the scaled value 
  servo_FR.write(ackermanLookup[ WHEEL_THETA_FR ][ val ]* 180 / PI+90);               
  servo_BL.write(ackermanLookup[ WHEEL_THETA_BL ][ val ]* 180 / PI+90);               
  servo_BR.write(ackermanLookup[ WHEEL_THETA_BR ][ val ]* 180 / PI+90);   
  Serial.print (":");
  Serial.print(val-90);
    Serial.print ("  FL :");
  Serial.print(ackermanLookup[ WHEEL_THETA_FL ][ val ]* 180 / PI);
  Serial.print ("  RL :");
  Serial.println(ackermanLookup[ WHEEL_THETA_BL ][ val ]* 180 / PI);
  delay(15);                           // waits for the servo to get there 
} 
