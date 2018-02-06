#include"PrinterVj.h"

PrinterVj printobj;
int sw = D5;  //button to print tocken
int i=0;

void printerCallback(){
  if(false == digitalRead(sw)){
    while(false == digitalRead(sw));
    delay(200);
    while(false == digitalRead(sw));
    i++;
    Serial.println("Tocken : " + String(i));
    printobj.printStr("Tocken : " + String(i));
    yield();
 }
 yield();
// delay(700L);
}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);               // only for debug

  printobj.init();
  pinMode(sw,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  printerCallback();
   // printobj.printStr("Tocken : " + String(1));
    yield();

}
