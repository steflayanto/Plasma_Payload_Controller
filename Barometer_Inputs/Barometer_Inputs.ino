float input;
int interval = 50, amount;
unsigned long timer;
float RightInput = 0, LeftInput = 0, CentralInput = 0;
float secondDerivative(int tempInterval);

void setup() {
  Serial.begin(9600);
  input = 100;
  amount = 0;
  timer = millis();
  
}

void loop() {
  updateInput(true); //pass in 'false' if you dont want it to print out values to serial monitor

  //Your Code Here.
  
}

void updateInput(boolean prints) {
  if (amount == 0 && millis() > 2000) {
    amount = 250;
  }
  if (input == 0) {
    //Serial.println("ended");
    return;
  }
  if (input > 30000) {
    input = 30000;
    amount = -50;
  }
  int tempInterval = millis() - timer;
  // which will act as dt
  if (tempInterval > interval) {
    input += amount;
    LeftInput = CentralInput;
    CentralInput = RightInput;
    RightInput = input;
    timer = millis();
    if (prints){
      Serial.println(input);
      Serial.println(secondDerivative(tempInterval));
    }
  }
}

/*
*   @para: Time interval of time difference
*   Global parameters: LeftInput, RightInput, CentralInput
*   Estimation function of second derivative using Taylor Expansion
*   Error EstimatedL O(dt^3)
*   April 21th by Kaiser Sun
*/
float secondDerivative(int tempInterval) {
    return (LeftInput - 2*CentralInput + RightInput) / tempInterval*tempInterval;
  }
