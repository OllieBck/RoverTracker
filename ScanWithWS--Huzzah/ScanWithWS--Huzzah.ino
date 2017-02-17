/*
This example  prints the WiFi shield's MAC address, and
 scans for available WiFi networks using the WiFi shield.
 Every ten seconds, it scans again. It doesn't actually
 connect to any network, so no encryption scheme is specified.

 Circuit:
 * WiFi shield attached

 created 13 July 2010
 by dlf (Metodo2 srl)
 modified 21 Junn 2012
 by Tom Igoe and Jaymes Dec

 This adds the Websocket support for ESP8266 found here: https://github.com/Links2004/arduinoWebSockets
 */


#include <SPI.h>
#include <ESP8266WiFi.h>
#include <Arduino.h>
#include <ESP8266WiFiMulti.h>
#include <WebSocketsClient.h>
#include <Hash.h>
#include "config.h"  //--- this is a file to hanle the wifi settings

ESP8266WiFiMulti WiFiMulti;
WebSocketsClient webSocket;

void setup() { 
  //Initialize serial and wait for port to open:
  Serial.begin(115200);
  while (!Serial) {
    // wait for serial port to connect. Needed for native USB port only
  }

  WiFiMulti.addAP(ssid, pass);

   while (WiFiMulti.run() != WL_CONNECTED) {
    delay(100);
  }

  // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue:
    while (true);
  }

  webSocket.begin("192.168.1.3", 8080); // this needs to be the same IP address and port of the server
  webSocket.onEvent(webSocketEvent);


  // scan for existing networks:
  Serial.println("Scanning available networks...");
  listNetworks(); // this function list outs the wifi networks once in step
}

void loop() {
  delay(10000); // ten secon delay
  // scan for existing networks:
  listNetworks(); // this lists ou the wifi networks continously
  webSocket.loop(); // maintains the Websocket connection
  //webSocket.sendTXT("here"); // this sends out a sample message of "here"
}

void listNetworks() {
  Serial.print("Scanning for available networks:");
  int numSsid = WiFi.scanNetworks(); // gets a list of all networks used to itterate through array
  int mySignals[numSsid]; // creates an array of the size of number of networks
  String myNames[numSsid];
  if (numSsid == -1)  {
    Serial.println("Couldn't get a wifi connection");
    return;     // return to the main loop
  }
  // print the number of available networks:
    Serial.println(numSsid);
  // print the network number and name for each network found:
  for (int thisNet = 0; thisNet < numSsid; thisNet++) {
    String signalStrength = String(WiFi.RSSI(thisNet));
    int value = signalStrength.toInt(); // take the string value and turn it into an int
    String names = WiFi.SSID(thisNet);
    mySignals[thisNet] = value; // goes through the networks and assigns values to them
    myNames[thisNet] = names; // gives each network its name
   /*
    Serial.print("signal: ");
    Serial.println(signalStrength);
    Serial.print(" value: ");
    Serial.println(value);
   */
  }
  // this cycles through the array to test for the strongest signal
  int maxVal = mySignals[0]; // first it sets the maxVal variable to the first network signal in array
  String bigName = myNames[0]; // sets the name of that array as the first value in array

  for (int i = 1; i < numSsid; i++) {
    if (mySignals[i] > maxVal) { // check to see if the current signal strength in the array is larger than maxVal
      maxVal = mySignals[i]; // if the current array item in list is larger, it assigns that value to maxVal
      bigName = myNames[i]; // and gets its name
    }
  }
  //these print out the maxVal
    Serial.print("Max Value: ");
    Serial.print(maxVal);
    Serial.print(" Name: ");
    Serial.println(bigName);
    webSocket.sendTXT(bigName);
}


void webSocketEvent(WStype_t type, uint8_t * payload, size_t lenght) {

  switch (type) {
    case WStype_DISCONNECTED:
      Serial.println("[WSc] Disconnected!\n");
      break;
    case WStype_CONNECTED: // if websocket connects, this fires
      {
        Serial.print("[WSc] Connected to url: %s\n");
        Serial.println("ESP Connected"); //((char*)payload);

        // send message to server when Connected
        webSocket.sendTXT("light on");
      }
      break;
    case WStype_TEXT: // if the server sends something this function handles it
      Serial.print("received: ");
      Serial.println((char*)payload);
      if (strcmp((char*)payload, "connected") == 0) {
        digitalWrite(5, HIGH);
      }
      if (strcmp((char*)payload, "light off") == 0) {
        digitalWrite(5, LOW);
      }
      break;
    case WStype_BIN: // this is if we are working with binary numbers
      Serial.printf("[WSc] get binary lenght: %u\n", lenght);
      break;
  }

}

