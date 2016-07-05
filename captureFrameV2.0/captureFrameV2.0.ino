/*
  Serial Event example

  When new serial data arrives, this sketch adds it to a String.
  When a newline is received, the loop prints the string and
  clears it.

  A good test for this is to try it with a GPS receiver
  that sends out NMEA 0183 sentences.

  Created 9 May 2011
  by Tom Igoe

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/SerialEvent

*/

#include <SoftwareSerial.h>

byte data[] = {(byte)0x6E, (byte)0x00, (byte)0x00, (byte)0x82, (byte)0x00, (byte)0x02, (byte)0xAA, (byte)0xC3, (byte)0x16, (byte)0x00, (byte)0xA9, (byte)0xD5};

byte buff[200];         // a byte array to hold incoming data
int i = 0;

SoftwareSerial camera(10, 11); // RX, TX --> the comm line data is sent to camera

void setup() {
  // initialize serial:
  Serial.begin(9600);
  camera.begin(57600);
  Serial.setTimeout(3000);
  camera.setTimeout(3000);
}

void loop() {
  Serial.flush();
  camera.write(data, sizeof(data)); //send msg to camera
  //Serial.println("msg sent to camera");

  //serialEvent(); //check for reply msg
  int numBytes = camera.readBytes(buff, 15);
  Serial.print("number of bytes received from cam: ");
  Serial.println(numBytes);

  for (int k = 0; k <= numBytes-1; ++k) {
    printHexWithLeadingZeros(buff[k]);
    Serial.print(',');
  }
  
  Serial.println();
  Serial.println("delaying");
  delay(5000);
}

void printHexWithLeadingZeros(byte hexValue) {
  if (hexValue < 16) {
    Serial.print('0');
  }
  Serial.print(hexValue, HEX);
}

