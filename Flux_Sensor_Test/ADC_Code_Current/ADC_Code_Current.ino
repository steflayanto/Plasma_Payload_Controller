#include <Wire.h>
#include <Adafruit_ADS1015.h>
#include <SparkFunTMP102.h>
#include<SPI.h>
#include<SD.h>

 // A0 is 0.0; no need for it
 const float a1 = 0.0025928;
 const float a2 = -0.0000007602961;
 const float a3 = 0.00000000004637791;
 const float a4 = -0.000000000000002165394;
 const float a5 =  0.00000000000000000006048144;
 const float a6 =  -0.0000000000000000000000007293422;
 const int chipSelect = 4;
 String file_name = "adc.csv";
 unsigned long startTime = 0;

// top to bottom order
Adafruit_ADS1115 adc1(0x4A);
Adafruit_ADS1115 adc2(0x48);
Adafruit_ADS1115 adc3(0x4B);
Adafruit_ADS1115 adc4(0x49);
void setup() {
  adc1.begin();
  adc2.begin();
  adc3.begin();
  adc4.begin();
  Serial.begin(9600);
  while(!Serial) {
    ;
  }
  adc1.setGain(GAIN_SIXTEEN);
  adc2.setGain(GAIN_SIXTEEN);
  adc3.setGain(GAIN_SIXTEEN);
  adc4.setGain(GAIN_SIXTEEN);
}

//10152 sensor. Whatever ADC this one gets plugged into needs to switch the 01 and 23. Right now plugged into top ADC (4A). 


void loop() {
  int16_t S1T, S2T, S3T, S4T, S1HF, S2HF, S3HF, S4HF;
  float T1, T2, T3, T4;
  
  S1HF = adc1.readADC_Differential_2_3();
  S1T = adc1.readADC_Differential_0_1();
  T1 = temp(7.8125 * (float) S1T);
    
  S2HF = adc2.readADC_Differential_2_3();
  S2T = adc2.readADC_Differential_0_1();
  T2 = temp(7.8125 * (float) S2T);

  S3HF = adc3.readADC_Differential_2_3();
  S3T = adc3.readADC_Differential_0_1();
  T3 = temp(7.8125 * (float) S3T);

  S4HF = adc4.readADC_Differential_0_1();
  S4T = adc4.readADC_Differential_2_3();
  T4 = temp(7.8125 * (float) S4T);
  
  //Serial.print("Sensor 1 Tempurature CAL:");
  //Serial.println(T1); 
  Serial.print("Sensor 1 Tempurature:");
  Serial.println(S1T); 
  //Serial.print("Sensor 2 Tempurature CAL:");
  //Serial.println(T2);
  //Serial.print("Sensor 2 Tempurature:");
  //Serial.println(S2T);
  //Serial.print("Sensor 3 Tempurature CAL:");
  //Serial.println(T3);
  //Serial.print("Sensor 3 Tempurature:");
  //Serial.println(S3T);
  //Serial.print("Sensor 4 Tempurature CAL:");
  //Serial.println(T4);
  //Serial.print("Sensor 4 Tempurature:");
  //Serial.println(S4T);

  Serial.print("Sensor 1 Heat Flux:");
  Serial.println(S1HF);
  //Serial.print("Sensor 2 Heat Flux:");
  //Serial.println(S2HF);
  //Serial.print("Sensor 3 Heat Flux:");
  //Serial.println(S3HF);
  //Serial.print("Sensor 4 Heat Flux:");
  //Serial.println(S4HF);

  File adcFile = SD.open(file_name, FILE_WRITE);
  if (adcFile) {
    adcFile.print(millis() - startTime);
    cma(adcFile);
    adcFile.print(S1HF);
    cma(adcFile);
    adcFile.print(S2HF);
    cma(adcFile);
    adcFile.print(S3HF);
    cma(adcFile);
    adcFile.print(S4HF);
  } else {
    Serial.println("bruh");
  }
   delay(400);

}

float temp(float t) {
    return (a1*t) + (a2*pow(t, 2)) + (a3*pow(t, 3)) + (a4*pow(t, 4)) + (a5*pow(t, 5)) + (a6*pow(t, 6));
}

void setupSD() {
  Serial.print("Initializing SD card..");
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed");
    while(1);
  }
  Serial.println("Card initialized");
  startTime = millis();
}

void cma(File f) {
  f.print(",");
}