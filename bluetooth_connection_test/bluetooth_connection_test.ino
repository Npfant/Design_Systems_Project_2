#include "SoftwareSerial.h"// import the serial library
#include <Wire.h>
 
SoftwareSerial mySerial(0, 1); // RX, TX

float x = -1;

void setup() 
{
  Serial.begin(9600);
  Serial.println("Initializing");
  // put your setup code here, to run once:
  mySerial.begin(9600);
}

float lenHelper(float x) {
    if (x >= 1000000000) return 14;
    if (x >= 100000000)  return 13;
    if (x >= 10000000)   return 12;
    if (x >= 1000000)    return 11;
    if (x >= 100000)     return 10;
    if (x >= 10000)      return 9;
    if (x >= 1000)       return 8;
    if (x >= 100)        return 7;
    if (x >= 10)         return 6;
    return 5;
}
 
void loop() 
{
  // put your main code here, to run repeatedly:
  int size = lenHelper(x);
  char str[size];
  sprintf(str, "%0.4f", x);
  for(int i = 0; i < (size + 1); i++){
    Serial.print(str[i]);
    mySerial.write(str[i]);
  }
  mySerial.write("\n");
  mySerial.write("\n");
  Serial.print("\n");

  delay(100);// prepare for next data ...
}