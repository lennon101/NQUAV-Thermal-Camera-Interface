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

byte frame1[] = {(byte)0x6E, (byte)0x00, (byte)0x00, (byte)0xAA, (byte)0x00, (byte)0x00, (byte)0xA5, (byte)0xE6, (byte)0x00, (byte)0x00};
byte frame2[] = {(byte)0x6E, (byte)0x00, (byte)0x00, (byte)0x82, (byte)0x00, (byte)0x02, (byte)0xAA, (byte)0xC3, (byte)0x16, (byte)0x00, (byte)0xA9, (byte)0xD5};


byte buff[100];         // a byte array to hold incoming data

SoftwareSerial camera(10, 11); // RX, TX --> the comm line data is sent to camera

void setup() {
  // initialize serial:
  Serial.begin(9600);
  camera.begin(57600);

  //serialEvent();
  //  Serial.setTimeout(3000);
  //camera.setTimeout(3000);
}

void loop() {
  //Serial.flush(); //Waits for the transmission of outgoing serial data to complete. (Prior to Arduino 1.0, this instead removed any buffered incoming serial data.)
  //camera.flush();
  if (Serial.available()) {
    char val = Serial.read();

    if (val == 'c') {
      //camera.flush();
      camera.write(frame1, sizeof(frame1)); //send msg to camera
      Serial.println("msg sent to camera");

      serialEvent();    //check for reply msg
      //      Serial.println("\ndelaying...");
      //      delay(5000);
      //      Serial.println("...Ready.");
      camera.write(frame2, sizeof(frame2)); //send msg to camera
      Serial.println("msg sent to camera");
      serialEvent();    //check for reply msg
    }
  }
}

void serialEvent() {
  int numBytes = camera.readBytes(buff, 18);          //Serial.readBytes() reads characters from the serial port into a buffer. The function terminates if the determined length has been read, or it times out (see Serial.setTimeout()).

  if (numBytes > 0) {
    Serial.print("number of bytes received from cam: ");
    Serial.println(numBytes);
    for (int k = 0; k <= numBytes - 1; ++k) {
      printHexWithLeadingZeros(buff[k]);
      Serial.print(',');
    }
  } else {
    Serial.println("no valid data was returned from camera");
  }
}

void printHexWithLeadingZeros(byte hexValue) {
  if (hexValue < 16) {
    Serial.print('0');
  }
  Serial.print(hexValue, HEX);
}

