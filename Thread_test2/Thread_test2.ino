
#include <Thread.h>
#include <ThreadController.h>

// ThreadController that will controll all threads
ThreadController thread_controll = ThreadController();

//My Thread (as a pointer)
Thread *my_tid = new Thread();

int i=0;

void handleClients(){
  i++;
  Serial.print(i,DEC);
  
}
void setup() {
  Serial.begin(9600);                   // only for debug
  my_tid -> onRun(handleClients);
  my_tid -> setInterval(500);
  thread_controll.add(my_tid);
  
  delay(200);
}

void loop () {
  thread_controll.run();
  delay(2000);
}

