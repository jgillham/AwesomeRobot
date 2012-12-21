// this code expects a servo on pin digital 9, with an IR sensor straped to it on pin analog
//
//first it will take a very slow scan as a base line of what it should see
//then it will take a scan at the TEST_DELAY speed (in microseconds)
//any distortions caused by a fast TEST_DELAY can then be visible, and hence calculated for
i



#include <Servo.h> 
#DEFINE TEST_DELAY 25 // set the ms delay to test here
Servo myservo;  
int pos = 0, edge = 0, oldValue, newValue, difference, lastMove, array[181], array2[181], IRpin = 5, Spos=90;   
float volts, distance;

void setup() 
{ 
  Serial.begin(9600);   
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object 
} 
 
void loop() 
{
  Serial.println("Actual values:");
  for (int i=0; i<=180; i++)
  scan(i, 250);
  printValue();
  for (int i=180; i>=0; i--)
  scan(i, 250);
  printValue();
  
  Serial.println("Fast values:");
  for (int i=0; i<=180; i++)
  scan(i, TEST_DELAY);
  printValue();
  for (int i=180; i>=0; i--)
  scan(i, TEST_DELAY);
  printValue();
}    
  
void scan(int pos, int Delay)
{
    myservo.write(pos); 
    delay(Delay); 
    volts = analogRead(IRpin)*0.0048828125;   // value from sensor * (5/1024) - if running 3.3.volts then change 5 to 3.3
    array[pos]= constrain(65 * pow(volts, -1.10), 0, 300);
    return;
}
void printValue()
{
  for (int i=0; i<=180; i++)
  {
    Serial.print(array[i]);
    Serial.print(", ");
  }
  Serial.println();
  return;
}
