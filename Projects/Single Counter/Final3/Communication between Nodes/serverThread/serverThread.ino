/*  Connects to the home WiFi network
 *  Asks some network parameters
 *  Starts WiFi server with fix IP and listens
 *  Receives and sends messages to the client
 *  Communicates: wifi_client_01.ino
 */
#include <ESP8266WiFi.h>
#include <LiquidCrystal.h>

#include <Thread.h>
#include <ThreadController.h>

const int rs = D3, en = D4, d4 = D5, d5 = D6, d6 = D7, d7 = D8;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

char ssid[] = "vijay";               // SSID of your home WiFi
char pass[] = "Vijay123";               // password of your home WiFi
WiFiServer server1(80);                    
WiFiServer server2(90);                    

IPAddress ip(10,10,10,100);            // IP address of the server
IPAddress gateway(10,10,10,1);           // gateway of your network
IPAddress subnet(255,255,255,0);          // subnet mask of your network

// ThreadController that will controll all threads
ThreadController thread_controll = ThreadController();

//My Thread (as a pointer)
//Thread *server_tid = new Thread();
Thread *server_rd_tid = new Thread();
Thread *server_wr_tid = new Thread();

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
      
/*void handleClients(){
  wifiConnectionCheck();
  yield();
  WiFiClient client = server.available();
  if (client) {
    if (client.connected()) {
      String request = client.readStringUntil('\r');    // receives the message from the client
      Serial.print("From client: ");
      Serial.println(request);
      client.print("Hellow " + request);
      client.println("\r");
      client.flush();
    }
    client.stop();                // tarminates the connection with the client
  }  
}*/

void writeToClients(){
  wifiConnectionCheck();
  yield();
  WiFiClient client = server1.available();
  if (client) {
    if (client.connected()) {
      client.print("Hellow client");
      client.println("\r");
      client.flush();
    }
    client.stop();                // tarminates the connection with the client
  }  
}

void readFromClients(){
  wifiConnectionCheck();
  yield();
  WiFiClient client = server2.available();
  if (client) {
    if (client.connected()) {
      String request = client.readStringUntil('\r');    // receives the message from the client
      Serial.print("From client: ");
      Serial.println(request);
    }
    client.stop();                // tarminates the connection with the client
  }
}

void wifiConnectionCheck(){

  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("connecting to Router...");
    lcd.clear();
    lcd.write("connecting to");
    lcd.setCursor(2,1);
    lcd.write("Router...");
    delay(400);
  }  
  lcd.clear();
  lcd.write("cnctd 2 Router");
}

void setup() {
  lcd.begin(16, 2);
  Serial.begin(9600);                   // only for debug
  WiFi.config(ip, gateway, subnet);     // forces to use the fix IP

  wifiConnectionCheck();
  Serial.println("connected to Router.");

//  server.begin();                         // starts the server
  server1.begin();                         // starts the server
  server2.begin();                         // starts the server
  printWIFI();
  
//  server_tid -> onRun(handleClients);
//  server_tid -> setInterval(500);
//  thread_controll.add(server_tid);
  server_rd_tid -> onRun(readFromClients);
  server_rd_tid -> setInterval(500);
  thread_controll.add(server_rd_tid);
  
  server_wr_tid -> onRun(writeToClients);
  server_wr_tid -> setInterval(500);
  thread_controll.add(server_wr_tid);
  
  delay(200);
}

void loop () {
  thread_controll.run();
}

