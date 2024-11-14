#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>

// Create an instance of the BNO055 sensor
Adafruit_BNO055 bno = Adafruit_BNO055();

// Variable to hold sensor data
sensors_event_t event;

void setup() {
  // Start serial communication at 115200 baud
  Serial.begin(115200);
  // Initialize the BNO055 sensor
  if (!bno.begin()) {
    Serial.print("Couldn't find the BNO055 sensor!");
    while (1);
  }

  // Set the sensor mode to NDOF (Nine Degrees Of Freedom), which includes accelerometer, gyroscope, and magnetometer data
  bno.setExtCrystalUse(true);

  Serial.println("BNO055 Sensor Initialized!");
}

void loop() {
  // Read acceleration data
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

  // Add a delay to make the data easier to read
  delay(500);
}

