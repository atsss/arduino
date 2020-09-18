/*******************************************************************
    Sets a custom status on your slack account using button inputs to change the text and presence.

 *  * = Affiliate
  This library and base code was written by Brian Lough found here: https://github.com/witnessmenow/arduino-slack-api/blob/master/README.md

  You will need to create a slack app with a OAuth Key, WiFi, and a WiFi enabled board.


  Look for emoji symbols here: https://www.webfx.com/tools/emoji-cheat-sheet/
 *******************************************************************/

#include <WiFi.h>
#include <WiFiClientSecure.h>

#include <ArduinoSlack.h> // Arduino Slack Library 
#include <ArduinoSlackCert.h>
#include <ArduinoJson.h> // Library used for parsing JSON from the API responses

//------- Replace the following! ------

char ssid[] = "WiFi SSID goes here";         // your network SSID (name)
char password[] = "WiFi Password goes here"; // your network password

#define SLACK_ACCESS_TOKEN "Insert your Slack Auth Key here!!" // 

//------- ---------------------- ------

int status = WL_IDLE_STATUS; // WiFi Status

WiFiClientSecure client;
ArduinoSlack slack(client, SLACK_ACCESS_TOKEN); // ArduinoSlack client
boolean testStatus = false;

unsigned long delayBetweenRequests = 30000; // Time between requests (1 minute)
unsigned long requestDueTime;               //time when request due

int button1 = 22;
int button2 = 23;

int buttonVal1;
int buttonVal2;

boolean button1on = false;
boolean button2on = true;

void setup() {

  Serial.begin(115200);

  while (!Serial); //Initialize serial and wait for port to open:

  // attempt to connect to Wifi network:
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to the network, SSID: ");
    Serial.println(ssid);
    status = WiFi.begin(ssid, password);

    // wait 10 seconds for connection:
    delay(10000);
  }
    client.setCACert(slack_server_cert);

  // once you are connected :
  Serial.println("You're connected to the network");

  pinMode(button1, INPUT);
  pinMode(button2, INPUT);


}

void loop() {

  buttonVal1 = digitalRead(button1);
  buttonVal2 = digitalRead(button2);

  SlackProfile profile;

  if (buttonVal1 == HIGH) { // when the button is pressed...
    if (!button1on) {  // if the button hasn't pressed button1on = false

      profile = slack.setCustomStatus("It is time for coffee!", ":coffee:");

      displayProfile(profile); // print out the profile information

      slack.setPresence(SLACK_PRESENCE_AWAY); // sets your presense to away
      Serial.println("Set presence to Away");

      button1on = !button1on; // set the value to true so we don't send multiple requests
      button2on = !button2on; // set the other value to false so that we know button 2 needs to be pressed next.
    }
  }

  if (buttonVal2 == HIGH) { // when the button is pressed...
    if (!button2on) {  // if the button hasn't pressed button2on = false

      profile = slack.setCustomStatus("Busy working - don't bother me!", ":wrench:");


      slack.setPresence(SLACK_PRESENCE_AUTO); // sets your presense to "here"
      Serial.println("Set presence to Auto");

      displayProfile(profile); // print out the profile information

      button2on = !button2on; // set the value to true so we don't send multiple requests
      button1on = !button1on; // set the other value to false so that we know button 1 needs to be pressed next.
    }
  }
}


void displayProfile(SlackProfile profile)
{
  if (!profile.error)
  {
    Serial.println("--------- Profile ---------");

    Serial.print("Display Name: ");
    Serial.println(profile.displayName);

    Serial.print("Status Text: ");
    Serial.println(profile.statusText);

    Serial.print("Status Emoji: ");
    Serial.println(profile.statusEmoji);

    Serial.print("Status Expiration: ");
    Serial.println(profile.statusExpiration);

    Serial.println("------------------------");
  }
  else
  {
    Serial.println("error getting profile");
  }
}
