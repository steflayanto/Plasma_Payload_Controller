#define RELAY_PIN 11                //this means before compiling, find RELAY replace with 10



void setup()
{
  Serial.begin(9600);
  //while(!Serial);
  relayInit();
  pinMode(13, HIGH);
  delay(8000);
  Serial.println("active");
  digitalWrite(RELAY_PIN, HIGH);
  delay(2000);
  Serial.println("Off");
  digitalWrite(RELAY_PIN, LOW);
  while(1);
}

void loop()
{
  Serial.println("Writing to SD Card");
  //if (Serial.available() > 0) {
  if (coast()) {
    trigger(5000, RELAY_PIN);
    
  }
  delay(100);
}

boolean coast() {
  if (millis() > 5000 && millis() < 6000) {
    Serial.println("triggered");
    return true;
  }
  return false;
}
