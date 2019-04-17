float input;
int interval = 50, amount;
unsigned long timer;

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
  if (millis() - timer > interval) {
    input += amount;
    timer = millis();
    if (prints){
      Serial.println(input);
    }
  }
}
