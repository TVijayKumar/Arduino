void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int pid = fork();
  if(pid){
    while(1){
      Serial.println("Child");
    }  
  }
  else{
    while(1){
      Serial.println("Parent");
    }  
  }
}
