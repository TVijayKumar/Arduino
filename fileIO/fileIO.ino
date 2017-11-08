
#include "FS.h"
#define FILE "/vijay.txt"

int sw1 = 5;
int sw2 = 4;

void setup() {
  pinMode(sw1,INPUT);
  pinMode(sw2,INPUT);
  
  Serial.begin(115200);
  Serial.println("");
  delay(1000);
  Serial.println("Mounting FS...");

  if (!SPIFFS.begin()) {
    Serial.println("Failed to mount file system");
    return;
  }
  Serial.println("Mounting Success!");
}

void writeFile(){
  Serial.println("Opening file to write");
  File myFile = SPIFFS.open(FILE, "w");
  if (!myFile) {
    Serial.println("Failed to open config file for writing");
    return;
  }
  Serial.println("Writing to file");
  myFile.println("vijay");
//  myFile.println(23,DEC);
  Serial.println("Closing file Write!!");
  myFile.close();
}

bool readFile(){
  char buff[20];
  Serial.println("Opening file to read");
  File myFile = SPIFFS.open(FILE, "r");
  if (!myFile) {
    Serial.println("Failed to open config file");
    return false;
  }
  Serial.println("Reading file");
  myFile.readBytes(buff,10);
  Serial.println(buff);
 //  int value = myFile.read();
//  Serial.println(value,DEC);
  Serial.println("Closing file Read!!");
  myFile.close();
}
void loop(){
  if(false == digitalRead(sw1)){
    while(true){
      if(false != digitalRead(sw1))
        break;
      yield();
    }
    delay(30);
    while(true){
      if(false != digitalRead(sw1))
        break;
      yield();
    }
    writeFile();
  }
  if(false == digitalRead(sw2)){
    while(true){
      if(false != digitalRead(sw2))
        break;
      yield();
    }
    delay(30);
    while(true){
      if(false != digitalRead(sw2))
        break;
      yield();
    }
    readFile();
    yield();  
  }
}
