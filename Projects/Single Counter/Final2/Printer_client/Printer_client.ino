#include <ESP8266WiFi.h>

char ssid[] = "vijay";           // SSID of your home WiFi
char pass[] = "Vijay123";            // password of your home WiFi

IPAddress server(10,10,10,100);       // the fix IP address of the server
WiFiClient client;

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
void handleServer(){
  client.connect(server, 80);   // Connection to the server
  client.println("Hello server from Printer.\r");  // sends the message to the server
  String answer = client.readStringUntil('\r');   // receives the answer from the sever
  Serial.println("from server: " + answer);
  client.flush();
  delay(40);                  // client will trigger the communication after two seconds  
  yield();
}


void wifiConnectionCheck(){
  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("Printer connecting to Router...");
    delay(400);
  }  
}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);               // only for debug
  WiFi.begin(ssid, pass);             // connects to the WiFi router
  wifiConnectionCheck();
  printWIFI();
}

void loop() {
  wifiConnectionCheck();
  yield();
  handleServer();
  yield();
}
