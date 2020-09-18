/**
 * Physical to API example.
 * The Arduino asks Wolfram a question and gets an answer.
**/

#include <WiFiNINA.h>
#define PubNub_BASE_CLIENT WiFiClient
#include <PubNub.h>
#include <ArduinoJson.h>


// Wi-Fi Credentials
char ssid[] = "wifi home";
char pass[] = "lachapelle";

int status = WL_IDLE_STATUS;       // the Wifi radio's status

// Open weather map api key
WiFiClient client; 
String apiKey= "65543233ac6f545f542694d1d21b9a62";
char server[] = "api.openweathermap.org";
String location= "Tokyo,JP"; //the city you want the weather for 


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
}

void loop() {
  getWeather(); 
  delay(10000);
}

void getWeather() { 
  Serial.println("\nStarting connection to server..."); 
  // if you get a connection, report back via serial: 
  if (client.connect(server, 80)) {
    Serial.println("connected to server"); 
    // Make a HTTP request: 
    client.print("GET /data/2.5/forecast?"); 
    client.print("q="+location); 
    client.print("&appid="+apiKey); 
    client.print("&cnt=3"); 
    client.println("&units=metric"); 
    client.println("Host: api.openweathermap.org"); 
    client.println("Connection: close"); 
    client.println(); 
  }
  else { 
   Serial.println("unable to connect"); 
  }
  delay(1000);
  String line = "";
  while (client.connected()) {
    line = client.readStringUntil('\n'); 
    Serial.println(line); 
    Serial.println("parsingValues"); 
    
    // create a json buffer where to store the json data 
    StaticJsonDocument<500> doc;
    doc.clear(); // clearing the last message
    deserializeJson(doc, line); // parse the JSON received
      
    //get the data from the json tree 
    String Temperature = doc["list"][0]["main"]["temp"]; 
    String FeelsLike = doc["list"][0]["main"]["feels_like"];
    String Pressure = doc["list"][0]["main"]["pressure"];
    String Humidity = doc["list"][0]["main"]["humidity"];
    // Print values. 
    Serial.println("Temperature: " + Temperature);
    Serial.println("Feels Like: " + FeelsLike);
    Serial.println("Pressure: " + Pressure);
    Serial.println("Humidity: " + Humidity);

  } 
}
