#include <Arduino_LSM6DS3.h>
#include <ArduinoBLE.h>

#define BLE_SENSE_UUID(val) ("6fbe1da7-" val "-44de-92c4-bb6e04fb0212")

const int VERSION = 0x00000000;

BLEService                     service                       (BLE_SENSE_UUID("0000"));
BLEUnsignedIntCharacteristic   versionCharacteristic         (BLE_SENSE_UUID("1001"), BLERead);
BLEUnsignedIntCharacteristic   accelerationCharacteristic    (BLE_SENSE_UUID("3001"), BLENotify); // Array of 3 floats, G


// String to calculate the local and device name
String name;

void setup() {
  Serial.begin(9600);

  while (!Serial);
  Serial.println("Started");

  if (!IMU.begin()) {
    Serial.println("Failed to initialized IMU!");
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
  service.addCharacteristic(accelerationCharacteristic);

  versionCharacteristic.setValue(VERSION);

  BLE.addService(service);
  BLE.advertise();
}

void sendAccelerationData(){
  float x, y, z;
  IMU.readAcceleration(x, y, z);
  float acceleration[3] = { x, y, z };
  unsigned int accelerationPower = sqrt(x*x + y*y + z*z) * 1000;

  if(!isnan(accelerationPower)){
    Serial.println(accelerationPower);
    accelerationCharacteristic.writeValue(accelerationPower);
  }
}

void loop() {
  while (BLE.connected()) {

    if (accelerationCharacteristic.subscribed() && IMU.accelerationAvailable()) {
      sendAccelerationData();
    }

  }
}
