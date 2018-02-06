/*  Connects to the home WiFi network
 *  Asks some network parameters
 *  Starts WiFi server with fix IP and listens
 *  Receives and sends messages to the client
 *  Communicates: wifi_client_01.ino
 */
#include <ESP8266WiFi.h>
#include <LiquidCrystal.h>

const int rs = D3, en = D4, d4 = D5, d5 = D6, d6 = D7, d7 = D8;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

char ssid[] = "vijay";               // SSID of your home WiFi
char pass[] = "Vijay123";               // password of your home WiFi
WiFiServer server(80);                    

IPAddress ip(10,10,10,100);            // IP address of the server
IPAddress gateway(10,10,10,1);           // gateway of your network
IPAddress subnet(255,255,255,0);          // subnet mask of your network

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
      
void handleClients(){
  yield();
  WiFiClient client = server.available();
  if (client) {
    if (client.connected()) {
      String request = client.readStringUntil('\r');    // receives the message from the client
      Serial.print("From client: ");
      Serial.println(request);
      client.flush();
      client.print("Hello client \r");
      lcd.clear();
      lcd.write("Vijay");
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
  
}

void setup() {
  lcd.begin(16, 2);
  Serial.begin(9600);                   // only for debug
  WiFi.config(ip, gateway, subnet);     // forces to use the fix IP
  wifiConnectionCheck();
  Serial.println("connected to Router.");
  server.begin();                         // starts the server
  printWIFI();

  delay(200);
}

void loop () {
   wifiConnectionCheck();
   yield();
   handleClients();
   yield();
}
