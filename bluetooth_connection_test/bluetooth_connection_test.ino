#include "SoftwareSerial.h"// import the serial library
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
 
SoftwareSerial mySerial(0, 1); // RX, TX
Adafruit_BNO055 bno = Adafruit_BNO055();
sensors_event_t event;
int data = 10000;

void setup() 
{
  Serial.begin(115200);
  Serial.println("Initializing");
  // put your setup code here, to run once:
  mySerial.begin(115200);
  if (!bno.begin()) {
    Serial.print("Couldn't find the BNO055 sensor!");
    while (1);
  }
  else {
    Serial.println("BNO055 Sensor Initialized!");
  }
  bno.setExtCrystalUse(true);
}
 
void loop() 
{
  // put your main code here, to run repeatedly:
  bno.getEvent(&event, Adafruit_BNO055::VECTOR_ACCELEROMETER);
  float accelX = event.acceleration.x;
  float accelY = event.acceleration.y;
  float accelZ = event.acceleration.z;

  // Read gyroscope (angular velocity) data
  bno.getEvent(&event, Adafruit_BNO055::VECTOR_GYROSCOPE);
  float gyroX = event.gyro.x;
  float gyroY = event.gyro.y;
  float gyroZ = event.gyro.z;

  // Read magnetometer data
  bno.getEvent(&event, Adafruit_BNO055::VECTOR_MAGNETOMETER);
  float magX = event.magnetic.x;
  float magY = event.magnetic.y;
  float magZ = event.magnetic.z;

  // Print the data to the Serial Monitor
  Serial.print("Acceleration (m/s²) X: ");
  Serial.print(accelX, 4);
  Serial.print(" Y: ");
  Serial.print(accelY, 4);
  Serial.print(" Z: ");
  Serial.println(accelZ, 4);

  Serial.print("Angular Velocity (rad/s) X: ");
  Serial.print(gyroX, 4);
  Serial.print(" Y: ");
  Serial.print(gyroY, 4);
  Serial.print(" Z: ");
  Serial.println(gyroZ, 4);

  Serial.print("Magnetic Field (µT) X: ");
  Serial.print(magX, 4);
  Serial.print(" Y: ");
  Serial.print(magY, 4);
  Serial.print(" Z: ");
  Serial.println(magZ, 4);

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