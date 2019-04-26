#include <Wire.h>
#include <Adafruit_ADS1015.h>
#include <SparkFunTMP102.h>

 typedef struct {
  Adafruit_ADS1115 adc;
  float sensitivity;
} sensor;

TMP102 tempSens(0x48);

const int adcCount = ?  ;
const int seebeck = 40; // Rough estimated coefficient given by PHFS doc; not exact!
const float sensMultiplier = .003334;
const float sensOffset = .918;

// IMPORTANT: This assumes that the sensors are in ascending order with 10151 on 0x48 and 10154 on 0x4B!
sensor adcs[adcCount] = {{Adafruit_ADS1115(), 1.55}};//, {Adafruit_ADS1115(0x49), 1.55},
                         //{Adafruit_ADS1115(0x4A), 1.48}, {Adafruit_ADS1115(0x4B), 1.58},};

void adcSetup() {
  for (int i = 0; i < adcCount; i++) {
    adcs[i].adc.begin(); 
 //   adcs[i].adc.setGain(GAIN_FOUR); // Input range +/- 1.024V, 1 bit = 0.5mV
  }
}

void adcLoop() {
  float flux[adcCount];
  int16_t tempDelta = adcs[0].adc.readADC_Differential_2_3(); // Can be one general value for all ADCs or read individuall
  float temp = tempSens.readTempC(); // Sensitivity calculation uses Celsius!
  temp += tempDeltaCalc(tempDelta); // Adds the differential voltage converted to temperature to get sensor temp
  for (int i = 0; i < adcCount; i++) {
    flux[i] = adcs[i].adc.readADC_Differential_0_1() / sensCalc(adcs[i].sensitivity, temp);
    testADC(flux);
  }
  
}

// Returns sensitivity scalar according to datasheet formula
float sensCalc(float sens, int temp) {
  return (sensMultiplier * temp + sensOffset) * sens; // Formula given by PHFS doc
}

// Returns temperature difference for given voltage difference
float tempDeltaCalc(int16_t delta) {
  return (float) delta / seebeck; // values are int16_t and int, so have to cast
}

// Following functions are for testing / serial plotting the flux valuess
void testADC(float a[]) {
  for (int i = 0; i < adcCount; i++) {
    Serial.print(a[i]);
    Serial.print(","); // You can open serial plotter instead of serial monitor to graph these values
  }
  Serial.println();
}


void adcTestSetup() {
}

// These setup and loop functions are so you can test with this program as a standalone
// in final product these will be gone
void setup() {
  Serial.begin(9600);
  adcSetup();
}

void bandaid() {
  int16_t f, tdiff;
  f = adcs[0].adc.readADC_Differential_0_1();
  tdiff = adcs[0].adc.readADC_Differential_2_3();
  Serial.println(f + "," + tdiff);
}

void loop() {
  bandaid();
  // adcLoop();
  delay(250);
}
