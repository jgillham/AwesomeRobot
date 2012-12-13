extern "C" void __cxa_pure_virtual() { while (1) ; }
int IRpin = 0;                                    // analog pin for reading the IR sensor

void setup() {
//  Serial.begin(115200);                             // start the serial port
}
void loop() {
  float volts = analogRead(IRpin)*0.0048828125;   // value from sensor * (5/1024) - if running 3.3.volts then change 5 to 3.3
  float distance = 65*pow(volts, -1.10);          // worked out from graph 65 = theretical distance / (1/Volts)S - luckylarry.co.uk
  int x = distance, multiplier=0;
  
  while (x > 255)
  {    x = x-255;   multiplier++;  }
  Serial.print( char(x) );
  delay(100);
  Serial.print( char(multiplier) );
  delay(100);
}
