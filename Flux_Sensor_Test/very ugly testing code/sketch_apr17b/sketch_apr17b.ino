#include <Wire.h>
#include <Adafruit_ADS1015.h>
#include <SparkFunTMP102.h>

Adafruit_ADS1115 adc1(0x48);
Adafruit_ADS1115 adc3(0x49);
Adafruit_ADS1115 adc2(0x4B);
Adafruit_ADS1115 dgoshit(0x4A);
void setup() {
  adc1.begin();
  adc2.begin();
  adc3.begin();
  dgoshit.begin();
  Serial.begin(9600);
  adc1.setGain(GAIN_SIXTEEN);
  adc2.setGain(GAIN_SIXTEEN);
  adc3.setGain(GAIN_SIXTEEN);
  dgoshit.setGain(GAIN_SIXTEEN);
}

void loop() {
  int16_t a, b, c, d;
  a = adc1.readADC_Differential_0_1();
  Serial.println(a);
  b = adc2.readADC_Differential_0_1();
  c = adc3.readADC_Differential_0_1();
  d = dgoshit.readADC_Differential_0_1();
  Serial.print("b:");
  Serial.println(b);
  Serial.print("c:");
  Serial.println(c);
  Serial.print("d:");
  Serial.println(d);
  
  delay(400);
}
