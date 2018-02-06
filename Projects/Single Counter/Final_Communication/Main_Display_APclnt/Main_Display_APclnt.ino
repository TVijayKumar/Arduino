#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>

/* Set these to your desired credentials. */
const char *ssid = "vijay";
const char *password = "Vijay123";

ESP8266WebServer server(80);

IPAddress    apIP(10, 10, 10, 1);        // Private network address: local & gateway

IPAddress server2(10,10,10,100); 
WiFiClient client;

void handleRoot() {
  server.send(200, "text/html", "<h1>You are connected</h1>");
}

void handleServer(){
  client.connect(server2, 80);   // Connection to the server
  client.println("Hello server from MD..\r");  // sends the message to the server
  String answer = client.readStringUntil('\r');   // receives the answer from the sever
  Serial.println("MD : from server: " + answer);
  client.flush();
  delay(2000);                  // client will trigger the communication after two seconds
}

void setup(){
  delay(1000);
  Serial.begin(9600);
  Serial.println();

//Configuring Nodemcu as Access Point
  Serial.print("Configuring access point...");
  /* You can remove the password parameter if you want the AP to be open. */
  WiFi.mode(WIFI_AP_STA);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));   // subnet FF FF FF 00
  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.on("/", handleRoot);
  server.begin();
  Serial.println("HTTP server started");
  // Configure myThread
}

void loop(){
  yield();
  handleServer();
}
