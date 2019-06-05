float rightInput = 0, leftInput = 0, centralInput = 0;


/*
    @para: Time interval of time difference
    Global parameters: LeftInput, RightInput, CentralInput
    Estimation function of second derivative using Taylor Expansion
    Error EstimatedL O(dt^3)
    April 21th by Kaiser Sun
*/
float secondDerivative(float tempInterval) {
//  Serial.print(leftInput);
//  Serial.print(", ");
//  Serial.print(centralInput);
//  Serial.print(", ");
//  Serial.print(rightInput);
//  Serial.print(", ");
  //Serial.println();
  return (leftInput - (2 * centralInput) + rightInput) / (tempInterval * tempInterval);
}


void updateInputs(float newValue) {
  leftInput = centralInput;
  centralInput = rightInput;
  rightInput = newValue;
}
