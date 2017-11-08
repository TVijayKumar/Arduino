/*int DS_PIN = 16;
int SHCP_PIN = 5;
int STCP_PIN = 4;
*/
int DS_PIN = D0;
int SHCP_PIN = D1;
int STCP_PIN = D2;

void setup() {
  // put your setup code here, to run once:
  pinMode(DS_PIN , OUTPUT);
  pinMode(STCP_PIN , OUTPUT);
  pinMode(SHCP_PIN , OUTPUT);
  Serial.begin(9600);
}

byte num[]={
64,   //0
121,  //1
36,   //2
48,   //3
25,   //4
18,   //5
2,    //6
120,  //7
0,    //8
24    //9
};

void loop() {
  // put your main code here, to run repeatedly:
/*
  for(int i = 0 ; i < 10 ; i++){
    yield();
    digitalWrite(STCP_PIN,LOW);
    shiftOut(DS_PIN,SHCP_PIN,MSBFIRST,num[i]);
    digitalWrite(STCP_PIN,HIGH);
    yield();
    delay(1000);  
  }
  for(int i = 9 ; i >= 0 ; i--){
    yield();
    digitalWrite(STCP_PIN,LOW);
    shiftOut(DS_PIN,SHCP_PIN,MSBFIRST,num[i]);
    digitalWrite(STCP_PIN,HIGH);
    yield();
    delay(1000);  
  }*/
  digitalWrite(STCP_PIN,LOW);
  shiftOut(DS_PIN,SHCP_PIN,MSBFIRST,num[0]);
//  shiftOut(DS_PIN,SHCP_PIN,MSBFIRST,121);
  digitalWrite(STCP_PIN,HIGH);
  delay(1000);
  yield();
  
  digitalWrite(STCP_PIN,LOW);
  shiftOut(DS_PIN,SHCP_PIN,MSBFIRST,num[1]);
//  shiftOut(DS_PIN,SHCP_PIN,MSBFIRST,36);
  digitalWrite(STCP_PIN,HIGH);
  delay(1000);
  yield();
  
  digitalWrite(STCP_PIN,LOW);
  shiftOut(DS_PIN,SHCP_PIN,MSBFIRST,num[2]);
//  shiftOut(DS_PIN,SHCP_PIN,MSBFIRST,48);
  digitalWrite(STCP_PIN,HIGH);
  delay(1000);
  yield();
  
  digitalWrite(STCP_PIN,LOW);
  shiftOut(DS_PIN,SHCP_PIN,MSBFIRST,num[3]);
//  shiftOut(DS_PIN,SHCP_PIN,MSBFIRST,25);
  digitalWrite(STCP_PIN,HIGH);
  delay(1000);
  yield();
  
  digitalWrite(STCP_PIN,LOW);
  shiftOut(DS_PIN,SHCP_PIN,MSBFIRST,num[4]);
//  shiftOut(DS_PIN,SHCP_PIN,MSBFIRST,18);
  digitalWrite(STCP_PIN,HIGH);
  delay(1000);
  yield();
  
  digitalWrite(STCP_PIN,LOW);
  shiftOut(DS_PIN,SHCP_PIN,MSBFIRST,num[5]);
//  shiftOut(DS_PIN,SHCP_PIN,MSBFIRST,2);
  digitalWrite(STCP_PIN,HIGH);
  delay(1000);
  yield();
  
  digitalWrite(STCP_PIN,LOW);
  shiftOut(DS_PIN,SHCP_PIN,MSBFIRST,num[6]);
//  shiftOut(DS_PIN,SHCP_PIN,MSBFIRST,120);
  digitalWrite(STCP_PIN,HIGH);
  delay(1000);
  yield();
  
  digitalWrite(STCP_PIN,LOW);
  shiftOut(DS_PIN,SHCP_PIN,MSBFIRST,num[7]);
//  shiftOut(DS_PIN,SHCP_PIN,MSBFIRST,0);
  digitalWrite(STCP_PIN,HIGH);
  delay(1000);
  yield();
  
  digitalWrite(STCP_PIN,LOW);
  shiftOut(DS_PIN,SHCP_PIN,MSBFIRST,num[8]);
//  shiftOut(DS_PIN,SHCP_PIN,MSBFIRST,24);
  digitalWrite(STCP_PIN,HIGH);
  delay(1000);
  yield();
  
  digitalWrite(STCP_PIN,LOW);
  shiftOut(DS_PIN,SHCP_PIN,MSBFIRST,num[9]);
//  shiftOut(DS_PIN,SHCP_PIN,MSBFIRST,64);
  digitalWrite(STCP_PIN,HIGH);
  delay(1000);
  yield();
  
}
