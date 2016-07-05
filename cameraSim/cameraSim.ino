#include <SoftwareSerial.h>

byte buff[200];         // a byte array to hold incoming data
SoftwareSerial serial(10, 11); // RX, TX --> the comm line connecting arduino to arduino

void setup() {
  Serial.begin(9600); //serial for debugging
  serial.begin(9600); //serial comms between dev boards
}

void loop() {
  // put your main code here, to run repeatedly:
  if (serial.available()) {
    int numBytes = serial.readBytes(buff, 15); //read any incoming data and save the amount of bytes received
    sendReply();
    Serial.print("number of bytes received: ");
    Serial.println(numBytes);

    //print the data recieved
    for (int k = 0; k <= numBytes - 1; ++k) {
      printHexWithLeadingZeros(buff[k]);
      Serial.print(',');
    }
    Serial.println();
  }

}

void sendReply() {
  byte replyMsg[] = {(byte)0x6E, (byte)0x00, (byte)0x00, (byte)0x82, (byte)0x00, (byte)0x02, (byte)0xAA, (byte)0xC3, (byte)0x16, (byte)0x00, (byte)0xA9, (byte)0xD5};
  serial.write(replyMsg, sizeof(replyMsg));
}

void printHexWithLeadingZeros(byte hexValue) {
  if (hexValue < 16) {
    Serial.print('0');
  }
  Serial.print(hexValue, HEX);
}
