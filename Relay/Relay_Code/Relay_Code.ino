#define RELAY 10                //this means before compiling, find RELAY replace with 10
const int relay = 10;           //arduino digital output pin

//For Trigger function.
unsigned long timer;
boolean notYetCalled = true;
boolean turnedOff = false;

void setup()
{
  Serial.begin(9600);
  pinMode(relay, OUTPUT);
  digitalWrite(relay, LOW);
  timer = 0;
}

void display()
{
}

void loop()
{
  Serial.println("Writing to SD Card");
  if (coast()) {
    trigger(2000, relay);
  }
  delay(100);
}

boolean coast() {
  if (millis() > 5000 && millis() < 9000) {
    return true;
  }
  return false;
}


// Trigger is a non-blocking function which prints Active the first time it is called, then prints Off after a cerain duration
// that is specified with the paramter passed in. Repeated calls to trigger do nothing. UPDATE
void trigger(int duration, int pin) {
  if (notYetCalled) {
    digitalWrite(pin, HIGH);
    Serial.println("Active");
    timer = millis();
    notYetCalled = false;
  }else if (millis() - timer > duration && !turnedOff) {
    digitalWrite(pin, LOW);
    Serial.println("Off");
    turnedOff = true;
  } 
}
