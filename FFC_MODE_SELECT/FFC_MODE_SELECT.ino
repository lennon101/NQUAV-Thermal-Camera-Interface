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

byte data[] = {0x6E,0x00,0x00,0x0B,0x00,0x00,0x2F,0x4A,0x00, 0x00};

byte buff[200];         // a byte array to hold incoming data
boolean complete = false;  // all bytes of packet received
int i = 0; 
int terminatingIndex = 0;

SoftwareSerial camera(10, 11); // RX, TX --> the comm line data is sent to camera

void setup() {
  // initialize serial:
  Serial.begin(9600);
  camera.begin(9600);
}

void loop() {
  Serial.flush();
  camera.write(data,sizeof(data)); //send msg to camera
  Serial.println("msg sent to camera");
  
  serialEvent(); //check for reply msg
  if (complete) {
      for (int k = 0; k <= terminatingIndex;++k){
        printHexWithLeadingZeros(buff[k]);
        Serial.print(',');
      }
    Serial.println();
    complete = false;
  }
  Serial.println("delaying");
  delay(5000);
}

/*
  SerialEvent occurs whenever a new data comes in the
 hardware serial RX.  This routine is run between each
 time loop() runs, so using delay inside loop can delay
 response.  Multiple bytes of data may be available.
 */
void serialEvent() {
  Serial.println(1);
  while (camera.available()) {
    Serial.println(2);
    // get the new byte:
    byte newByte = (byte)camera.read();
    
    Serial.println(newByte, HEX);
    
    if (newByte == 0x6E) {i = 0;} //start of new packet, set index back to zero
    
    // add it to the buffer:
    buff[i] = newByte;
    ++i;
    
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
//    if (newByte ==0x1021) {
    Serial.print("index = "); 
    Serial.print(i);
    Serial.print('\n');
    if (i == 12){
      complete = true;
      terminatingIndex = i; //used for capturing end point of data
      i = 0;
    }
  }
}

void printHexWithLeadingZeros(byte hexValue){
  if (hexValue <16){ Serial.print('0');}
  Serial.print(hexValue,HEX);
}

