#include <Wire.h>
#include <Adafruit_ADS1015.h>
#include <SparkFunTMP102.h>

Adafruit_ADS1115 adc1(0x48);
Adafruit_ADS1115 adc2(0x49);
TMP102 tempSens(0x48);
void setup() {
  adc1.begin();
  tempSens.begin();
  adc2.begin();
  Serial.begin(9600);
}

void loop() {
  int16_t f1, f2;
  f1 = adc1.readADC_Differential_0_1();
  f2 = adc2.readADC_Differential_0_1();
  float t = tempSens.readTempF();
//  Serial.print("t: ");
//  Serial.println(t);
  Serial.print("f1: ");
  Serial.println(f1);
  Serial.print("f2: ");
  Serial.println(f2);
  delay(400);
}
