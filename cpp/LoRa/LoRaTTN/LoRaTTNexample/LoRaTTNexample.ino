#include "LoRaStuff.h"

unsigned long futureTime;

void setup() {
  Serial.begin(115200);
  TTNsetup();
  futureTime = millis() + 1000;
}

void loop() {
  TTNupdate();
  
  if (millis() >= futureTime)
  {
    send2TTN("Hello!");
    Serial.println("Sent Hello! ");
    futureTime += 10000;
  }
}
