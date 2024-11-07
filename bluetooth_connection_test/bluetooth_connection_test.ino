#include "SoftwareSerial.h"// import the serial library
 
SoftwareSerial mySerial(0, 1); // RX, TX
int data = 10000;

void setup() 
{
  Serial.begin(9600);
  Serial.println("Initializing");
  // put your setup code here, to run once:
  mySerial.begin(9600);
}
 
void loop() 
{
  // put your main code here, to run repeatedly:
  char str[5];
  sprintf(str, "%d", data);
  for(int i = 0; i < 5; i++){
    mySerial.write(str[i]);
  }
  mySerial.write("\n");
  delay(100);// prepare for next data ...
  data++;
  if(data > 19999) data = 10000;
}