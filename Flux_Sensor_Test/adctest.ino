#include <Wire.h>
#include <Adafruit_ADS1015.h>

// Global Variables
const int adcCount = 4;
const int seebeck = 40; // Rough estimated coefficient given by PHFS doc; not exact!

// Sensors; assuming 1:1 PHFS:ADC
// When wiring, different addresses need different connections for ADR port!
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
  for (int i = 0; i < adcCount; i++) {
    adcs[i].begin(); 
    adcs[i].setGain(GAIN_EIGHT); // Input range +/- 512mV, 1 bit = 0.25mV
  }
  adcTestSetup();
}

void adcLoop() {
  float flux[adcCount];
  int16_t tempDelta; // Can be one general value for all ADCs or read individually
  float temp; // Temperature reading at voltage measurement site, must use additional sensor
  temp += tempCalc(tempDelta);
  for (int i = 0; i < adcCount; i++) {
    flux[i] = adcs[i].readADC_Differential_0_1() / sensCalc(sensitivities[i], temp);
    testADC(flux[i]);
  }
  
}

// Returns sensitivity scalar according to datasheet formula
// sens = sensor-specific sensitivity factor
// How good is floating point precision for Arduino?
float sensCalc(float sens, int temp) {
  return (0.003334 * temp + 0.918) * sens; // Formula given by PHFS doc
}

// Returns temperature difference for given voltage difference
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
