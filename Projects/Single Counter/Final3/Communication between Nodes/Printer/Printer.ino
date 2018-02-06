/*  Connects to the home WiFi network
 *  Asks some network parameters
 *  Sends and receives message from the server in every 2 seconds
 *  Communicates: wifi_server_01.ino
 */ 
#include <Thread.h>
#include <ThreadController.h>

#include <SPI.h>
#include <ESP8266WiFi.h>

char ssid[] = "vijay";           // SSID of your home WiFi
char pass[] = "Vijay123";            // password of your home WiFi

IPAddress server(10,10,10,100);       // the fix IP address of the server

WiFiClient client;

// ThreadController that will controll all threads
ThreadController thread_controll = ThreadController();

//My Thread (as a pointer)
Thread *client_wr_tid = new Thread();

void wifiConnectionCheck(){
  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("connecting to Router...");
    delay(400);
  }  
}

void writeToServer(){
  client.connect(server, 90);   // Connection to the server
  client.println("Printer.\r");  // sends the message to the server
  client.flush();  
}

void setup() {
  Serial.begin(9600);               // only for debug
  WiFi.begin(ssid, pass);             // connects to the WiFi router
  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("connecting to Router...");
    delay(500);
  }
  
  Serial.println("connected to Router.");
  client_wr_tid -> onRun(writeToServer);
  client_wr_tid -> setInterval(500);
  thread_controll.add(client_wr_tid);
}

void loop(){
  // run ThreadController
  // this will check every thread inside ThreadController,
  // if it should run. If yes, he will run it;
  wifiConnectionCheck();
  thread_controll.run();

  // Rest of code
}
