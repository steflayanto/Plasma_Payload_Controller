#include <Adafruit_ADS1015.h>

#include <Wire.h>

// TMP102 sensor(0x48)
Adafruit_ADS1115 sensor;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  sensor.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  //float t = sensor.readTempC();
  int16_t t = sensor.readADC_Differential_0_1();
  Serial.println(t);
}
