#include <Arduino_LSM6DS3.h>
#include <ArduinoBLE.h>

#define BLE_SENSE_UUID(val) ("6fbe1da7-" val "-44de-92c4-bb6e04fb0212")

const int VERSION = 0x00000000;

BLEService                     service                       (BLE_SENSE_UUID("0000"));
BLEUnsignedIntCharacteristic   versionCharacteristic         (BLE_SENSE_UUID("1001"), BLERead);
BLEFloatCharacteristic         accelerationXCharacteristic   (BLE_SENSE_UUID("3001"), BLERead);
BLEFloatCharacteristic         accelerationYCharacteristic   (BLE_SENSE_UUID("3002"), BLERead);
BLEFloatCharacteristic         accelerationZCharacteristic   (BLE_SENSE_UUID("3003"), BLERead);
BLEFloatCharacteristic         gyroscopeXCharacteristic      (BLE_SENSE_UUID("3011"), BLERead);
BLEFloatCharacteristic         gyroscopeYCharacteristic      (BLE_SENSE_UUID("3012"), BLERead);
BLEFloatCharacteristic         gyroscopeZCharacteristic      (BLE_SENSE_UUID("3013"), BLERead);


// String to calculate the local and device name
String name;

void setup() {
  Serial.begin(9600);

  while (!Serial);
  Serial.println("Started");

  if (!IMU.begin()) {
    Serial.println("Failled to initialized IMU!");
    while (1);
  }

  if (!BLE.begin()) {
    Serial.println("Failled to initialized BLE!");
    while (1);
  }

  String address = BLE.address();

  Serial.print("address = ");
  Serial.println(address);

  address.toUpperCase();

  name = "BLESense-";
  name += address[address.length() - 5];
  name += address[address.length() - 4];
  name += address[address.length() - 2];
  name += address[address.length() - 1];

  Serial.print("name = ");
  Serial.println(name);

  BLE.setLocalName(name.c_str());
  BLE.setDeviceName(name.c_str());
  BLE.setAdvertisedService(service);

  service.addCharacteristic(versionCharacteristic);
  service.addCharacteristic(accelerationXCharacteristic);
  service.addCharacteristic(accelerationYCharacteristic);
  service.addCharacteristic(accelerationZCharacteristic);
  service.addCharacteristic(gyroscopeXCharacteristic);
  service.addCharacteristic(gyroscopeYCharacteristic);
  service.addCharacteristic(gyroscopeZCharacteristic);

  versionCharacteristic.setValue(VERSION);

  BLE.addService(service);
  BLE.advertise();
}

void loop() {
  while (BLE.connected()) {
    float x, y, z;
    IMU.readAcceleration(x, y, z);

    accelerationXCharacteristic.writeValue(x);
    accelerationYCharacteristic.writeValue(y);
    accelerationZCharacteristic.writeValue(z);

    Serial.println("acceleration");
    Serial.print("x: "); Serial.print(x);
    Serial.print(", y: "); Serial.print(y);
    Serial.print(", z: "); Serial.println(z);

    IMU.readGyroscope(x, y, z);

    gyroscopeXCharacteristic.writeValue(x);
    gyroscopeYCharacteristic.writeValue(y);
    gyroscopeZCharacteristic.writeValue(z);

    Serial.println("gyro");
    Serial.print("x: "); Serial.print(x);
    Serial.print(", y: "); Serial.print(y);
    Serial.print(", z: "); Serial.println(z);

    // delay(500);
  }
}
