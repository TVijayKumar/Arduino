/*
DS3231_set.pde
Eric Ayars
4/11

Test of set-time routines for a DS3231 RTC

*/

#include <DS3231.h>
#include <Wire.h>

DS3231 Clock;

byte Year;
byte Month;
byte Date;
byte DoW;
byte Hour;
byte Minute;
byte Second;
bool h12;
bool PM;
bool Century=false;

void GetDateStuff(byte& Year, byte& Month, byte& Day, byte& DoW, 
		byte& Hour, byte& Minute, byte& Second) {
	// Call this if you notice something coming in on 
	// the serial port. The stuff coming in should be in 
	// the order YYMMDDwHHMMSS, with an 'x' at the end.
	boolean GotString = false;
	char InChar;
	byte Temp1, Temp2;
	char InString[20];

	byte j=0;
	while (!GotString) {
		if (Serial.available()) {
			InChar = Serial.read();
			InString[j] = InChar;
			j += 1;
			if (InChar == 'x') {
				GotString = true;
			}
		}
	}
	Serial.println(InString);
	// Read Year first
	Temp1 = (byte)InString[0] -48;
	Temp2 = (byte)InString[1] -48;
	Year = Temp1*10 + Temp2;
	// now month
	Temp1 = (byte)InString[2] -48;
	Temp2 = (byte)InString[3] -48;
	Month = Temp1*10 + Temp2;
	// now date
	Temp1 = (byte)InString[4] -48;
	Temp2 = (byte)InString[5] -48;
	Day = Temp1*10 + Temp2;
	// now Day of Week
	DoW = (byte)InString[6] - 48;		
	// now Hour
	Temp1 = (byte)InString[7] -48;
	Temp2 = (byte)InString[8] -48;
	Hour = Temp1*10 + Temp2;
	// now Minute
	Temp1 = (byte)InString[9] -48;
	Temp2 = (byte)InString[10] -48;
	Minute = Temp1*10 + Temp2;
	// now Second
	Temp1 = (byte)InString[11] -48;
	Temp2 = (byte)InString[12] -48;
	Second = Temp1*10 + Temp2;
}

void printWeek(){
  byte day = Clock.getDoW();
  switch(day){
    case 0 :   Serial.print("SUN"); break;
    case 1 :   Serial.print("MON"); break;
    case 2 :   Serial.print("TUE"); break;
    case 3 :   Serial.print("WED"); break;
    case 4 :   Serial.print("THU"); break;
    case 5 :   Serial.print("FRI"); break;
    case 6 :   Serial.print("SAT"); break;
    default :  Serial.print(Clock.getDoW(), DEC);
  }
  Serial.print(' ');
}
void printTime(){
  // then the date
  Serial.print(Clock.getDate(), DEC);
  Serial.print('/');

  // then the month
  Serial.print(Clock.getMonth(Century), DEC);
  Serial.print('/');
  
  // then the year
  Serial.print(Clock.getYear(), DEC);
  Serial.print(' ');
  
  // and the day of the week
  /*Serial.print(Clock.getDoW(), DEC);
  Serial.print(' ');*/
  printWeek();
  
  // Finally the hour, minute, and second
  Serial.print(Clock.getHour(h12, PM), DEC);
  Serial.print(':');
  Serial.print(Clock.getMinute(), DEC);
  Serial.print(':');
  Serial.print(Clock.getSecond(), DEC);
  // Add AM/PM indicator
  if (h12) {
    if (PM) {
      Serial.print(" PM ");
    } else {
      Serial.print(" AM ");
    }
  } else {
    Serial.print(" 24h ");
  }
  Serial.println("\n");  
}
void setup() {
	// Start the serial port
	Serial.begin(9600);

	// Start the I2C interface
	Wire.begin();
}

void loop() {

	// If something is coming in on the serial line, it's
	// a time correction so set the clock accordingly.
	if (Serial.available()) {
		GetDateStuff(Year, Month, Date, DoW, Hour, Minute, Second);

		Clock.setClockMode(false);	// set to 24h
		//setClockMode(true);	// set to 12h

		Clock.setYear(Year);
		Clock.setMonth(Month);
		Clock.setDate(Date);
		Clock.setDoW(DoW);
		Clock.setHour(Hour);
		Clock.setMinute(Minute);
		Clock.setSecond(Second);

		// Test of alarm functions
		// set A1 to one minute past the time we just set the clock
		// on current day of week.
		Clock.setA1Time(DoW, Hour, Minute+1, Second, 0x0, true, 
			false, false);
		// set A2 to two minutes past, on current day of month.
		Clock.setA2Time(Date, Hour, Minute+2, 0x0, false, false, 
			false);
		// Turn on both alarms, with external interrupt
		Clock.turnOnAlarm(1);
		Clock.turnOnAlarm(2);

	}
  printTime();
	delay(1000);
}
