// this code grabs physical left edges in front of a SHARP long range ir sensor + servo combo
// and follows the edge around the environment.
// We learned from caibration that there is this relationship:
//data blur (in degrees) = Shift
//milliseconds delay = ms
//Shift = -0.0054571*ms^3 + 0.27204*ms^2 - 4.7537*ms + 34.688
//this is why you will see a moving avg of 10 and a ms delay of 9
//the moving average tries to keep track of enough previous values
//to that when it sees "Hey! I found an edge!" (when in fact it is pointing 10 degrees past it)
//it know that the average of the last 10 values is the baseline
//for the distance of the object (or the background) depending on its
//direction of sweep


#include <Servo.h> 
int mode=0, E=0, avgValue, storedAvg, oldValue, newValue, difference, scanDirection=1, count=0, countLimit=25, IRpin = 5, Spos=90, objectSpos, objectDistance, objectAngle; 
float volts, distance, objectAngleAvg, objectDistanceAvg;
Servo myservo;

void setup() 
{ 
  //Serial.begin(9600);   
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object 
  myservo.write(0);  //center servo
  delay(15);
} 
 
 
void loop() 
{  
  //mode -1 means looking for left edge only
  //mode 0 means looking for both edge types
  //mode 1 means looking for right edge only
  //scanDirection 1 means scan right
  //scanDirection -1 means scan left
  //edge 1 means approching edge
  //edge -1 means receding edge
  
  //probe, sweep, probe, sweep
  //probe, sweep direction, if seroLimit (direction , seach mode), if edge (edge type + direction + seach mode = direction, search mode), probe, sweep.
    //Serial.println("::");
    IR();
    Sweep();
    E = Edge();
    if (scanDirection == 1) // clockwise
    {
      //Serial.print("Clockwise");
      if (mode == 0) //normal scan mode
      {
        //Serial.println(" normal mode");
        if (E == 1) // approching edge
        {
          //Serial.println(" with a left edge");
          scanDirection = -1;
        }
        else if (E == -1) //receding edge
        {
          //Serial.println(" with a right edge");
          scanDirection = -1;
          mode = -1;
        }
      }
      else if (mode == -1)
      {
        //Serial.println(" left only mode");
        if (E == 1) //approching edge
        {
          //Serial.println(" with a left edge");
          scanDirection = -1;
          mode = 0;
        }
      }
    }
    else if (scanDirection == -1)
    //Serial.print("Counter Clockwise");
    {
      if (mode ==0)
      {
      //  Serial.println(" normal mode");
        if (E == 1)
        {
        //  Serial.println(" with a right edge");
          scanDirection = 1;
          mode = -1;
        }
        else if (E == -1)
        {
          //Serial.println(" with a left edge");
          scanDirection = 1;
        }
      }
      else if (mode == -1)
      {
        //Serial.println(" left only mode");
        if (E == -1)
        {
          //Serial.println(" with a left  edge");
          scanDirection = 1;
          mode = 0;
        }
      }
    }
}

void IR()
{
    volts = analogRead(IRpin)*0.0048828125;   // value from sensor
    distance = constrain(65*pow(volts, -1.10),0,200); //ignores distant values
    avgValue = (9*avgValue+distance)/10; // the 10 here is "shift" in the equation above
}

int Edge()
{
    //returns -1 if receding edge, 0 if no edge, and 1 if approching edge 
    E=0;
    if(distance > 2 * storedAvg)//hit a receding edge
    {
      storedAvg = avgValue;
      return -1;
    }
    else if (2 * distance < storedAvg)//hit an approching edge
    {
      storedAvg = avgValue;
      return 1;
    }
    else//hit no edge
    {
      return 0;
    }
}

void Sweep()
{
    if (Spos > 180)  //bounce off servo limits
    {
      scanDirection = -1;
      mode = 0;
    }
    else if (Spos < 0)
    {
      scanDirection = 1;
      mode = 0;
    }  
    Spos += scanDirection;
    myservo.write(Spos);   
    delay(9); //this delay is incredibly important, its the ms in  the equation above
}

