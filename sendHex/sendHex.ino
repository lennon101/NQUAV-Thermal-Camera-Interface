#include <SoftwareSerial.h>

byte data[] = {0x6e,0x00,0x00,0x0b,0x00,0x00,0x2f,0x4a,0x00};

SoftwareSerial mySerial(10, 11); // RX, TX

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  mySerial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("sending data");
  mySerial.write(data,sizeof(data));
  mySerial.print('\n');

  delay(5000);

  if (mySerial.available()){
    Serial.print(mySerial.read(),HEX);
    Serial.println();
  }
}
