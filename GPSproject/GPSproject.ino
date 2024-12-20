#include "SoftwareSerial.h"// import the serial library
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <TinyGPSPlus.h>
#include <SoftwareSerial.h>
#include <SD.h>
#include <SPI.h>
 
SoftwareSerial mySerial(0, 1); // RX, TX
TinyGPSPlus gps;
SoftwareSerial gpsSerial(7, 8);
Adafruit_BNO055 bno = Adafruit_BNO055();
sensors_event_t event;
const int chipSelect = BUILTIN_SDCARD;

int count = 0;
float accelX = -1; float accelY = 0; float accelZ = 1;
float gyroX = -1; float gyroY = -1; float gyroZ = -1;
float magX = -1; float magY = -1; float magZ = -1;
float lng = -1; float lat = -1; float alt = -1;
float month = -1; float day = -1; float year = -1;
float hour = -1; float minute = -1; float sec = -1;
float sat = -1;

void setup() 
{
  Serial.begin(115200);
  Serial.println("Initializing");
  // put your setup code here, to run once:
  mySerial.begin(9600);
  gpsSerial.begin(9600);
  if (!bno.begin()) {
    Serial.println("Couldn't find the BNO055 sensor!");
  }
  else {
    Serial.println("BNO055 Sensor Initialized!");
  }
  if (!SD.begin(chipSelect)) {
    Serial.println("SD Card failed, or not present");
  }
  else {
    Serial.println("SD Card Initialized!");
  }
  bno.setExtCrystalUse(true);

  File dataFile = SD.open("datalog.csv", FILE_WRITE);

  // if the file is available, write to it:
  if (dataFile) {
    dataFile.print("Date"); dataFile.print(","); dataFile.print("Time"); dataFile.print(","); 
    dataFile.print("X Acceleration (m/s²)"); dataFile.print(","); dataFile.print("Y Acceleration (m/s²)"); dataFile.print(","); dataFile.print("Z Acceleration (m/s²)"); dataFile.print(",");
    dataFile.print("X Angular Velocity (rad/s)"); dataFile.print(","); dataFile.print("Y Angular Velocity (rad/s)"); dataFile.print(","); dataFile.print("Z Angular Velocity (rad/s)"); dataFile.print(",");
    dataFile.print("X Magnetic Field (µT)"); dataFile.print(","); dataFile.print("Y Magnetic Field (µT)"); dataFile.print(","); dataFile.print("Z Magnetic Field (µT)"); dataFile.print(",");
    dataFile.print("Latitude"); dataFile.print(","); dataFile.print("Longitude"); dataFile.print(","); dataFile.print("Altitude"); dataFile.print(","); dataFile.println("Satellites");
    dataFile.close();
  } else {
    // if the file isn't open, pop up an error:
    Serial.println("Error opening datalog.csv");
  }
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
  sprintf(str, "%0.6f", x);
  for(int i = 0; i < (size + 1); i++){
    Serial.print(str[i]);
    mySerial.write(str[i]);
  }
  mySerial.write("\n");
  Serial.print("\n");
}

void loop() {
  // Check for data from the GPS module
  if(gpsSerial.available() > 0) {
    gps.encode(gpsSerial.read()); // Parse each character

    // Check if location data is valid
    if (gps.location.isUpdated()) {
      //Serial.print("Latitude: ");
      //Serial.println(gps.location.lat(), 6);  // Latitude with 6 decimal places
      lat = gps.location.lat();
      //Serial.println(lat);
      //Serial.print("Longitude: ");
      //Serial.println(gps.location.lng(), 6);  // Longitude with 6 decimal places
      lng = gps.location.lat();
      //Serial.println(lng);
      //Serial.print("Altitude: ");
      //Serial.println(gps.altitude.meters());
      alt = gps.altitude.meters();
      //Serial.println(alt);
      //Serial.print("Num Sat: ");
      //Serial.println(gps.satellites.value());
      sat = gps.satellites.value();
      //Serial.println(sat);
    
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

  Serial.println("S");
  mySerial.println("S");
  portPrint(sat);
  portPrint(accelX);
  portPrint(accelY);
  portPrint(accelZ);
  portPrint(gyroX);
  portPrint(gyroY);
  portPrint(gyroZ);
  portPrint(magX);
  portPrint(magY);
  portPrint(magZ);
  portPrint(lat);
  portPrint(lng);
  portPrint(alt);

  /*File dataFile = SD.open("datalog.csv", FILE_WRITE);

  // if the file is available, write to it:
  if (dataFile) {
    dataFile.print(month); dataFile.print("/"); dataFile.print(day); dataFile.print("/"); dataFile.print(year); dataFile.print(",");
    dataFile.print(hour); dataFile.print(":"); dataFile.print(minute); dataFile.print(":"); dataFile.print(sec); dataFile.print(",");
    dataFile.print(accelX); dataFile.print(","); dataFile.print(accelY); dataFile.print(","); dataFile.print(accelZ); dataFile.print(",");
    dataFile.print(gyroX); dataFile.print(","); dataFile.print(gyroY); dataFile.print(","); dataFile.print(gyroZ); dataFile.print(",");
    dataFile.print(magX); dataFile.print(","); dataFile.print(magY); dataFile.print(","); dataFile.print(magZ); dataFile.print(",");
    dataFile.print(lat); dataFile.print(","); dataFile.print(lng); dataFile.print(","); dataFile.print(alt); dataFile.print(","); dataFile.println(sat);

    dataFile.close();
  } else {
    // if the file isn't open, pop up an error:
    Serial.println("Error opening datalog.csv");
  }
  */
  }}
}

