#include "SoftwareSerial.h"// import the serial library
 
SoftwareSerial mySerial(0, 1); // RX, TX
String data = "Test :)";
int BluetoothData;

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
  if (Serial.available())
  {
    BluetoothData = Serial.read();
    if(BluetoothData=='1')
    {   
     mySerial.write("Test 1 \n");
    }
  }
delay(100);// prepare for next data ...
}