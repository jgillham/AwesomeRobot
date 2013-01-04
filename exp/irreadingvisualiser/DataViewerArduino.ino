#include <Ping.h>
#include <Servo.h>

Ping ping = Ping(A7,0,0);
Servo myservo;

int DELAY = 20;
int pos = 00;
int deltaPos = 5;
int IRpin = A0;                                    // analog pin for reading the IR sensor



void setup() 
{
  Serial.begin(115200);                             // start the serial port
  myservo.attach(9);
}
void loop() 
{
  myservo.write(pos);
  delay(DELAY);
  int IRreading = analogRead(IRpin);   // value from sensor * (5/1024) - if running 3.3.volts then change 5 to 3.3
  //ping.fire();
 
  pos += deltaPos;
  if (pos == 0 || pos == 180) {deltaPos = -deltaPos;}

  //Serial.println(x); Serial.println();
  //  Serial.println(x>>8); Serial.println();
  Serial.print( char('a'));
  delay(DELAY);
  Serial.print( char(pos));
  delay(DELAY);
  Serial.print( char(IRreading%256) );
  delay(DELAY);
  Serial.print( char(IRreading>>8) );
 
  
}
