// this code grabs physical left edges in front of a SHARP long range ir sensor + servo combo
// and follows the edge around the environment.
// We learned from caibration that there is this relationship:
//data blur (in degrees) = Shift
//milliseconds delay = ms
//Shift = f(ms)
//this is why you will see a moving avg of 10 and a ms delay of 9
//the moving average tries to keep track of enough previous values
//to that when it sees "Hey! I found an edge!" (when in fact it is pointing 10 degrees past it)
//it know that the average of the last 10 values is the baseline
//for the distance of the object (or the background) depending on its
//direction of sweep


#include <Servo.h> 
int degs, avgValue, storedAvg, oldValue, newValue, difference, scanDirection, count=0, countLimit=25, IRpin = 5, Spos=90, objectSpos, objectDistance, objectAngle; 
float volts, distance, objectAngleAvg, objectDistanceAvg;
Servo myservo;

void setup() 
{ 
  Serial.begin(9600);   
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object 
  myservo.write(90);  //center servo
  delay(15);
} 
 
 
void loop() 
{ 
    IR();
    ScanForEdge();
   // smoothObject();
   // printData();
}

void IR()
{
    volts = analogRead(IRpin)*0.0048828125;   // value from sensor
    distance = constrain(65*pow(volts, -1.10),0,200); //ignores distant values
    avgValue = (6*avgValue+distance)/7; // the  "shift" in the equation above
}

void ScanForEdge()
{
    if (distance > 2 * storedAvg)//hit an edge while turning counterclockwise
    {
      scanDirection=1;
      storedAvg = avgValue;
      objectSpos=Spos;
    }
    else if (2 * distance < storedAvg)//hit an edge while turning clockwise
    {
      objectDistance=distance;
      if (objectDistance<100)
        {degs=3;}
      else if (objectDistance<200)
        {degs=2;}
      else
        {degs=1;}
      scanDirection=-1;
      storedAvg=avgValue;
      objectAngle=Spos;
    }
    else//hit no edge
    {
      Spos += degs * scanDirection;
    }
    if (Spos > 180)  //bounce off servo limits
    {
      scanDirection = -1;
    }
    else if (Spos < 0)
    {
      scanDirection = 1;
    } 
    myservo.write(Spos);   
    delay(13); //this delay is incredibly important
              //its the ms in  the equation above
    return;
}

void smoothObject()
{
    objectAngleAvg= (3*objectAngleAvg + objectAngle)/4;
    objectDistanceAvg=(6*objectDistanceAvg+objectDistance)/7;
    return;
}

void printData()//this adds delay, so try not to use it
{
  Serial.print("A:");
  Serial.print(objectAngleAvg);
  Serial.print("D:");
  Serial.println(objectDistanceAvg);
  return; 
}
