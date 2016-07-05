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

byte frame1[] = {(byte)0x6E, (byte)0x00, (byte)0x00, (byte)0x82, (byte)0x00, (byte)0x02, (byte)0xAA, (byte)0xC3, (byte)0x16, (byte)0x00, (byte)0xA9, (byte)0xD5};
byte buff[200];         // a byte array to hold incoming data
int i = 0;

SoftwareSerial xbee(12, 13); // RX, TX --> the comm line data is sent to camera

void setup() {
  Serial.begin(9600);
  xbee.begin(9600);

  delay(100);
  // new calibration function
  joystickShield.calibrateJoystick();


}

void loop() {
  joystickShield.processEvents(); // process events

  if (joystickShield.isJoystickButton()) {
    Serial.println("Joystick Clicked") ;
  }

  if (joystickShield.isUpButton()) {
    Serial.println("Up Button Clicked") ;
  }

  if (joystickShield.isRightButton()) {
    Serial.println("Right Button Clicked") ;

    xbee.write('a');
    Serial.println("msg sent to xbee");

    //serialEvent(); //check for reply msg
    serialEvent();
    Serial.println("\ndelaying");
    delay(5000);
    Serial.println();
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
    Serial.write(xbee.read());
  }
}


