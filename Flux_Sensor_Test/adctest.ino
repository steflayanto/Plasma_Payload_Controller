#include <Wire.h>
#include <Adafruit_ADS1015.h>

const size_t adcCount = 4;
const int seebeck = 40; // Rough estimated coefficient given by PHFS doc; not exact!
Adafruit_ADS1115 adcs[adcCount] = {
  Adafruit_ADS1115(0x48);
  Adafruit_ADS1115(0x49);
  Adafruit_ADS1115(0x4A);
  Adafruit_ADS1115(0x4B);
}

float sensitivities[adcCount] = {
  // Hardcoded sensors-specific sensitivity values
}

void adcSetup() {
  adc1.begin();
  adc2.begin();
  adc3.begin();
  adc4.begin();
  adcTestSetup();
}

void adcLoop() {
  float flux[adcCount];
  int16_t tempDelta; // Can be one general value for all ADCs or read individually
  float temp; // Temperature reading at voltage measurement site, must use additional sensor
  temp += tempCalc(tempDelta);
  for (int i = 0; i < adcCount; i++) {
    flux[i] = sensCalc(sensitivities[i], temp) * adcs[i].readADC_Differential_0_1();
    testADC(flux[i]);
  }
  
}

// How good is floating point precision for Arduino?
float sensCalc(float sens, int t) {
  return (0.003334 * temp + 0.918) * sens; // Formula given by PHFS doc
}

float tempCalc(int16_t delta) {
  return (float) delta / seebeck; // values are int16_t and int, so have to cast
}

// Following functions are for testing / serial plotting the flux valuess
void testADC(float a[]) {
  for (int i = 0; i < sizeOf(a); i++) {
    Serial.print(a[i]);
    Serial.print(",");
  }
  Serial.println();
}


void adcTestSetup() {
  Serial.begin(9600); 
}
