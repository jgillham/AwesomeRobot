/* try to impliment a send and recieve protocol
   THIS WILL BE THE TRANSMIT SIDE
   the point is to listen in a loop for a commmmand signal. the reciever side 
   will poll the transmiter by sending command signals. this signal will 
   indicate one of the three channels to read. Then the transmiter will read
   one of the channel analog inputs and then transmit it */

int chnl_1, chnl_2, chnl_3; // these will be read in from analog inputs
int command;
int bounceCount = 0;


void setup()
{
  Serial.begin(9600);
}

void loop ()
{
  // listen repeatedly 
  if ( Serial.available() > 0 )
  {
    command = Serial.read();
    
    // get an analog value depening on what
    // the transmiter is looking for
    switch ( command )
    {
      case 1: // (T)
        chnl_1 = analogRead(A0);
        chnl_1 = map(chnl_1, 90, 915, 0, 255);
        Serial.write(chnl_1);
        //Serial.println(chnl_1, DEC);
        bounceCount++;
      break;
      
      case 2: // (X)
        chnl_2 = analogRead(A1);
        chnl_2 = map(chnl_2, 50, 850, 0, 255);
        Serial.write(chnl_2);
        //Serial.println(chnl_2, DEC);
        bounceCount++;
      break;
      
      case 3: // (Y)
        chnl_3 = analogRead(A2);
        chnl_3 = map(chnl_3, 140, 920, 0, 255);
        Serial.write(chnl_3);
        //Serial.println(chnl_3, DEC);
        bounceCount++;
      break;

    }
  } // end if
  
  if(bounceCount > 100)
  {
    Serial.flush();
    bounceCount = 0;
  }
  
}
        

