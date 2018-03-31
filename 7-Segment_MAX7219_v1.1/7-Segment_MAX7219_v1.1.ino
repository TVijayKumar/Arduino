#define MAX7219_DIN D1
#define MAX7219_CS  D2
#define MAX7219_CLK D3

void initialise()
{
  digitalWrite(MAX7219_CS, HIGH);
  pinMode(MAX7219_DIN, OUTPUT);
  pinMode(MAX7219_CS, OUTPUT);
  pinMode(MAX7219_CLK, OUTPUT);
}

void output(byte address, byte data)
{
  digitalWrite(MAX7219_CS, LOW);
  shiftOut(MAX7219_DIN, MAX7219_CLK, MSBFIRST, address);
  shiftOut(MAX7219_DIN, MAX7219_CLK, MSBFIRST, data);
  digitalWrite(MAX7219_CS, HIGH);
}

void sendToDisplay(int val){
  output(0x01,val/100);
  val = val %100;
  output(0x02,val/10);
  val = val %10;
  output(0x03,val);
}
void setup() {
  Serial.begin(9600);                   // only for debug
  Serial.println("Started..");
 
  // put your setup code here, to run once:
  initialise();
  output(0x0f, 0x00); //display test register - test mode off
  output(0x0c, 0x01); //shutdown register - normal operation
  output(0x0b, 0x07); //scan limit register - display digits 0 thru 7
  output(0x0a, 0x0f); //intensity register - max brightness
  output(0x09, 0xff); //decode mode register - CodeB decode all digits
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Loop Started..");

  for(int i=0;i<1000;i++){
    Serial.println(i,DEC);
     sendToDisplay(i);
    delay(300);  
  }/*
  output(0x01, 1);
  output(0x02, 2);
  output(0x03, 5);
  delay(600);*/
}
