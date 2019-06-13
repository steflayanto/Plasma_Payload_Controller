#include <Wire.h>
#include <Adafruit_ADS1015.h>
#include <SparkFunTMP102.h>
#include<SPI.h>
#include<SD.h>

#define WRITE false

const int chipSelect = 4;
String file_name = "adc.txt";
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
  Serial.begin(115200);
  while (!Serial) {
    ;
  }
  if (WRITE) {
    setupSD();
  }
  Serial.println("Setup complete");
  adc1.setGain(GAIN_SIXTEEN);
  adc2.setGain(GAIN_SIXTEEN);
  adc3.setGain(GAIN_SIXTEEN);
  adc4.setGain(GAIN_SIXTEEN);
}


void loop() {
  Serial.println("Starting loop");
  int16_t S1T, S2T, S3T, S4T, S1HF, S2HF, S3HF, S4HF;

  S1HF = adc1.readADC_Differential_0_1();
  S1T = adc1.readADC_Differential_2_3();

  S2HF = adc2.readADC_Differential_0_1();
  S2T = adc2.readADC_Differential_2_3();

  S3HF = adc3.readADC_Differential_0_1();
  S3T = adc3.readADC_Differential_2_3();

  S4HF = adc4.readADC_Differential_0_1();
  S4T = adc4.readADC_Differential_2_3();

  Serial.print("Sensor 1 Tempurature:");
  Serial.println(S1T);
  Serial.print("Sensor 2 Tempurature:");
  Serial.println(S2T);
  Serial.print("Sensor 3 Tempurature:");
  Serial.println(S3T);
  Serial.print("Sensor 4 Tempurature:");
  Serial.println(S4T);

  Serial.print("Sensor 1 Heat Flux:");
  Serial.println(S1HF);
  Serial.print("Sensor 2 Heat Flux:");
  Serial.println(S2HF);
  Serial.print("Sensor 3 Heat Flux:");
  Serial.println(S3HF);
  Serial.print("Sensor 4 Heat Flux:");
  Serial.println(S4HF);

  if (WRITE) {
    File adcFile = SD.open(file_name, FILE_WRITE);
    if (adcFile) {
      adcFile.print(millis() - startTime);
      adcFile.print(",");
      adcFile.print(S1HF);
      adcFile.print(",");
      adcFile.print(S2HF);
      adcFile.print(",");
      adcFile.print(S3HF);
      adcFile.print(",");
      adcFile.print(S4HF);
      adcFile.print(",");
      adcFile.print(S1T);
      adcFile.print(",");
      adcFile.print(S2T);
      adcFile.print(",");
      adcFile.print(S3T);
      adcFile.print(",");
      adcFile.print(S4T);
      adcFile.println();
      adcFile.close();
    } else {
      Serial.println("problem writing");
    }
  }
  delay(400);

}


void setupSD() {
  Serial.print("Initializing SD card..");
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed");
    while (1);
  }
  Serial.println("Card initialized");
  startTime = millis();
}

void cma(File f) {
  f.print(",");
}
