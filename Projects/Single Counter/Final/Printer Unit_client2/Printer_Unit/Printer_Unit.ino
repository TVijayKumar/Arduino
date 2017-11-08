#include"PrinterVj.h"

#include <Thread.h>
#include <ThreadController.h>

#include <SPI.h>
#include <ESP8266WiFi.h>

PrinterVj printobj;
int sw = D0;  //button to print tocken
 
char ssid[] = "vijay";           // SSID of your home WiFi
char pass[] = "Vijay123";            // password of your home WiFi

IPAddress server(10,10,10,100);       // the fix IP address of the server
WiFiClient client;

// ThreadController that will controll all threads
ThreadController controll = ThreadController();

//My Thread (as a pointer)
Thread* myThread = new Thread();
//His Thread (not pointer)
Thread hisThread = Thread();

static int tocken_num=0;

void clientCallback(){
  client.connect(server, 80);   // Connection to the server
  client.println("#" + String(tocken_num) + "*" + "\r");  // sends the message to the server
  String answer = client.readStringUntil('\r');   // receives the answer from the sever
  Serial.println("from server: " + answer);
  client.flush();
  delay(2000);                  // client will trigger the communication after two seconds  
  yield();
}

void printerCallback(){
  if(false == digitalRead(sw)){
    while(false == digitalRead(sw));
    delay(100);
    while(false == digitalRead(sw));
    tocken_num++;
    printobj.printStr("Tocken : " + String(tocken_num));
    yield();
 }
 yield();
// delay(700L);
}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);               // only for debug
  WiFi.begin(ssid, pass);             // connects to the WiFi router
  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("Connecting to Router..");
    delay(500);
  }
  Serial.println("Connected to wifi");
  Serial.print("Status: "); Serial.println(WiFi.status());    // Network parameters
  Serial.print("IP: ");     Serial.println(WiFi.localIP());
  Serial.print("Subnet: "); Serial.println(WiFi.subnetMask());
  Serial.print("Gateway: "); Serial.println(WiFi.gatewayIP());
  Serial.print("SSID: "); Serial.println(WiFi.SSID());
  Serial.print("Signal: "); Serial.println(WiFi.RSSI());

  myThread->onRun(clientCallback);
  myThread->setInterval(200);

  // Configure myThread
  hisThread.onRun(printerCallback);
  hisThread.setInterval(200);

  // Adds both threads to the controller
  controll.add(myThread);
  controll.add(&hisThread); // & to pass the pointer to it

  printobj.init();
  pinMode(sw,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
   controll.run();
}
