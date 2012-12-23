// this code expects a servo on pin digital 9, with an IR sensor straped to it on pin analog
//
//first it will take a very slow scan as a base line of what it should see
//then it will take a scan at the TEST_DELAY speed (in microseconds)
//any distortions caused by a fast TEST_DELAY can then be visible, and hence calculated for




#include <Servo.h> 
#define TEST_DELAY 25 // set the ms delay to test here
Servo myservo;  
int average, pos = 0, edge = 0, oldValue, newValue, difference, lastMove, array[181], leftArray[181], rightArray[181], IRpin = 5, Spos=90;   
float volts, distance;

void setup() 
{ 
  Serial.begin(9600);   
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object 
} 
 
void loop() 
{
  /*
  Serial.println("Actual values:");
  for (int i=0; i<=180; i++)
  scan(i, 250);
  printValue();
  for (int i=180; i>=0; i--)
  scan(i, 250);
  printValue();
  */
  Serial.println();
  Serial.println("Left values:");
  for (int i=0; i<=180; i++)
  scan(i, TEST_DELAY, 3);
  printValue();
      
    for (int i = 4;i<177;i++)
    {
    Serial.print(leftArray[i]);
    Serial.print(", ");
    }
    Serial.println();
    Serial.println("Right values:");
  for (int i=180; i>=0; i--)
  scan(i, TEST_DELAY, -3);
  printValue();
  
      for (int i = 4;i<177;i++)
    {
    Serial.print(rightArray[i]);
    Serial.print(", ");
    }
}    
  
void scan(int pos, int Delay, int offset)
{
    myservo.write(pos); 
    delay(Delay); 
    volts = analogRead(IRpin)*0.0048828125;   // value from sensor * (5/1024) - if running 3.3.volts then change 5 to 3.3
    if ( (pos-offset) >= 0 && (pos-offset) <= 180)
    array[pos-offset]= constrain(65 * pow(volts, -1.10), 0, 400);
    return;
}
void printValue()
{
  for (int i=4; i<=177; i++)
  {average=((2*average+array[i-1])/3);
    if (array[i] > 2 * average)
    {
     //right edge of distance array[i]
     rightArray[i-1]=array[i-1];
     leftArray[i]=0;
    }
    else if (average > 2 * array[i])
    {
      //left edge of distance array[i-1]
      leftArray[i]=array[i];
      rightArray[i]=0;
    }
    else
    leftArray[i]=0;
    rightArray[i]=0;
  }
  return;
}
