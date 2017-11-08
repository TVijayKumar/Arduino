/*  Connects to the home WiFi network
 *  Asks some network parameters
 *  Sends and receives message from the server in every 2 seconds
 *  Communicates: wifi_server_01.ino
 */
#ifndef __PrinterClient__
#ifndef __PrinterClient__
 
#include <Thread.h>
#include <ThreadController.h>

#include <SPI.h>
#include <ESP8266WiFi.h>
#include "PrinterClient.h"

char ssid[] = "vijay";           // SSID of your home WiFi
char pass[] = "Vijay123";            // password of your home WiFi

unsigned long askTimer = 0;

IPAddress server(10,10,10,100);       // the fix IP address of the server
WiFiClient client;

// ThreadController that will controll all threads
ThreadController controll = ThreadController();

//My Thread (as a pointer)
Thread* myThread = new Thread();
//His Thread (not pointer)
Thread hisThread = Thread();

void PrinterClient::init(){
	
} 

void clientHandler(){
  client.connect(server, 80);   // Connection to the server
  client.println("Hello server! I am Printer\r");  // sends the message to the server
  String answer = client.readStringUntil('\r');   // receives the answer from the sever
  Serial.println("from server: " + answer);
  client.flush();
  delay(2000);                  // client will trigger the communication after two seconds  
}

void boringCallback(){
  
}

void setup() {
  Serial.begin(115200);               // only for debug
  WiFi.begin(ssid, pass);             // connects to the WiFi router
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  Serial.println("Connected to wifi");
  Serial.print("Status: "); Serial.println(WiFi.status());    // Network parameters
  Serial.print("IP: ");     Serial.println(WiFi.localIP());
  Serial.print("Subnet: "); Serial.println(WiFi.subnetMask());
  Serial.print("Gateway: "); Serial.println(WiFi.gatewayIP());
  Serial.print("SSID: "); Serial.println(WiFi.SSID());
  Serial.print("Signal: "); Serial.println(WiFi.RSSI());

  myThread->onRun(clientHandler);
  myThread->setInterval(500);

  // Configure myThread
  hisThread.onRun(boringCallback);
  hisThread.setInterval(250);

  // Adds both threads to the controller
  controll.add(myThread);
  controll.add(&hisThread); // & to pass the pointer to it

}

void loop () {
  controll.run();

}

#endif