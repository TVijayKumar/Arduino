//int led = 5;
int sw = D5;

void setup() {
  // put your setup code here, to run once:
//  pinMode(led,OUTPUT);
  pinMode(sw,INPUT);
  Serial.begin(9600);               // only for debug
}

void loop() {
  // put your main code here, to run repeatedly:
  if(false == digitalRead(sw))
  {
    while(false == digitalRead(sw));
    delay(100);
    while(false == digitalRead(sw));
    Serial.println("Connecting to Router..");
  }

  /*  digitalWrite(led,true);
  else
    digitalWrite(led,false);
*/
}
