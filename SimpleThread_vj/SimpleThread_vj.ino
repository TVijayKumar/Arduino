#include <Thread.h>
//int ledPin = 13;

//My simple Thread
Thread myThread = Thread();

int sv = 0;

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

int val = 0;
// callback for myThread
void niceCallback(){
/*	static bool ledStatus = false;
	ledStatus = !ledStatus;

	digitalWrite(ledPin, ledStatus);
*/
  if(!isLocked()){
      lock();
      val++;
      unlock();
  }
	Serial.print("COOL! I'm running on: "); 
	Serial.println(millis());
}

void setup(){
	Serial.begin(9600);

//	pinMode(ledPin, OUTPUT);

	myThread.onRun(niceCallback);
	myThread.setInterval(500);
}

void loop(){
	// checks if thread should run
	if(myThread.shouldRun()){
    Serial.println("Thread starting");
		myThread.run();
	}
	// Other code...
  int v;
  if(!isLocked()){
      lock();
      v = val;
      unlock();
  }
	Serial.print("Vijay:");
  Serial.println(v,DEC);
  delay(1000);
}
