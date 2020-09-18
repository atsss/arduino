/**
 * Physical to API example.
 * The Arduino asks Wolfram a question and gets an answer.
**/

#include <WiFi.h>
#define PubNub_BASE_CLIENT WiFiClient
#include <PubNub.h>
#include <ArduinoJson.h>


// Wi-Fi Credentials
char ssid[] = "Your Wifi Network Name Here";
char pass[] = "Your Wifi Password Here";

int status = WL_IDLE_STATUS;       // the Wifi radio's status

// PubNub Keys
char pubkey[] = "Your Publish Key Here";
char subkey[] = "Your Subscribe Key Here";

const static char channel[] = "wolfram"; // channel to use

// outgoing JSON variables
StaticJsonDocument<200> sending; // The JSON from the outgoing message
char msg[64]; // variable for the JSON to be serialized into for your outgoing message

// Incoming JSON Variables
StaticJsonDocument<200> doc; // JSON object for receiving the incoming values
const char* messageText;

// Circuit pins
const int buttonPin = 22;    // the number of the pushbutton pin
const int LEDPin = 23;       // the number of the LED pin

int buttonState = 0;        // variable for reading the pushbutton status
int LEDState = 0;           // variable for LED value

bool readyToReadMessage = false;
int whatTimeIsIt = 0;

void setup() {

  // Setup Serial Connection
  Serial.begin(115200);
  
  while (!Serial); //Initialize serial and wait for port to open:
  
  // attempt to connect to Wifi network:
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to the network, SSID: ");
    Serial.println(ssid);
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(10000);
  }

  // Once you are connected:
  Serial.println("You're connected to the network");

  // conecctiong to PubNub
  PubNub.begin(pubkey, subkey);
  Serial.println("PubNub set up");

  // initialize the circuit pins
  pinMode(buttonPin, INPUT);
  pinMode(LEDPin, OUTPUT);

  // Temporary fix as the first message from PubNub is not read
  // TODO: Find the issue and update this
  delay(500);
  SubscribetoPubNub(); //seems to be fixing the issue
  delay(500);

  Serial.println("Ready to Call!");
}

void loop() {
  // Checks if it should be recieving a message
   if ( readyToReadMessage == true ) {
    SubscribetoPubNub();      // receive the incoming messages from your channel
    delay(300);               // wait 300ms to avoid lag
    readyToReadMessage = false;    // message has been read, no more message to read
  }

  // Based on what time it is, set the brightness of the LED
  if (whatTimeIsIt > 13) {LEDState = map(whatTimeIsIt,0,24,0,255);}
  else {LEDState = map(whatTimeIsIt,0,24,255,0);}
  digitalWrite(LEDPin,LEDState);        // write a LED value

  buttonState = digitalRead(buttonPin); // read the state of the pushbutton value:
  
  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    sendMessage("What time is it in Toronto?");
    Serial.println("Message Sent!");
    delay(500); // wait 500ms to avoid lags
    readyToReadMessage = true;  // a message has been sent, so i'm expecting a result to be read
  }

}

void sendMessage(const char* val) {
  
  // assemble the JSON to publish
  sending["text"] = val; // sending your question to wolfram

  serializeJson(sending, msg); // serialize JSON to send - sending is the JSON object, and it is serializing it to the char msg
  
  WiFiClient* client = PubNub.publish(channel, msg); // publish the variable char 
  if (!client) {
    Serial.println("publishing error"); // if there is an error print it out 
  }
  
}

void SubscribetoPubNub() {

  String val; // String for printing out the incoming message
  
  PubSubClient* sclient = PubNub.subscribe(channel); // subscribe to the channel defined at the top of the code
  
  SubscribeCracker ritz(sclient); // This "cracker" retrieves the incoming messages and holds onto the value
  
  while (!ritz.finished()) { // when the message is retrieved
    ritz.get(val); // get the value of the message as a string 
    if (val.length() > 0) { // make sure there is a value 
      //Serial.print("Received: "); // print out the message
      //Serial.println(val); // entire string of json
      printMessage(val); // call printMessage function (this allows us to use the incoming data outside of this function)
    }
  }
  sclient->stop();
  
}

void printMessage(String v) {
  
  doc.clear(); // clearing the last message

  deserializeJson(doc, v); // parse the JSON received

  messageText = doc["answer"]; // the message that is being sent

  // print out results
  Serial.print("messageText: ");
  Serial.println(messageText);
  setLEDValue(messageText);
  
}

void setLEDValue(String codedMessage) {
  whatTimeIsIt = 0;

  // Fidning if it is pm or am
  // if it is pm, add 12 to the time
  int whereIsTheDot = codedMessage.indexOf(".");
  if ((codedMessage.charAt(whereIsTheDot-1)) == 'P') { whatTimeIsIt = 12; }

  int whereIsTheColon = codedMessage.indexOf(":");
  String hour = codedMessage.substring(whereIsTheColon-2,whereIsTheColon);
  //Serial.println(hour.toInt());
  whatTimeIsIt = whatTimeIsIt + hour.toInt();
  //Serial.println(whatTimeIsIt);
}
