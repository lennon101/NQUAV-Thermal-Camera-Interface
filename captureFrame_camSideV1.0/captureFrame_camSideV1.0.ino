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

byte transfer_frame[] = {(byte)0x6E, (byte)0x00, (byte)0x00, (byte)0x82, (byte)0x00, (byte)0x02, (byte)0xAA, (byte)0xC3, (byte)0x16, (byte)0x00, (byte)0xA9, (byte)0xD5};

byte buff[200];         // a byte array to hold acknoledment frames from camera
char val;               // variable to hold incoming data from RC
int count;              //count the number of images captured
bool buffFull = false; //is the buffer on the camera full or not?

unsigned long time;
unsigned long newTime;

SoftwareSerial camera(6, 7); // RX, TX --> the comm line data is sent to camera
SoftwareSerial xbee(10, 11); // RX, TX --> the comm line for xbee


void setup() {
  // initialize digital pin 13 for light output
  pinMode(13, OUTPUT);

  count = 0;  //reset the number of images taken zero

  // initialize serial:
  Serial.begin(9600);
  Serial.println("---- Tau2 Thermal Camera Wireless System ----");
  Serial.println("Initialising Serial Comms...");

  camera.begin(57600);
  xbee.begin(57600);

  xbee.listen();
  val = xbee.read();
  while (val != 'k') {  //wait for xbee test message from remote control
    val = xbee.read();
    flashLED();
    Serial.println("val != 'k'");
  }
  Serial.println("Remote has signaled its ready");
  for (int i = 1; i <= 2; ++i) {
    digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);              // wait for a second
    digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
    delay(1000);              // wait for a second
  }
  Serial.println("sending acknowledgment message..");
  xbee.write('k');

  Serial.println("...Finished initialising Serial Comms.");

  Serial.println("Ready.");
}

void loop() {
  xbee.listen();    //NB: with two or more serial ports opened, you must force listening on each
  time = millis();
  if (xbee.available()) {
    //Serial.println("Messaged received from xBee.");
    //flashLED(); //send notification that a message has been receieved
    val = xbee.read();    //read the single character recieved from the xbee
    if (val == 'a') {
      if (!buffFull) {
        camera.write(transfer_frame, sizeof(transfer_frame)); //reply statement
        Serial.println("msg sent to camera");
        camera.listen();
        serialEvent(); //call the function
        checkBuff();
        Serial.println();

        count++;  //increment count by 1 to track the number of images captured

        Serial.print("Num Images: ");
        Serial.println(count);

        Serial.println("waiting for camera...");
        for (int i = 2; i >= 1; i--) {
          Serial.print(i);
          Serial.print(",");
          delay(1000);
        }
        Serial.println("...Ready.");
        Serial.println("-------------------------------------");
        flashLED();
        xbee.write('b');
      } else {
        Serial.println("========== buffer full ==========");
      }
    } else if (val == 'k') {
      xbee.write('k');              //send acknowledgment
      newTime = millis();
      Serial.println("heartbeat sent");
    } else {
      Serial.println("Incorrect Button pressed on Remote.");
      Serial.println("Please press button 'B' on the Remote");
      Serial.println();
    }
  } else if (time - newTime > 10000){
    Serial.println("no heartbeat recieved for 10 seconds");
  }
}

void serialEvent() {
  //  if (camera.available()) {
  int numBytes = camera.readBytes(buff, 18); //Serial.readBytes() reads characters from the serial port into a buffer. The function terminates if the determined length has been read, or it times out (see Serial.setTimeout()).
  Serial.print("number of bytes received from cam: ");
  Serial.println(numBytes);

  for (int k = 0; k <= numBytes - 1; ++k) {
    printHexWithLeadingZeros(buff[k]);
    Serial.print(',');
  }
  //  }else{
  //    Serial.println("no ack from camera");
  //  }
}

void printHexWithLeadingZeros(byte hexValue) {
  if (hexValue < 16) {
    Serial.print('0');
  }
  Serial.print(hexValue, HEX);
}

void checkBuff() {
  if (buff[1] == 0x02) {
    Serial.println("========== buffer full ==========");
    buffFull = true;
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

