/**
   JoystickShield - Arduino Library for JoystickShield (http://hardwarefun.com/projects/joystick-shield)

   Copyright 2011  Sudar Muthu  (email : sudar@sudarmuthu.com)

   ----------------------------------------------------------------------------
   "THE BEER-WARE LICENSE" (Revision 42):
   <sudar@sudarmuthu.com> wrote this file. As long as you retain this notice you
   can do whatever you want with this stuff. If we meet some day, and you think
   this stuff is worth it, you can buy me a beer or coffee in return - Sudar
   ----------------------------------------------------------------------------
   2014 edit by Markus Mücke, muecke.ma(a)gmail.com
   Changes for JoysikShield V1.2
   added a function to read the amplitude of the joystick
   added a auto calibrate function for 3.3V and 5V mode

   Added functions:
    Functions for F and E Button
    Calibrate Joystick
    xAmplitude
    yAmplitude
*/

/**
   Before running this example, stack the JoystickShield on top of Arduino board

*/

#include <JoystickShield.h> // include JoystickShield Library
#include <SoftwareSerial.h>
JoystickShield joystickShield; // create an instance of JoystickShield object

SoftwareSerial xbee(10, 11); // RX, TX --> the comm line data is sent to camera
char val;               // variable to hold incoming data from RC
int syncCount = 0;

void setup() {
  // initialize digital pin 13 for light output
  pinMode(13, OUTPUT);

  Serial.begin(9600);
  xbee.begin(57600);

  xbee.listen();
  xbee.write('k');    //send test data to camera
  val = xbee.read();  //attempt to get acknowlegement from camera
  while (val != 'k') {
    flashLED();         //wait for reply message
    xbee.write('k');    //continue sending test data to camera until a reply message is received
    val = xbee.read();
    if (val == 'k') {
      Serial.println("Camera has signaled its ready");
    }
  }

  Serial.println("...Finished initialising Serial Comms.");
  Serial.println("Ready.");

  delay(100);
  // new calibration function
  joystickShield.calibrateJoystick();
}

void loop() {
  joystickShield.processEvents(); // process events

  ++syncCount;
  Serial.println(syncCount);
  if (syncCount == 500) {
    syncCount = 0;                  //reset count
    xbee.write('k');                //send heartbeat to camera
    while (xbee.available() == 0) { //wait for comms from camera
      Serial.println("xbee not available");
      delay(1000);
      xbee.write('k');              //send connection test to camera
    }
    
    val = xbee.read();      //check for ack
    Serial.println(val);
    while (val != 'k') {
      flashLED();         //wait for reply message
      xbee.write('k');    //continue sending test data to camera until a reply message is received
      delay(1000);
      Serial.println("val != 'k'");
      val = xbee.read();
    }
    Serial.println("Camera has signaled its ready");
  }

  if (joystickShield.isJoystickButton()) {
    Serial.println("Joystick Clicked") ;
  }

  if (joystickShield.isUpButton()) {
    Serial.println("Up Button Clicked") ;
  }

  if (joystickShield.isRightButton()) {
    Serial.println("Right Button Clicked") ;
    flashLED();

    xbee.write('a');
    Serial.println("msg sent to xbee");

    //check for reply msg
    serialEvent();
    Serial.println("-------------");
  }

  if (joystickShield.isDownButton()) {
    Serial.println("Down Button Clicked") ;
  }

  if (joystickShield.isLeftButton()) {
    Serial.println("Left Button Clicked") ;
  }

  // new eventfunctions
  if (joystickShield.isEButton()) {
    Serial.println("E Button Clicked") ;
  }

  if (joystickShield.isFButton()) {
    Serial.println("F Button Clicked") ;
  }
}

void serialEvent() {
  if (xbee.available()) {
    val = xbee.read();
    if (val == 'a') {
      flashLED();
    }
  }
}


void flashLED() {
  for (int i = 1; i <= 2; ++i) {
    digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(300);              // wait for a second
    digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
    delay(300);              // wait for a second
  }
}
