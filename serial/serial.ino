/*  Connects to the home WiFi network
 *  Asks some network parameters
 *  Starts WiFi server with fix IP and listens
 *  Receives and sends messages to the client
 *  Communicates: wifi_client_01.ino
 */
//#include <SPI.h>
//#include <ESP8266WiFi.h>

void setup() {
  Serial.begin(115200);                   // only for debug
  Serial.println("vijay");
  delay(500);
}

void loop () {
    if(Serial.available()>0){
      String str = Serial.readString();
      Serial.println(str.c_str());
    }
    
}
