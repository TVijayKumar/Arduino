#include"PrinterVj.h"

PrinterVj printobj;

void setup() {
  // put your setup code here, to run once:
  printobj.init();
}

void loop() {
  // put your main code here, to run repeatedly:
   int val = 230;
   String str = "Tocken : "; 
   printobj.printStr(str + String(243));
   delay(3000L);
 
}
