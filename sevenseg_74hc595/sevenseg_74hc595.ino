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
void writeReg(){
  digitalWrite(SHCP_PIN,LOW);
  for(int i=7 ; i>=0 ; i--){
    digitalWrite(STCP_PIN,LOW);
    digitalWrite(DS_PIN,data[i]);
    delay(100);
    digitalWrite(STCP_PIN,HIGH);
  }
  digitalWrite(SHCP_PIN,HIGH);
  
}
void loop() {
  // put your main code here, to run repeatedly:
  for(int i=0; i<8; i++){
    data[i]=LOW;
  //  delay(100);  
  } 
  writeReg();
  delay(1000); 
  
  for(int i=0; i<8; i++){
    data[i]=HIGH;
   // delay(100);
  } 
  writeReg();  
  delay(1000);
  
}
/*
void loop() {
  // put your main code here, to run repeatedly:
  for(int i=0; i<8; i++){
    data[i]=HIGH;
    delay(100); 
    writeReg();  
  }
  delay(500); 
  for(int i=0; i<8; i++){
    data[i]=LOW;
    delay(100);
    writeReg();  
  }

}*/
