#include<pthread.h>

void fun(){}

void setup() {
  // put your setup code here, to run once:
    int a;
}

void loop() {
  // put your main code here, to run repeatedly:

  pthread_create(NULL,fun,NULL,NULL);
}
