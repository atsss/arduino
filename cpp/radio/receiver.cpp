#include <SoftwareSerial.h>           //-Extra serial

SoftwareSerial receiver(7, 8, true);  //-A serial that receives on 8 and sends at 7 (not used)
String window = "........";           //-A cue for 8 incomming characters
int outputPin = 4;

void setup() {
  Serial.begin(9600);
  pinMode(outputPin, OUTPUT);
  receiver.begin(1200);               //-Serial to talk to radio
}

void loop() {
  if (receiver.available())           //-Anything from radio?
  {
    char c = receiver.read();         //-Get it
    if (isPrintable(c))               //-We only care about printable characters
    {
      window += c;                    //-Put it at the end of the window
      window = window.substring(1);   //-Remove the character at the other end
      Serial.println(window);
      if (window.endsWith("ON123"))   //-Check for match
      {
        Serial.println("Received message!");
        digitalWrite(outputPin, HIGH);
        delay(200);
      } else {
        digitalWrite(outputPin, LOW);
      }
    }
  }
}
