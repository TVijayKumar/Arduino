void lcdWrite(char *data,int col=0xff, int row=0xff);
void lcdInit();
void lcdClear();

void setup() {
  // put your setup code here, to run once:

  lcdInit();

}

void loop() {
  // put your main code here, to run repeatedly:
  int tocken = 45;
  lcdClear();
  lcdWrite("Mahi",1,3);
  delay(2000);
  
  lcdClear();
  lcdWrite("anil");
  delay(2000);
  
}
