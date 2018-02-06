#include <Thread.h>
#include <ThreadController.h>

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

int val = 0;

// ThreadController that will controll all threads
ThreadController thread_controll = ThreadController();

//My Thread (as a pointer)
//Thread *client_tid = new Thread();
Thread *client_rd_tid = new Thread();
Thread *client_wr_tid = new Thread();

void handleRoot() {
  server.send(200, "text/html", "<h1>You are connected</h1>");
}

// callback for myThread
/*void handleServer(){
  client.connect(server2, 80);   // Connection to the server
  client.println("Printer.\r");  // sends the message to the server
  client.flush();
  String answer = client.readStringUntil('\r');   // receives the answer from the sever
  Serial.println("from server: " + answer);
  delay(2000);                  // client will trigger the communication after two seconds
  //client.stop();
}
*/
void writeToServer(){
  client.connect(server2, 90);   // Connection to the server
  client.println("MainDisplay.\r");  // sends the message to the server
  client.flush();  
}

void readFromServer(){
  client.connect(server2, 80);   // Connection to the server
  String answer = client.readStringUntil('\r');   // receives the answer from the sever
  Serial.println("from server: " + answer);
}
void setup(){

  delay(1000);
  Serial.begin(9600);
  Serial.println();
  Serial.print("Configuring access point...");
  /* You can remove the password parameter if you want the AP to be open. */
  WiFi.mode(WIFI_AP_STA);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));   // subnet FF FF FF 00
//  WiFi.softAP("TardisTime");

  WiFi.softAP(ssid, password);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.on("/", handleRoot);
  server.begin();
  Serial.println("HTTP server started");

  // Configure myThread
  //client_tid -> onRun(handleServer);
  //client_tid -> setInterval(500);
  
  client_wr_tid -> onRun(writeToServer);
  client_wr_tid -> setInterval(500);
  thread_controll.add(client_wr_tid);

  client_rd_tid -> onRun(readFromServer);
  client_rd_tid -> setInterval(500);
  thread_controll.add(client_rd_tid);
}

void loop(){
  // run ThreadController
  // this will check every thread inside ThreadController,
  // if it should run. If yes, he will run it;
  handleRoot();
  thread_controll.run();
  // Rest of code
}
