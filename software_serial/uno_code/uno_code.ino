#include<SoftwareSerial.h>
SoftwareSerial newSerial(12, 13);  // 12 RX, 13 TX
int inbyte;
void setup() {
    Serial.begin(57600);
    newSerial.begin(4800);
}
char incoming;
void loop() {
    incoming = newSerial.read();
  if (incoming == (char)0x03) {
    newSerial.write(10);
    incoming = newSerial.read();
  }
  if (incoming == (char)0x00) {
    newSerial.write(11);
    incoming = newSerial.read();
  } 
  if (incoming == (char)0x01) {
    newSerial.write(12);
    incoming = newSerial.read();
  } 
  if (incoming == (char)0x02) {
    newSerial.write(13);
    incoming = newSerial.read();
  }
    
}
