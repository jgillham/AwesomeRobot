#include <Servo.h>

String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete
Servo R[3];
int newTheta[] = {0,0,0};
int oldTheta[] = {0,0,0};
int thetaCount = 0;
void setup() 
{
  R[0].attach(5);
  R[1].attach(6);
  R[2].attach(10);
  Serial.begin(9600);
  inputString.reserve(200);
}

void loop() 
{
  
  if (stringComplete) 
  {
    Serial.print("oldTheta: ");
    for(int i = 0; i < 3; i++)
    {
      Serial.print(oldTheta[i]);
      Serial.print(',');
    }
    Serial.println();
    Serial.print("newTheta: ");
    for(int j = 0; j < 3; j++)
    {
      Serial.print(newTheta[j]);
      Serial.print(',');
    }   
    Serial.println();
    
    for(int i = 1; i <= 180; i++)
    {
      for(int j = 0; j < 3; j++)
      {
        R[j].write(oldTheta[j] + (newTheta[j] - oldTheta[j])*i/180);
      }
      delay(15);
    }
    for(int i = 0; i < 3; i++)
    {
      oldTheta[i] = newTheta[i];
    }
    delay(15);
    Serial.println("done");
    stringComplete = false;
  }
}

void serialEvent() 
{

  while (Serial.available()) 
  {
    char inChar = (char)Serial.read(); 
    

    
    if(isDigit(inChar))
      inputString += (char)inChar;
      
      if(inChar == ',')
      {
        newTheta[thetaCount] = inputString.toInt();
        inputString = "";
        thetaCount += 1;
      }
    
    if (inChar == 'f') 
    {
       newTheta[thetaCount] = inputString.toInt();
       stringComplete = true;
       thetaCount = 0;
       inputString = "";
    } 
  }
  
}


