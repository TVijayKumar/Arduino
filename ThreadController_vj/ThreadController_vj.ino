#include <Thread.h>
#include <ThreadController.h>

int val = 0;

// ThreadController that will controll all threads
ThreadController controll = ThreadController();

//My Thread (as a pointer)
Thread* myThread = new Thread();
//His Thread (not pointer)
Thread hisThread = Thread();

  int sv;
  bool isLocked(){
    if(0 == sv)
     return false;  
  }

  void lock(){
   sv++;
  }

  void unlock(){
   sv--;  
  }


// callback for myThread
void niceCallback(){
	Serial.print("COOL! I'm running on: ");
	Serial.println(millis());
  if(!isLocked()){
      lock();
      val++;
      unlock();
  }
}

// callback for hisThread
void boringCallback(){
  int v;
	Serial.print("BORING...");
  if(!isLocked()){
      lock();
      v = val;
      unlock();
  }
  Serial.println(v,DEC);
}

void setup(){
	Serial.begin(9600);

	// Configure myThread
	myThread->onRun(niceCallback);
	myThread->setInterval(500);

	// Configure myThread
	hisThread.onRun(boringCallback);
	hisThread.setInterval(250);

	// Adds both threads to the controller
	controll.add(myThread);
	controll.add(&hisThread); // & to pass the pointer to it
}

void loop(){
	// run ThreadController
	// this will check every thread inside ThreadController,
	// if it should run. If yes, he will run it;
	controll.run();

	// Rest of code
}
