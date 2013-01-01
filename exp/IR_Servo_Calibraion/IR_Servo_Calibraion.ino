// this code expects a servo on pin digital 9, with an IR sensor straped to it on pin analog
//
//first it will take a very slow scan as a base line of what it should see
//then it will take a scan at the TEST_DELAY speed (in microseconds)
//any distortions caused by a fast TEST_DELAY can then be visible, and hence calculated for



#include <Servo.h> 
Servo myservo;  
int i=0, pos = 0, edge = 0, oldValue, newValue, difference, lastMove, array[181], array2[181], IRpin = 5, Spos=90;   
float a, b, y, volts, distance, movingAvg;
int TEST_DELAY = 60; // set the ms delay to test here
int degs = 2;
const int max_tests = 5;

int tests = max_tests;

void setup() 
{ 
  Serial.begin(9600);   
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object 
  myservo.write(0); 
  delay(200);
} 
 
void loop() 
{/*
  Serial.println("Actual values:");
  for (int i=0; i<=180; i++)
  scan(i, 250);
  printValue();
  for (int i=180; i>=0; i--)
  scan(i, 250);
  printValue();
 */
 // Serial.println("values:");
  
  for (int i=0; i<=90; i+=degs)
  scan(i, TEST_DELAY);
  printValue();
  b=a;
  /*
    for (i=0; i<=180; i++)
  {Serial.print(array[i]);
Serial.print(", ");}
Serial.println();*/
  for (int i=90; i>=0; i-=degs)
  scan(i, TEST_DELAY);
  printValue();
  y=(b-a)/2;
  movingAvg=(movingAvg*(max_tests-1)+y)/max_tests;
 /* Serial.println(movingAvg);
    for (i=0; i<=180; i++)
  {Serial.print(array[i]);
Serial.print(", ");}
Serial.println();
 */ 
tests--;
if (tests<1)
{
  Serial.print("delay:");
  Serial.print(TEST_DELAY);
  Serial.print(", accuracy:");
  Serial.print(degs);
  Serial.print(" , smear:");
  Serial.print(movingAvg);
  Serial.println(" degrees");
  tests = max_tests;
  TEST_DELAY++;
  if (TEST_DELAY>60)
  {
   degs++;
   TEST_DELAY = 1;
   
  }
}
}    

  
void scan(int pos, int Delay)
{
    myservo.write(pos); 
    delay(Delay); 
    volts = analogRead(IRpin)*0.0048828125;   // value from sensor * (5/1024) - if running 3.3.volts then change 5 to 3.3
    array[pos/degs]= constrain(65 * pow(volts, -1.10), 0, 300);
    return;
}
void printValue()
{ int x =0;
  for (i=0; i<=180; i++)
  {
    if (array[i]>100 && x == 0)
    {
    //Serial.print(i);
    a=i;
    //Serial.print(", ");
    x=1;
    }
  }
  //Serial.println();
  return;
}
