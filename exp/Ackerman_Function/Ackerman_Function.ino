#include <Servo.h>

#define BODY_WIDTH 4.515625
#define BODY_LENGTH 3.6875

int throttle, angle;
double FL_Angle, FR_Angle, leftSpeed, rightSpeed, FL_SERVO, FR_SERVO, BL_SERVO, BR_SERVO;
Servo FLSERVO, FRSERVO, BLSERVO, BRSERVO;

void setup() 
{ 
  Serial.begin(9600);
  FLSERVO.attach(2); //front left servo
  FRSERVO.attach(3); //front right servo
  BLSERVO.attach(4); //back left servo
  BRSERVO.attach(5); //back right servo
}


void loop() 
{ 
  //SAMPLE CODE:
  for(angle = -90; angle < 90; angle += 1)  // goes from 0 degrees to 180 degrees 
  {       
  ackSolve(angle, throttle); //solve ackerman
  FLSERVO.write(FL_SERVO);   //set servos
  FRSERVO.write(FR_SERVO);
  BLSERVO.write(BL_SERVO);
  BRSERVO.write(BR_SERVO);           
  delay(100);                // waits 100ms
  } 
  for(angle = 90; angle>=-90; angle-=1)     // goes from 180 degrees to 0 degrees 
  {                                
  ackSolve(angle, throttle); //solve ackerman
  FLSERVO.write(FL_SERVO);   //set servos
  FRSERVO.write(FR_SERVO);
  BLSERVO.write(BL_SERVO);
  BRSERVO.write(BR_SERVO);           
  delay(100);                // waits 100ms
  } 
    
   
} 

// ACKERMAN FUNCTION
// inputs: angle, speed
// outputs: global angles: FL_SERVO, FR_SERVO, BL_SERVO, BR_SERVO
// outputs: global speeds: leftSpeed, rightSpeed

void ackSolve(float theta, double motorSpeed){

  // turn theta into radians
  theta = theta * PI / 180;  
  
  
  // find ackerman center of rotation
  float xPos = BODY_LENGTH / tan(theta);
  
  
  // set wheel angles
  FL_Angle = atan2( BODY_LENGTH, ( xPos + BODY_WIDTH ) ); 
  FR_Angle = atan2( BODY_LENGTH, ( xPos - BODY_WIDTH ) );
  
  
  //set motor speeds
  leftSpeed  = motorSpeed * distance( xPos + BODY_WIDTH, BODY_LENGTH ) / distance( xPos - BODY_WIDTH, BODY_LENGTH ) ; 
  rightSpeed = motorSpeed * distance( xPos - BODY_WIDTH, BODY_LENGTH ) / distance( xPos + BODY_WIDTH, BODY_LENGTH );
  
  
  //fix servo angles that are outside of their ranges, and reverse motors accordingly
      if (FL_Angle < -PI / 2)           //Front Left wheel went too far left
      {FL_Angle += PI;                  //rotate font right wheel 180 to the right
       // reverse motor here
      }
      if (FL_Angle > PI / 2)            //Front right wheel went too far right
      {FL_Angle -= PI;                  //rotate front left wheel 180 to the left
        // reverse motor here
      }
      if (FR_Angle < -PI / 2)           //Front right wheel went too far left
      {FR_Angle += PI;                  //rotate front right wheel 180 to the right
        //reverse motor here
      }
      if (FR_Angle > PI / 2)            //Front right wheel went too far right
      {FR_Angle -= PI;                  //rotate front right wheel 180 to the left
        //reverse motor here
      } 
            
      //exit radians and convert to servo angles
      FL_SERVO=FL_Angle*180/PI+90;
      FR_SERVO=FR_Angle*180/PI+90;
      
      
      //set rear servos to be the inverse of the front servos
      BL_SERVO=-FL_SERVO+180;
      BR_SERVO=-FR_SERVO+180;
}


//Returns the hypotenuse of a triangle
double distance( double x, double y )
{  return sqrt( x * x + y * y );   }

