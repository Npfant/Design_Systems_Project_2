#include "SoftwareSerial.h"// import the serial library
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <TinyGPSPlus.h>
 
SoftwareSerial mySerial(0, 1); // RX, TX
TinyGPSPlus gps;
SoftwareSerial gpsSerial(15, 14);
Adafruit_BNO055 bno = Adafruit_BNO055();
sensors_event_t event;

float accelX = -1; float accelY = 0; float accelZ = -1;
float gyroX = -1; float gyroY = -1; float gyroZ = -1;
float magX = -1; float magY = -1; float magZ = -1;
float lng = -1; float lat = -1;
float month = -1; float day = -1; float year = -1;
float hour = -1; float minute = -1; float sec = -1;

void setup() 
{
  Serial.begin(115200);
  Serial.println("Initializing");
  // put your setup code here, to run once:
  mySerial.begin(115200);
  gpsSerial.begin(115200);
  if (!bno.begin()) {
    Serial.print("Couldn't find the BNO055 sensor!");
  }
  else {
    Serial.println("BNO055 Sensor Initialized!");
  }
  bno.setExtCrystalUse(true);
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

void portPrint(float x){
  int size = lenHelper(x);
  char str[size];
  sprintf(str, "%0.4f", x);
  for(int i = 0; i < (size + 1); i++){
    Serial.print(str[i]);
    mySerial.write(str[i]);
  }
  mySerial.write("\n");
  Serial.print("\n");
}
 
void loop() 
{
  // put your main code here, to run repeatedly:
  if(bno.begin()){
    bno.getEvent(&event, Adafruit_BNO055::VECTOR_ACCELEROMETER);
    accelX = event.acceleration.x;
    accelY = event.acceleration.y;
    accelZ = event.acceleration.z;

    // Read gyroscope (angular velocity) data
    bno.getEvent(&event, Adafruit_BNO055::VECTOR_GYROSCOPE);
    gyroX = event.gyro.x;
    gyroY = event.gyro.y;
    gyroZ = event.gyro.z;

    // Read magnetometer data
    bno.getEvent(&event, Adafruit_BNO055::VECTOR_MAGNETOMETER);
    magX = event.magnetic.x;
    magY = event.magnetic.y;
    magZ = event.magnetic.z;

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
  }

  if (gpsSerial.available() > 0) {
    gps.encode(gpsSerial.read()); // Parse each character

      // Check if location data is valid
    if (gps.location.isUpdated()) {
      Serial.print("Latitude: ");
      lat = gps.location.lat();
      Serial.println(lat, 6);  // Latitude with 6 decimal places
      Serial.print("Longitude: ");
      lng = gps.location.lng();
      Serial.println(lng, 6);  // Longitude with 6 decimal places
    }

      // Check if date and time data is valid
    if (gps.date.isUpdated() && gps.time.isUpdated()) {
      Serial.print("Date: ");
      month = gps.date.month();
      Serial.print(month);
      Serial.print("/");
      day = gps.date.day();
      Serial.print(day);
      Serial.print("/");
      year = gps.date.year();
      Serial.println(year);

      Serial.print("Time: ");
      hour = gps.time.hour();
      Serial.print(hour);
      Serial.print(":");
      minute = gps.time.minute();
      Serial.print(minute);
      Serial.print(":");
      sec = gps.time.second();
      Serial.println(sec);
    }
  }

  Serial.println("Start");
  portPrint(accelX);
  portPrint(accelY);
  //portPrint(accelZ);
  //portPrint(gyroX);
  //portPrint(gyroY);
  //portPrint(gyroZ);
  //portPrint(magX);
  //portPrint(magY);
  //portPrint(magZ);
  //portPrint(lat);
  //portPrint(lng);
  Serial.println("End");

  delay(100);// prepare for next data ...
}