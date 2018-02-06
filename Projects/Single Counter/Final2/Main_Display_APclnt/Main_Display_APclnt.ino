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

// ThreadController that will controll all threads
ThreadController controll = ThreadController();

//My Thread (as a pointer)
Thread* myThread = new Thread();
//His Thread (not pointer)
Thread hisThread = Thread();

void handleRoot() {
  server.send(200, "text/html", "<h1>You are connected</h1>");
}

#define MAX7219_DIN D1
#define MAX7219_CS  D2
#define MAX7219_CLK D3

void initialiseMax7219()
{
  digitalWrite(MAX7219_CS, HIGH);
  pinMode(MAX7219_DIN, OUTPUT);
  pinMode(MAX7219_CS, OUTPUT);
  pinMode(MAX7219_CLK, OUTPUT);

  output(0x0f, 0x00); //display test register - test mode off
  output(0x0c, 0x01); //shutdown register - normal operation
  output(0x0b, 0x07); //scan limit register - display digits 0 thru 7
  output(0x0a, 0x0f); //intensity register - max brightness
  output(0x09, 0xff); //decode mode register - CodeB decode all digits
}

void output(byte address, byte data)
{
  yield();
  digitalWrite(MAX7219_CS, LOW);
  yield();
  shiftOut(MAX7219_DIN, MAX7219_CLK, MSBFIRST, address);
  yield();
  shiftOut(MAX7219_DIN, MAX7219_CLK, MSBFIRST, data);
  yield();
  digitalWrite(MAX7219_CS, HIGH);
  yield();
}

char tocken_str[6]={'\0'};

void parseServerData(String answer){
  const char *ptr = answer.c_str();
    for(int i=0; i < answer.length(); i++){
      if(*(ptr+i) == '#' ){
        for(char i=0; i < 6 ; i++) tocken_str[i]='\0';
        for(int j=0; *(ptr+i) != '\r' ; j++){
         i++;
         if(*(ptr+i) == '*'){
             *(tocken_str+j) = '\0';
             break;
          }
          *(tocken_str+j) = *(ptr+i);
          yield();
        }
        break;
      }
    yield();
    }  
}

void handleServer(){
  client.connect(server2, 80);   // Connection to the server
  client.println("Hello server from MD..\r");  // sends the message to the server
  yield();
  String answer = client.readStringUntil('\r');   // receives the answer from the sever
  parseServerData(answer);
  Serial.println("MD : from server: " + answer);
  yield();
  client.flush();
  client.stop();                // tarminates the connection with the client
}

void displaySegment(){
  Serial.println("Tocken to Display : " + String(tocken_str) );
  if(tocken_str[0]=='\0'){
   // output(0x01, 0);
    output(0x02, 0);
    output(0x03, 0);
    yield();
  }
  else if(tocken_str[1]=='\0'){
   // output(0x01, 0);
    output(0x02, 0);
    output(0x03, tocken_str[0]-48);
    yield();
  }
  else if(tocken_str[2]=='\0'){
  //  output(0x01, 0);
    output(0x02, tocken_str[0]-48);
    output(0x03, tocken_str[1]-48);
    yield();
  }
  else{
   // output(0x01, tocken_str[0]-48);
    output(0x02, tocken_str[1]-48);
    output(0x03, tocken_str[2]-48);
    yield();
  }
  yield();
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
  
  initialiseMax7219();
    // Configure myThread
  myThread->onRun(handleServer);
  myThread->setInterval(250);

  // Configure myThread
  hisThread.onRun(displaySegment);
  hisThread.setInterval(250);

  // Adds both threads to the controller
  controll.add(myThread);
  controll.add(&hisThread); // & to pass the pointer to it


}

void loop(){
//  handleServer();
  yield();  
  // run ThreadController
  // this will check every thread inside ThreadController,
  // if it should run. If yes, he will run it;
  controll.run();

//  displaySegment();
  yield();
}
