
byte prev_key = D6;
byte next_key = D7;
byte ok_key = D8;

unsigned int tocken_num = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(prev_key,INPUT);
  pinMode(next_key,INPUT);
  pinMode(ok_key,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(!digitalRead(prev_key)){
    while(!digitalRead(prev_key));
    delay(300);
    while(!digitalRead(prev_key));
    tocken_num--;
    Serial.println("prev");
  }
  
  if(!digitalRead(next_key)){
    while(!digitalRead(next_key));
    delay(300);
    while(!digitalRead(next_key));
    tocken_num++;
    Serial.println("next");
  }
  
  if(!digitalRead(ok_key)){
    while(!digitalRead(prev_key));
    delay(300);
    while(!digitalRead(prev_key));
    Serial.println("ok " + String(tocken_num));
  }
}
