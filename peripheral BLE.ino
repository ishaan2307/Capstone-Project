#include <Adafruit_BluefruitLE_SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_MAX30205.h>
#include <Adafruit_MAX3010x.h>

#define MAX30205_SENSOR_ADDRESS 0x49  // MAX30205 I2C address
#define MAX30102_I2C_ADDRESS 0x57     // MAX30102 I2C address

Adafruit_BluefruitLE_SPI ble;
Adafruit_MAX30205 max30205 = Adafruit_MAX30205(MAX30205_SENSOR_ADDRESS);
Adafruit_MAX3010X max30102 = Adafruit_MAX3010X(MAX30102_I2C_ADDRESS);

BLEService temperatureService("1809");  // BLE temperature service UUID
BLECharacteristic temperatureCharacteristic("2A1C", BLERead | BLENotify, 2); // BLE temperature characteristic UUID

BLEService pulseOximeterService("180D");  // BLE pulse oximeter service UUID
BLECharacteristic oxygenCharacteristic("2A5E", BLERead | BLENotify, 2); // BLE oxygen characteristic UUID
BLECharacteristic heartRateCharacteristic("2A37", BLERead | BLENotify, 2); // BLE heart rate characteristic UUID

void setup() {
  Serial.begin(115200);

  if (!ble.begin(VERBOSE_MODE)) {
    while (1);
  }

  ble.echo(false);

  // Initialize the MAX30205 temperature sensor
  if (!max30205.begin()) {
    Serial.println("Could not find a valid MAX30205 sensor, check wiring!");
    while (1);
  }

  // Initialize the MAX30102 pulse oximeter sensor
  if (!max30102.begin(Wire, I2C_SPEED_FAST)) {
    Serial.println("Could not find a valid MAX30102 sensor, check wiring!");
    while (1);
  }

  ble.setLocalName("FloraPeripheral");
  ble.setDeviceName("FloraPeripheral");

  ble.beginAdvertising();
}

void loop() {
  // Read temperature data from MAX30205
  float temperature = max30205.readTemperature();
  uint16_t temperatureData = static_cast<uint16_t>(temperature * 100);

  // Update the temperature characteristic
  temperatureCharacteristic.writeValue(temperatureData);

  // Read pulse oximeter data from MAX30102
  float oxygenLevel = max30102.getSpO2();
  uint16_t oxygenData = static_cast<uint16_t>(oxygenLevel * 100);
  int heartRate = max30102.getHeartRate();
  uint16_t heartRateData = static_cast<uint16_t>(heartRate);

  // Update oxygen and heart rate characteristics
  oxygenCharacteristic.writeValue(oxygenData);
  heartRateCharacteristic.writeValue(heartRateData);

  // Delay for a while before updating again
  delay(1000);
}
