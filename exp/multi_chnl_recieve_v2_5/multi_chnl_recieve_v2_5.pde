/* try to impliment a send and recieve protocal
   THIS WILL BE THE RECIEVE SIDE
   this side will repeatedly poll the transmiter
   it will poll each channel an unlimited number of times, and wait for a response
   once it gets a response it will write that value out to one of the attached
   devices
*/

#include <Servo.h>

Servo myservo1;

int chnl_1, chnl_2, chnl_3;
int Left, Right;

int flag = 0;
int bounceCount = 0;


int leftSpeed = 9;
int rightSpeed = 10;
int motorLeft0 = 22;
int motorLeft1 = 23;
int motorRight0 = 24;
int motorRight1 = 25;

void setup()
{
  Serial.begin(9600);
  Serial1.begin(9600);
  myservo1.attach(26);

  pinMode(motorLeft0, OUTPUT);
  pinMode(motorLeft1, OUTPUT);
  pinMode(motorRight0, OUTPUT);
  pinMode(motorRight1, OUTPUT);
  
}

void loop()
{
  
  do
  { // (T)
  flag = 0;
  Serial1.write(1); // poll the first chanel
  delay(30);
    if ( Serial1.available() > 0 )
    {
      chnl_1 = Serial1.read();
      flag = 1;
      //myservo1.write(int(chnl_1));
      Serial.print("T: ");
      Serial.print(chnl_1, DEC);
    }
  } while ( flag == 0 );
  
  
  
  do
  { //(X)
  flag = 0;
  Serial1.write(2); // poll the second chanel
  delay(30);
    if ( Serial1.available() > 0 )
    {
      chnl_2 = Serial1.read();
      flag = 1;
     // myservo2.write(int(chnl_2));
      Serial.print("\tX: ");
      Serial.print(chnl_2, DEC);
    }
  } while ( flag == 0 );
  

  
  do
  {// (Y)
  flag = 0;
  Serial1.write(3); //poll the last chanel
  delay(30);
    if ( Serial1.available() > 0 )
    {
      // this one is incomplete you still need to declare an output pin
      chnl_3 = Serial1.read();
      flag = 1;
      Serial.print("\tY: ");
      Serial.print(chnl_3, DEC);
      chnl_3 =map(chnl_3,0,255,0,180);
      myservo1.write(chnl_3);
    }
  } while ( flag == 0 );
  
  if(bounceCount > 99)
  {
    Serial1.flush();
    bounceCount = 0;
  }
  
  // start here*******************************************************
  Left = chnl_1;
  Right = chnl_1;
  
  if (chnl_2 > 1)
  {
    Left = Left - map(chnl_2,128,255,0,255);
    Right = Right + map(chnl_2,128,255,0,255);
  }
  if (chnl_2 <= 128)
  {
    Left = Left + map(chnl_2,0,128,255,0);
    Right = Right - map(chnl_2,0,128,255,0);
  }

if (Left>255){Left=255;}            //cap values
if (Left<0){Left=0;}
if (Right>255){Right=255;}
if (Right<0){Right=0;}

  
  Serial.print("\tLeft: ");
  Serial.print(Left,DEC);
  
  Serial.print("\tRight:");
  Serial.print(Right,DEC);

//now to write the values out!

if (Left>138)
{
  Left = map(Left,128,255,0,255);
  digitalWrite(motorLeft0, HIGH);
  digitalWrite(motorLeft1, LOW);
}

else if (Left<=118)
{
  Left = map(Left,0,128,255,0);
  digitalWrite(motorLeft0, LOW);
  digitalWrite(motorLeft1, HIGH);
}
else {Left=0;}

if (Right>138)
{
  Right =  map(Right,128,255,0,255);
  digitalWrite(motorRight0, HIGH);
  digitalWrite(motorRight1, LOW);
}

else if (Right<=118)
{
  Right = map(Right,0,128,255,0);
  digitalWrite(motorRight0, LOW);
  digitalWrite(motorRight1, HIGH);
} 
else {Right=0;}

  analogWrite(leftSpeed, Left);  
  analogWrite(rightSpeed, Right);
 
  
  Serial.print("\tLeft: ");
  Serial.print(Left,DEC);
  
  Serial.print("\tRight:");
  Serial.println(Right,DEC);
  
}// end loop 


