#include "SoftwareSerial.h"
#define TX_PIN 14 // Arduino transmit  YELLOW WIRE  labeled RX on printer
#define RX_PIN 12 // Arduino receive   GREEN WIRE   labeled TX on printer

SoftwareSerial mySerial(RX_PIN, TX_PIN); // Declare SoftwareSerial obj first


void setup() {
//  Serial.begin(115200);               // only for debug
  mySerial.begin(9600);
  mySerial.println("Hello vijay");
}

void loop () {
  mySerial.println("Good JOB");
  delay(1000);  
  
  mySerial.println("This is Dharma, careful!!");
  delay(1000);               
}
