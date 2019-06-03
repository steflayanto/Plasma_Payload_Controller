float rightInput = 0, leftInput = 0, centralInput = 0;

// Store the data
#define DATA_STORAGE 9
float secDeriData[DATA_STORAGE];
int isFull = 0;

/*
*   @param: newValue, the new altitude value
*   Update the new value to the storage(use shift
*   for better value obtaining)
*/
void updateStorage(float newValue) {
  for (int i = 1; i <= DATA_STORAGE - 1; i++) {
    *(secDeriData + (DATA_STORAGE - i)) = *(secDeriData + (DATA_STORAGE - (i+1)));
  }
  *secDeriData = newValue;
  isFull ++;
  return;
}

/*
    @para: Time interval of time difference
    Global parameters: LeftInput, RightInput, CentralInput
    Estimation function of second derivative using Taylor Expansion
    Error EstimatedL O(dt^3)
*/
float secondDerivative(float tempInterval) {
  Serial.print(leftInput);
  Serial.print('\t');
  Serial.print(centralInput);
  Serial.print('\t');
  Serial.print(rightInput);
  Serial.println();
  return (leftInput - (2 * centralInput) + rightInput) / (tempInterval * tempInterval);
}

/*
*   Update the value that is put in;
*   If the data is full, start using the value in storage
*/
void updateInputs() {
  if(isFull < 9) {
    leftInput = centralInput;
    centralInput = rightInput;
    rightInput = secDeriData[0];
  } else {
    leftInput = secDeriData[DATA_STORAGE - 1];
    centralInput = secDeriData[int(DATA_STORAGE/2)];
    rightInput = secDeriData[0];
  }
  return;
}
