#include <DHT.h>

#define DHTPIN 2       // Define the pin connected to DHT11 data pin
#define DHTTYPE DHT22  // Set the type of DHT sensor

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600); // Initialize serial communication
  dht.begin();        // Initialize the DHT sensor
}

void loop() {
  // Read temperature and humidity from the DHT sensor
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();


  delay(2000); // Wait for a few seconds before reading again

  // Print the values to the serial monitor
 // Serial.print("Temperature: ");
  Serial.println(temperature);

  delay(2000); // Wait for a few seconds before reading again
}
