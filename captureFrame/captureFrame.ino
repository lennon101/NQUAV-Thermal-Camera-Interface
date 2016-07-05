/*
  Software serial multple serial test

  Receives from the hardware serial, sends to software serial.
  Receives from software serial, sends to hardware serial.

  The circuit:
   RX is digital pin 10 (connect to TX of other device)
   TX is digital pin 11 (connect to RX of other device)

  Note:
  Not all pins on the Mega and Mega 2560 support change interrupts,
  so only the following can be used for RX:
  10, 11, 12, 13, 50, 51, 52, 53, 62, 63, 64, 65, 66, 67, 68, 69

  Not all pins on the Leonardo support change interrupts,
  so only the following can be used for RX:
  8, 9, 10, 11, 14 (MISO), 15 (SCK), 16 (MOSI).

  created back in the mists of time
  modified 25 May 2012
  by Tom Igoe
  based on Mikal Hart's example

  This example code is in the public domain.

*/
#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); // RX, TX

byte setup1[] = {(byte)0x6E,(byte)0x00,(byte)0x00,(byte)0xAA,(byte)0x00,(byte)0x00,(byte)0xA5,(byte)0xE6,(byte)0x00,(byte)0x00};
byte snapshot[] = {(byte)0x6E, (byte)0x00, (byte)0x00, (byte)0x82, (byte)0x00, (byte)0x02, (byte)0xAA, (byte)0xC3, (byte)0x16, (byte)0x00, (byte)0xA9, (byte)0xD5};

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(57600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);

}

void loop() { // run over and over
  //Serial.println("taking snapshot");
    mySerial.write(setup1, sizeof(setup1));
    mySerial.write(snapshot, sizeof(snapshot));

    
//  int bytesSent = Serial.write(snapshot, sizeof(snapshot));
//  Serial.println();
//  Serial.print("bytes sent is: ");
//  Serial.println(bytesSent);
  Serial.write(snapshot,sizeof(snapshot));
  Serial.println("\nsnapshot taken");

//  if (mySerial.available()) {
//    Serial.println("returned:");
//    Serial.write(mySerial.read());
//    Serial.println();
//  }

  delay(10000);

}

