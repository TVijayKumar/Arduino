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
ThreadController controll = ThreadController();

//My Thread (as a pointer)
Thread* myThread = new Thread();
//His Thread (not pointer)
Thread hisThread = Thread();

  int sv;
  bool isLocked(){
    if(0 == sv)
     return false;  
  }

  void lock(){
   sv++;
  }

  void unlock(){
   sv--;  
  }

void handleRoot() {
  server.send(200, "text/html", "<h1>You are connected</h1>");
}

// callback for myThread
void clientHandler(){
  client.connect(server2, 80);   // Connection to the server
  client.println("Hello server.\r");  // sends the message to the server
  String answer = client.readStringUntil('\r');   // receives the answer from the sever
  Serial.println("from server: " + answer);
  client.flush();
  delay(2000);                  // client will trigger the communication after two seconds

/*  if(!isLocked()){
      lock();
      val++;
      unlock();
  }*/
}

// callback for hisThread
void boringCallback(){
 /* int v;
  Serial.print("BORING...");
  if(!isLocked()){
      lock();
      v = val;
      unlock();
  }
  Serial.println(v,DEC);*/
}

void setup(){

  delay(1000);
  Serial.begin(115200);
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
  myThread->onRun(clientHandler);
  myThread->setInterval(500);

  // Configure myThread
  hisThread.onRun(boringCallback);
  hisThread.setInterval(250);

  // Adds both threads to the controller
  controll.add(myThread);
  controll.add(&hisThread); // & to pass the pointer to it
}

void loop(){
  // run ThreadController
  // this will check every thread inside ThreadController,
  // if it should run. If yes, he will run it;
  controll.run();

  // Rest of code
}
