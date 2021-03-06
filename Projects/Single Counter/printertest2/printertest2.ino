/*------------------------------------------------------------------------
  Example sketch for Adafruit Thermal Printer library for Arduino.
  Demonstrates a few text styles & layouts, bitmap printing, etc.

  IMPORTANT: DECLARATIONS DIFFER FROM PRIOR VERSIONS OF THIS LIBRARY.
  This is to support newer & more board types, especially ones that don't
  support SoftwareSerial (e.g. Arduino Due).  You can pass any Stream
  (e.g. Serial1) to the printer constructor.  See notes below.

  You may need to edit the PRINTER_FIRMWARE value in Adafruit_Thermal.h
  to match your printer (hold feed button on powerup for test page).
  ------------------------------------------------------------------------*/

#include "Adafruit_Thermal.h"
//#include "adalogo.h"
//#include "adaqrcode.h"

// Here's the new syntax when using SoftwareSerial (e.g. Arduino Uno) ----
// If using hardware serial instead, comment out or remove these lines:

#include "SoftwareSerial.h"
#define TX_PIN D3 // Arduino transmit  YELLOW WIRE  labeled RX on printer
#define RX_PIN D4 // Arduino receive   GREEN WIRE   labeled TX on printer

SoftwareSerial mySerial(RX_PIN, TX_PIN); // Declare SoftwareSerial obj first
Adafruit_Thermal printer(&mySerial);     // Pass addr to printer constructor
// Then see setup() function regarding serial & printer begin() calls.

// Here's the syntax for hardware serial (e.g. Arduino Due) --------------
// Un-comment the following line if using hardware serial:

//Adafruit_Thermal printer(&Serial);      // Or Serial2, Serial3, etc.

// -----------------------------------------------------------------------

void setup() {

  // This line is for compatibility with the Adafruit IotP project pack,
  // which uses pin 7 as a spare grounding point.  You only need this if
  // wired up the same way (w/3-pin header into pins 5/6/7):
  //pinMode(7, OUTPUT); digitalWrite(7, LOW);

  // NOTE: SOME PRINTERS NEED 9600 BAUD instead of 19200, check test page.
//  mySerial.begin(19200);  // Initialize SoftwareSerial
  mySerial.begin(9600);  // Initialize SoftwareSerial
  Serial.begin(9600); // Use this instead if using hardware serial
  Serial.println("VIJAY");
  printer.begin();        // Init printer (same regardless of serial type)

  // The following calls are in setup(), but don't *need* to be.  Use them
  // anywhere!  They're just here so they run one time and are not printed
  // over and over (which would happen if they were in loop() instead).
  // Some functions will feed a line when called, this is normal.

 
  // Test character double-height on & off
  printer.doubleHeightOn();
  printer.println(F("Double Height ON"));
 
  printer.justify('C');
  printer.println(F("Center justified"));
 
  // Test more styles
  printer.boldOn();
  yield();
  printer.println(F("Bold text"));
  yield();
 
}

void loop() {
  yield();
  printer.setSize('L');        // Set type size, accepts 'S', 'M', 'L'
  printer.println(F("Large"));
  while(true){
    yield();
      printer.setSize('L');        // Set type size, accepts 'S', 'M', 'L'
      printer.println(F("Welcome vijay!"));
    delay(3000L);
  }

}
