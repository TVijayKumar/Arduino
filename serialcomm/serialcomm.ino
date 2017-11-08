/*  Connects to the home WiFi network
 *  Asks some network parameters
 *  Sends and receives message from the server in every 2 seconds
 *  Communicates: wifi_server_01.ino
 */ 
//#include <SPI.h>
//#include <ESP8266WiFi.h>

byte ledPin = 2;

unsigned long askTimer = 0;


void setup() {
//  Serial.begin(115200);               // only for debug
  Serial.begin(9600);
  Serial.println("Hello vijay");
  pinMode(ledPin, OUTPUT);
}

void disp(Stream *S){
  S->println("disp func is EXECUTING");  
}
void loop () {
  disp(&Serial);
  digitalWrite(ledPin, LOW);    // to show the communication only (inverted logic)
  Serial.println("welcome to Project!");
  delay(1000);  
  digitalWrite(ledPin, HIGH);
  delay(1000);               
}
