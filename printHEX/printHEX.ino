void setup() {
  // initialize serial:
  Serial.begin(9600);
}

void loop() {
  byte data[] = {0x6e,0x00,0x00,0x0b,0x00,0x00,0x2f,0x4a,0x00};

  for (int i = 0; i <= sizeof(data);++i){
      printHexWithLeadingZeros(data[i]);
      //Serial.print(',');
  }
  Serial.println('\n');
}

void printHexWithLeadingZeros(byte hexValue){
  if (hexValue <16){ Serial.print('0');}
  Serial.print(hexValue,HEX);
}

