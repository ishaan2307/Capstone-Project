#include <Wire.h>
#include "MAX30105.h" // Example library for MAX30102, adjust as needed

MAX30105 particleSensor;

void setup()
{
  Serial.begin(9600);
  Serial.println("Initializing...");
  
  // Initialize I2C communication
  Wire.begin();
  
  // Initialize the MAX30102 sensor
  if (!particleSensor.begin(Wire, I2C_ADDRESS)) // I2C_ADDRESS is the sensor's I2C address
  {
    Serial.println("Sensor not found!");
    while (1);
  }
  
  // Configure sensor settings
  particleSensor.setup();
  
  // Start measurement
  particleSensor.start();
  
  Serial.println("Initialization complete.");
}

void loop()
{
  // Read sensor data
  if (particleSensor.available())
  {
    float heartRate = particleSensor.getHeartRate();
    float spo2 = particleSensor.getSpO2();
    
    Serial.print("Heart Rate: ");
    Serial.println(heartRate);
    
    Serial.print("SpO2: ");
    Serial.println(spo2);
  }
  
  // Add appropriate delay or sleep here if needed
}
