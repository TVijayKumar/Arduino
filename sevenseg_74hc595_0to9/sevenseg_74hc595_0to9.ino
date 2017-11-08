int DS_PIN = 16;
int SHCP_PIN = 5;
int STCP_PIN = 4;
void setup() {
  // put your setup code here, to run once:
  pinMode(DS_PIN , OUTPUT);
  pinMode(STCP_PIN , OUTPUT);
  pinMode(SHCP_PIN , OUTPUT);
}


bool data[8]={LOW};

void writeRegCore(){
  digitalWrite(SHCP_PIN,LOW);
  for(int i=7 ; i>=0 ; i--){
    digitalWrite(STCP_PIN,LOW);
    digitalWrite(DS_PIN,data[i]);
    digitalWrite(STCP_PIN,HIGH);
  }
  digitalWrite(SHCP_PIN,HIGH);
}

void writeReg(unsigned char ch){
  for(int i=0 ; i<=7 ; i++){
    data[i] = (((1 << i) & 0xff) & ch);
    writeRegCore();
  }
}
void loop() {
  // put your main code here, to run repeatedly:

  writeReg(0x81); 
  delay(600);

  writeReg(0xed); 
  delay(600);

  writeReg(0xc3); 
  delay(600);

  writeReg(0xc9); 
  delay(600);

  writeReg(0x2d); 
  delay(600);

  writeReg(0x19); 
  delay(600);

  writeReg(0x11); 
  delay(600);

  writeReg(0xcd); 
  delay(600);

  writeReg(0x01); 
  delay(600);

  writeReg(0x0d); 
  delay(600);
}
