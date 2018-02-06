/*  Connects to the home WiFi network
 *  Asks some network parameters
 *  Starts WiFi server with fix IP and listens
 *  Receives and sends messages to the client
 *  Communicates: wifi_client_01.ino
 */
#include <Thread.h>
#include <ThreadController.h>

#include <SPI.h>
#include <ESP8266WiFi.h>

char ssid[] = "vijay";               // SSID of your home WiFi
char pass[] = "Vijay123";               // password of your home WiFi
WiFiServer server(80);                    

IPAddress ip(10,10,10,100);            // IP address of the server
IPAddress gateway(10,10,10,1);           // gateway of your network
IPAddress subnet(255,255,255,0);          // subnet mask of your network

// ThreadController that will controll all threads
ThreadController thread_controll = ThreadController();

//My Thread (as a pointer)
Thread* server_thread = new Thread();

void printWIFI(){
  Serial.println("Connected to wifi");
  Serial.print("Status: "); Serial.println(WiFi.status());  // some parameters from the network
  Serial.print("IP: ");     Serial.println(WiFi.localIP());
  Serial.print("Subnet: "); Serial.println(WiFi.subnetMask());
  Serial.print("Gateway: "); Serial.println(WiFi.gatewayIP());
  Serial.print("SSID: "); Serial.println(WiFi.SSID());
  Serial.print("Signal: "); Serial.println(WiFi.RSSI());
  Serial.print("Networks: "); Serial.println(WiFi.scanNetworks());
}

void serverHandler(){
  WiFiClient client = server.available();
  if (client) {
    if (client.connected()) {
      String request = client.readStringUntil('\r');    // receives the message from the client
      Serial.print("From client: "); Serial.println(request);
      client.flush();
      client.println("Hello" + request);
      client.println("\r"); // sends the answer to the client
    }
    client.stop();                // tarminates the connection with the client
  }  
}

void setup() {
  Serial.begin(9600);                   // only for debug
  WiFi.config(ip, gateway, subnet);       // forces to use the fix IP
  Serial.println("connecting to Router..");
  WiFi.begin(ssid, pass);                 // connects to the WiFi router
  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("connecting to Router...");
    delay(500);
  }
  Serial.println("connected to Router.");
  server.begin();                         // starts the server
  printWIFI();

  server_thread->onRun(serverHandler);
  server_thread->setInterval(500);

  thread_controll.add(server_thread);
}
void loop () {

    // run ThreadController
  // this will check every thread inside ThreadController,
  // if it should run. If yes, he will run it;
  thread_controll.run();

  // Rest of code

}
