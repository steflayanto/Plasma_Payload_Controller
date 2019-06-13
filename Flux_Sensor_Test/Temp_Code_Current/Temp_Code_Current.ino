#include <Wire.h>
#include <Adafruit_ADS1015.h>
#include <SparkFunTMP102.h>
#include<SPI.h>
#include<SD.h>

//SCL to A5
//SDA to A4
//GND to GND
//1.4 to 3.3V

const int chipSelect = 4;
String file_name = "tempsens.txt";
unsigned long startTime = 0;
 
TMP102 tempSens(0x48);

void setup() {
  tempSens.begin();
  Serial.begin(115200);
  while(!Serial);
  //setupSD();
  Serial.println("Starting");
}

void loop() { 
  float Temperature;
  Temperature = tempSens.readTempF();
  Serial.println(Temperature);
  /*
  File tempFile = SD.open(file_name, FILE_WRITE);
  if (tempFile) {
    tempFile.print(millis() - startTime);
    tempFile.print(",");
    tempFile.print(Temperature);
    tempFile.println();
    tempFile.close();
  } else {
    Serial.println("problem writing");
  }*/
   delay(400);

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
