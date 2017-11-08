int led = 5;
int sw = 4;

void setup() {
  // put your setup code here, to run once:
  pinMode(led,OUTPUT);
  pinMode(sw,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(false == digitalRead(sw))
    digitalWrite(led,true);
  else
    digitalWrite(led,false);

}
