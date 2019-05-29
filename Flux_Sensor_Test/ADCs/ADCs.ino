#include <Wire.h>
#include <Adafruit_ADS1015.h>
#include <SparkFunTMP102.h>

Adafruit_ADS1115 adc3(0x48);
Adafruit_ADS1115 adc1(0x49);
Adafruit_ADS1115 adc2(0x4B);
Adafruit_ADS1115 adc4(0x4A); //shit

void setup() {
  adc1.begin();
  adc2.begin();
  adc3.begin();
  adc4.begin();
  Serial.begin(115200);
  adc1.setGain(GAIN_SIXTEEN);
  adc2.setGain(GAIN_SIXTEEN);
  adc3.setGain(GAIN_SIXTEEN);
  adc4.setGain(GAIN_SIXTEEN);
}

void loop() {
  int16_t a, b, c, d;
  a = adc1.readADC_Differential_0_1();
  b = adc2.readADC_Differential_0_1();
  c = adc3.readADC_Differential_0_1();
  d = adc4.readADC_Differential_0_1();
  Serial.print("a:")
  Serial.println(a);
  Serial.print("b:");
  Serial.println(b);
  Serial.print("c:");
  Serial.println(c);
  Serial.print("d:");
  Serial.println(d);

  delay(400);
}
