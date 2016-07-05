void setup() {
  Serial.begin(9600);
}

void loop() {
  byte msg[] = {(byte)0x6E, (byte)0x00, (byte)0x00, (byte)0x82, (byte)0x00, (byte)0x02, (byte)0xAA, (byte)0xC3, (byte)0x16, (byte)0x00, (byte)0xA9, (byte)0xD5};
  Serial.write(msg, sizeof(msg));
  delay(3000);
}
