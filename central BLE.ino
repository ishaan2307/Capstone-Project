 #include <Adafruit_BluefruitLE_SPI.h>

Adafruit_BluefruitLE_SPI ble;

BLEClientCentral bleCentral;

BLEService temperatureService("1809");  // Service UUID for temperature data
BLECharacteristic temperatureCharacteristic("2A1C", BLERead, 2); // Characteristic UUID for temperature

BLEService pulseOximeterService("180D");  // Service UUID for pulse oximeter data
BLECharacteristic pulseOximeterCharacteristic("2A37", BLERead, 2); // Characteristic UUID for pulse oximeter

void setup() {
  Serial.begin(115200);

  if (!ble.begin(VERBOSE_MODE)) {
    while (1);
  }

  ble.echo(false);

  ble.setLocalName("FloraGPS");
  ble.setDeviceName("FloraGPS");

  ble.beginAdvertising();
}

void loop() {
  // Scan for nearby peripheral devices
  bleCentral = ble.central();

  if (bleCentral) {
    Serial.print("Connected to: ");
    Serial.println(bleCentral.address());

    // Check if the connected device has the temperature service
    if (bleCentral.hasService(temperatureService)) {
      // Read temperature data
      uint16_t temperatureData = temperatureCharacteristic.readValue();

      // Process and display temperature data
      float temperature = static_cast<float>(temperatureData) / 100.0;
      Serial.print("Temperature: ");
      Serial.println(temperature);
    }

    // Check if the connected device has the pulse oximeter service
    if (bleCentral.hasService(pulseOximeterService)) {
      // Read pulse oximeter data
      uint16_t pulseOximeterData = pulseOximeterCharacteristic.readValue();

      // Process and display pulse oximeter data
      int heartRate = static_cast<int>(pulseOximeterData);
      Serial.print("Heart Rate: ");
      Serial.println(heartRate);
    }

    // Disconnect from the peripheral
    ble.disconnect(bleCentral);

    // Delay before scanning for another peripheral
    delay(1000);
  }
}
