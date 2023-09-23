#include <Wire.h>
#include <MAX30205.h> // Example library for MAX30205, adjust as needed

MAX30205 temperatureSensor;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  
  // Initialize the MAX30205 sensor
  if (!temperatureSensor.begin()) {
    Serial.println("Sensor not found!");
    while (1);
  }
  
  Serial.println("Sensor initialized.");
}

void loop() {
  // Read temperature from the sensor
  float temperature = temperatureSensor.readTemperature();
  
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");
  
  delay(1000); // Delay between readings
}
