/*  Connects to the home WiFi network
 *  Asks some network parameters
 *  Sends and receives message from the server in every 2 seconds
 *  Communicates: wifi_server_01.ino
 */ 
#include <Thread.h>
#include <ThreadController.h>

#include <SPI.h>
#include <ESP8266WiFi.h>

int sw = D5;  //button to print tocken
 
char ssid[] = "vijay";           // SSID of your home WiFi
char pass[] = "Vijay123";            // password of your home WiFi


IPAddress ip(10,10,10,101);            // IP address of the server
IPAddress gateway(10,10,10,1);           // gateway of your network
IPAddress subnet(255,255,255,0);          // subnet mask of your network

IPAddress server(10,10,10,100);       // the fix IP address of the server
WiFiClient client;

// ThreadController that will controll all threads
ThreadController thread_controll = ThreadController();

//My Thread (as a pointer)
Thread* client_thread = new Thread();
//His Thread (not pointer)
Thread* printer_thread = new Thread();

static int tocken_num=0;

void printerHandler(){
  if(!digitalRead(sw)){
    while(!digitalRead(sw));
    delay(300);
    while(!digitalRead(sw));
    tocken_num++;
    Serial.println("Printer Tocken to send : " + String(tocken_num));
  }
}
void clientHandler(){
  client.connect(server, 80);   // Connection to the server
  client.println("#" + String(tocken_num) + "*" + "\r");  // sends the message to 
  String answer = client.readStringUntil('\r');   // receives the answer from the sever
  Serial.println("from server: " + answer);
  client.flush();
  delay(2000);                  // client will trigger the communication after two seconds  
  yield();
}

void setup() {
  pinMode(sw,INPUT);
  Serial.begin(9600);               // only for debug
  WiFi.config(ip, gateway, subnet);       // forces to use the fix IP
  WiFi.begin(ssid, pass);             // connects to the WiFi router
  while (WiFi.status() != WL_CONNECTED) {
  Serial.println("Connecting to wifi");
  delay(500);
  }
  Serial.println("Connected to wifi");
  Serial.print("Status: "); Serial.println(WiFi.status());    // Network parameters
  Serial.print("IP: ");     Serial.println(WiFi.localIP());
  Serial.print("Subnet: "); Serial.println(WiFi.subnetMask());
  Serial.print("Gateway: "); Serial.println(WiFi.gatewayIP());
  Serial.print("SSID: "); Serial.println(WiFi.SSID());
  Serial.print("Signal: "); Serial.println(WiFi.RSSI());

  client_thread->onRun(clientHandler);
  printer_thread->onRun(printerHandler);
  
  client_thread->setInterval(500);
  printer_thread->setInterval(250);

  thread_controll.add(client_thread);
  thread_controll.add(printer_thread);
}

void loop () {
  thread_controll.run(); 
  yield();
}
