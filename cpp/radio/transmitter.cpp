#include <SoftwareSerial.h>             //-Build in library
SoftwareSerial transmitter(7,8,true);   //-Pin 8 transmits

const int trigPin = 9;
const int echoPin = 10;

long duration;
int distance;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  transmitter.begin(1200);
  Serial.begin(9600);
}
void loop() {
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);

  // Calculating the distance
  distance = duration*0.034/2;

  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  if (distance < 10) {
    transmitter.println(".........ON123ON123ON123"); //Message
    Serial.println("HIGH");
    delay(100);
  }
}
