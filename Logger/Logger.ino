#include <SPI.h>
#include <SD.h>

#define CHIP_SELECT 4

int fileCount = 0;
unsigned long timer = 0;
unsigned long frequency = 5000; //new file every 5 seconds (5000ms)

void setup() {
  #ifndef ESP8266
  while (!Serial);     // For running on ESP boards. Will pause until serial console opens
  #endif
  Serial.begin(116200);
  
  Serial.print("Initializing SD card...");  // see if the card is present and can be initialized:
  if (!SD.begin(CHIP_SELECT)) {
    Serial.println("Card failed, or not present");
    while (1);
  }
  Serial.println("card initialized.");
  initSensors();
}

void loop() {
  if (millis() - timer >= frequency) {
    timer = millis();
    fileCount++;
  }
  readSensors();
  String dataString = "";
  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  String fileName = "log" + String(fileCount) + ".txt";
  File dataFile = SD.open(fileName, FILE_WRITE);
  if (dataFile) { // if the file is available, write to it:
    dataFile.println(dataString);
    dataFile.close();
    // print to the serial port too:
    Serial.println(dataString);
  } else {
    Serial.println("error opening " + fileName);
  }
}

void initSensors() {
  
}

void readSensors() {
  //reads the ADCs directly
}
