void printLSMData() {
  Serial.print(LSMaccelX()); Serial.print(","); 
  Serial.print(LSMaccelY()); Serial.print(","); 
  Serial.print(LSMaccelZ()); Serial.print(","); 
  Serial.print(LSMmagX()); Serial.print(",");
  Serial.print(LSMmagY()); Serial.print(",");
  Serial.print(LSMmagZ()); Serial.print(",");
  Serial.print(LSMgyroX()); Serial.print(",");
  Serial.print(LSMgyroY()); Serial.print(",");
  Serial.print(LSMgyroZ()); Serial.print(",");
}

void printBMEData() {
  Serial.print(BMEpressure()); Serial.print(","); 
  Serial.print(BMEalt()); Serial.print(","); 
  Serial.print(BMEhum()); Serial.print(","); 
  Serial.print(BMEtemp()); Serial.print(",");
}

void printTempSensData() {
  Serial.print(tempSensTemp()); Serial.print(",");
}
