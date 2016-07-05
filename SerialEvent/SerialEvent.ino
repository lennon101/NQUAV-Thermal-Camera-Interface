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

byte baud_rate[] = {0x6E,0x00,0x00,0x07,0x00,0x02,0x7A,0x69,0x00,0x04,0x40,0x84};

byte buff[200];         // a byte array to hold incoming data
boolean complete = false;  // all bytes of packet received
int i = 0; 
int terminatingIndex = 0;

SoftwareSerial camera(6, 7); // RX, TX

void setup() {
  // initialize serial:
  Serial.begin(9600);
  camera.begin(57600);
}

void loop() {
  delay(2000);
  camera.write(baud_rate,sizeof(baud_rate)); //reply statement
  serialEvent(); //call the function
  Serial.println();
}

/*
  SerialEvent occurs whenever a new data comes in the
 hardware serial RX.  This routine is run between each
 time loop() runs, so using delay inside loop can delay
 response.  Multiple bytes of data may be available.
 */
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

void printHexWithLeadingZeros(byte hexValue){
  if (hexValue <16){ Serial.print('0');}
  Serial.print(hexValue,HEX);
}



