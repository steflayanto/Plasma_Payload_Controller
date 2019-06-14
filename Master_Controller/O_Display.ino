void printFlightParameters() {
  Serial1.print(weightedFlightStage); Serial1.print(",");
  Serial.print(primaryTrigger()); Serial.print(",");
  Serial.print(imuTrigger()); Serial.print(",");
  Serial.print(baroTrigger()); Serial.print(",");
  Serial.print(timerStage); Serial.print(",");
  Serial.print(decisionAlgorithm()); Serial.print(",");
  Serial.print(activated); Serial.print(",");
  Serial.print(inCone); Serial.print(",");
}

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
