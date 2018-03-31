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
/*  output(0x08, 0x08); //digit 7 (leftmost digit) data
  output(0x07, 0x07);
  output(0x06, 0x06);
  output(0x05, 0x05);
  output(0x04, 0x04);
  output(0x03, 0x03);
  output(0x02, 0x02);
  for(int i=0;i<10;i++){
    output(0x01, i); //digit 0 (rightmost digit) data
    delay(300);
  }*/
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Loop Started..");
/*  for(int i=0;i<10;i++){
    output(0x03, i);
    if(i<9)
      output(0x02, i+1);
    else
      output(0x02, i-9);
    if(i==8 )
      output(0x01, i-8); //digit 0 (rightmost digit) data
    else if(i==9)
      output(0x01, i-8); //digit 0 (rightmost digit) data
    else
      output(0x01, i+2); //digit 0 (rightmost digit) data

//    output(0x01, i);
    delay(600);
  }*/
//  output(0x01, 1);
//  output(0x02, 2);
  output(0x03, 5);
  delay(600);
}
