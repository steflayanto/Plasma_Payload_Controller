#define RELAY_PIN 10                //this means before compiling, find RELAY replace with 10



void setup()
{
  Serial.begin(9600);
  relayInit();
}

void loop()
{
  Serial.println("Writing to SD Card");
  if (Serial.available() > 0) {
    trigger(2000, RELAY_PIN);
  }
  delay(100);
}

boolean coast() {
  if (millis() > 5000 && millis() < 9000) {
    return true;
  }
  return false;
}
