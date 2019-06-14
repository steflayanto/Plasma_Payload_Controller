#include <SPI.h>
#include <SD.h>
#include <Wire.h>
#include <Adafruit_ADS1015.h>

#define CHIP_SELECT 4
#define WRITE false //CHANGE BEFORE FLIGHT

int fileCount = 0;
unsigned long fileCountTimer = 0;
unsigned long frequency = 10000; //new file every 10 seconds (10,000ms)

//ADC data
int16_t S1T, S2T, S3T, S4T, S1HF, S2HF, S3HF, S4HF;

Adafruit_ADS1115 adc1(0x4A);
Adafruit_ADS1115 adc2(0x48);
Adafruit_ADS1115 adc3(0x4B);
Adafruit_ADS1115 adc4(0x49);

void setup() {
#ifndef ESP8266
  while (!Serial);     // For running on ESP boards. Will pause until serial console opens
#endif
  Serial.begin(116200);
  Serial.print("Initializing SD card...");  // see if the card is present and can be initialized:
  if (!SD.begin(CHIP_SELECT)) {
    Serial.println("Card failed, or not present");
    while (1 && WRITE);
  }
  Serial.println("card initialized.");
  initSensors();
}

void loop() {
  readSensors();
  //printADCs();
  String dataString = formatData();
  if (WRITE) {
    if (millis() - fileCountTimer >= frequency) {
      fileCountTimer = millis();
      fileCount++;
    }
    File dataFile = SD.open(fileName(), FILE_WRITE);
    if (dataFile) { // if the file is available, write to it:
      dataFile.println(dataString);
      dataFile.close();
      // print to the serial port too:
      Serial.println(dataString);
    } else {
      Serial.println("error opening " + fileName());
    }
  }
  Serial.println(dataString);
}

String fileName() {
  return "log" + String(fileCount) + ".csv";
}

String formatData() {
  String ADCs = String(S1HF) + "," + String(S1T) + ","
    + String(S2HF) + "," + String(S2T) + "," 
    + String(S3HF) + "," + String(S3T) + "," 
    + String(S4HF) + "," + String(S4T) + ",";
  String tempSens = String(getCircuitVoltage()) + ",";
  return ADCs + tempSens;
}

void initSensors() {
  adc1.begin();
  adc2.begin();
  adc3.begin();
  adc4.begin();
  adc1.setGain(GAIN_SIXTEEN);
  adc2.setGain(GAIN_SIXTEEN);
  adc3.setGain(GAIN_SIXTEEN);
  adc4.setGain(GAIN_SIXTEEN);
  Serial.println("Sensors Initialized");
}

void readSensors() {
  //Read ADCs
  S1HF = adc1.readADC_Differential_0_1();
  S1T = adc1.readADC_Differential_2_3();

  S2HF = adc2.readADC_Differential_0_1();
  S2T = adc2.readADC_Differential_2_3();

  S3HF = adc3.readADC_Differential_0_1();
  S3T = adc3.readADC_Differential_2_3();

  S4HF = adc4.readADC_Differential_0_1();
  S4T = adc4.readADC_Differential_2_3();
}


int getCircuitVoltage() {
  return (analogRead(A1) * 3.3) / 4095.0;
}

void printADCs() {
  Serial.print(F("Sensor 1 Temperature:"));
  Serial.println(S1T);
  Serial.print("Sensor 2 Temperature:");
  Serial.println(S2T);
  Serial.print("Sensor 3 Temperature:");
  Serial.println(S3T);
  Serial.print("Sensor 4 Temperature:");
  Serial.println(S4T);

  Serial.print(F("Sensor 1 Heat Flux:"));
  Serial.println(S1HF);
  Serial.print("Sensor 2 Heat Flux:");
  Serial.println(S2HF);
  Serial.print("Sensor 3 Heat Flux:");
  Serial.println(S3HF);
  Serial.print("Sensor 4 Heat Flux:");
  Serial.println(S4HF);
}
