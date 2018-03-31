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
#include <LiquidCrystal.h>

byte prev_key = D0;
byte next_key = D1;
const int rs = D3, en = D4, d4 = D5, d5 = D6, d6 = D7, d7 = D8;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

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
Thread* keys_thread = new Thread();

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

char tocken_str[6]={'\0'};
char current_tocken_str[6]={'\0'};

void parseClientRequest(String request){
  const char *ptr = request.c_str();
    for(int i=0; i < request.length(); i++){
      if(*(ptr+i) == '#' ){  
        lcd.clear();
        for(char i=0; i < 6 ; i++) tocken_str[i]='\0';
        for(int j=0; *(ptr+i) != '\r' ; j++){
         i++;
         if(*(ptr+i) == '*'){
             *(tocken_str+j) = '\0';
             break;
          }
          *(tocken_str+j) = *(ptr+i);
        }
        break;
      }
    }
    lcd.setCursor(0,0);
    lcd.write("                ");
    lcd.setCursor(0,0);
    lcd.write("TotalTockens:");
    lcd.write(tocken_str);  
}

void serverHandler(){
  WiFiClient client = server.available();
  if (client) {
    if (client.connected()) {
      String request = client.readStringUntil('\r');    // receives the message from the client
      Serial.print("From client: "); Serial.println(request);
//      lcd.clear();
//      lcd.write(request.c_str());
      parseClientRequest(request);

      client.flush();
      client.print("To Main Display : #"); 
      client.print(current_tocken_str);
      client.println("*\r");
    }
    client.stop();                // tarminates the connection with the client
  }  
}
void wifiStatus(){
  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("connecting to Router...");
    lcd.clear();
    lcd.write("cnctng 2 Router");
    lcd.setCursor(2,1);
    lcd.write(".....");
    delay(300);
  }
}

unsigned int tocken_num = 0;
void keysHandler(){
  yield();
  if(!digitalRead(prev_key)){
    while(!digitalRead(prev_key));
    delay(300);
    while(!digitalRead(prev_key));
    tocken_num--;
    Serial.println("prev");
  }
  
  yield();
  if(!digitalRead(next_key)){
    while(!digitalRead(next_key));
    delay(300);
    while(!digitalRead(next_key));
    tocken_num++;
    Serial.println("next");
  }
  
/*  yield();
  if(!digitalRead(ok_key)){
    while(!digitalRead(prev_key));
    delay(300);
    while(!digitalRead(prev_key));
    Serial.println("ok " + String(tocken_num));
  }*/

  yield();
  if(tocken_num >= atoi(tocken_str)) tocken_num = atoi(tocken_str);
  strcpy(current_tocken_str,String(tocken_num).c_str());
  
 // lcd.clear();
 // lcd.setCursor(0,0);
//  lcd.write("TotalTockens:");
//  lcd.write(tocken_str);  

  lcd.setCursor(0,1);
  lcd.write("                ");
  lcd.setCursor(0,1);
  lcd.write("Current : ");
  lcd.write(current_tocken_str);    
  yield();
}
void setup() {
  pinMode(prev_key,INPUT);
  pinMode(next_key,INPUT);
  
  lcd.begin(16, 2);
  Serial.begin(9600);                   // only for debug
  
  WiFi.config(ip, gateway, subnet);       // forces to use the fix IP
  Serial.println("connecting to Router..");
  WiFi.begin(ssid, pass);                 // connects to the WiFi router
  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("connecting to Router...");
    lcd.clear();
    lcd.write("cnctng 2 Router");
    lcd.setCursor(2,1);
    lcd.write(".....");
    delay(500);
  }
  lcd.clear();
  lcd.write("cnctd 2 Router");
  Serial.println("connected to Router.");
  
  server.begin();                         // starts the server
  printWIFI();

  server_thread->onRun(serverHandler);
  server_thread->setInterval(500);
  keys_thread->onRun(keysHandler);
  keys_thread->setInterval(250);
  thread_controll.add(server_thread);
  thread_controll.add(keys_thread);
}
void loop () {

    // run ThreadController
  // this will check every thread inside ThreadController,
  // if it should run. If yes, he will run it;
  wifiStatus();
  thread_controll.run();
  // Rest of code

}
