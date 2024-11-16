#include <TinyGPSPlus.h>
#include <SoftwareSerial.h>

// Create TinyGPSPlus and SoftwareSerial objects
TinyGPSPlus gps;
SoftwareSerial gpsSerial(4, 3);  // RX, TX (adjust pins if needed)

void setup() {
  Serial.begin(9600);            // Serial monitor baud rate
  gpsSerial.begin(9600);          // GPS module baud rate
  Serial.println("GPS Start...");
}

void loop() {
  // Check for data from the GPS module
  while (gpsSerial.available() > 0) {
    gps.encode(gpsSerial.read()); // Parse each character

    // Check if location data is valid
    if (gps.location.isUpdated()) {
      Serial.print("Latitude: ");
      Serial.println(gps.location.lat(), 6);  // Latitude with 6 decimal places
      Serial.print("Longitude: ");
      Serial.println(gps.location.lng(), 6);  // Longitude with 6 decimal places
    }

    // Check if date and time data is valid
    if (gps.date.isUpdated() && gps.time.isUpdated()) {
      Serial.print("Date: ");
      Serial.print(gps.date.month());
      Serial.print("/");
      Serial.print(gps.date.day());
      Serial.print("/");
      Serial.println(gps.date.year());

      Serial.print("Time: ");
      Serial.print(gps.time.hour());
      Serial.print(":");
      Serial.print(gps.time.minute());
      Serial.print(":");
      Serial.println(gps.time.second());
    }
  }
}

