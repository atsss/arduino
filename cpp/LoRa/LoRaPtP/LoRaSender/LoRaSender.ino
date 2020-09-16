#include <SPI.h>
#include <LoRa.h>

//TTGO ESP32 LoRa connections
#define SS      18   // GPIO18 -- SX1278's CS
#define RST     14   // GPIO14 -- SX1278's RESET
#define DI0     26   // GPIO26 -- SX1278's IRQ(Interrupt Request)

int counter = 0;

void setup() {
  Serial.begin(115200);

  Serial.println("LoRa Sender");
  LoRa.setPins(SS, RST, DI0);

  //For frequencies see:
  //https://www.thethingsnetwork.org/docs/lorawan/frequency-plans.html

  if (!LoRa.begin(904300000)) {     //Americas (ch3)
    //  if (!LoRa.begin(868300000)) {   //Europe
    Serial.println("Starting LoRa failed!");
    while (1);
  }
}

void loop() {
  Serial.print("Sending packet: ");
  Serial.println(counter);
  // send packet
  LoRa.beginPacket();
  LoRa.print("hello ");
  LoRa.print(counter);
  LoRa.endPacket();
  counter++;
  delay(5000);
}
