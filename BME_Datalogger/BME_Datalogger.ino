/*
  SD card datalogger

  The circuit:
   analog sensors on analog ins 0, 1, and 2
   SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 4 (for MKRZero SD: SDCARD_SS_PIN)

*/

#if defined(ARDUINO_SAMD_ZERO) && defined(SERIAL_PORT_USBVIRTUAL)
// Required for Serial on Zero based boards
#define Serial SERIAL_PORT_USBVIRTUAL
#endif

#include <SPI.h>
#include <SD.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define FACTOR 0.2
#define LOW_BURN 10
#define LOW_EARLY 20 // equiv HIGH_BURN
#define LOW_LATE 30  // equiv HIGH_EARLY
#define HIGH_LATE 50

#define SEALEVELPRESSURE_HPA (1013.25)
Adafruit_BME280 bme; // I2C

const int chipSelect = 4;
const int altOffset = 120;
unsigned long startTime = 0;
float alt = 0;
String file_name = "DATALOG.csv";

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(115200);

  //initialize built in LED
  pinMode(LED_BUILTIN, OUTPUT);

  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }


  Serial.print("Initializing SD card...");

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    while (1);
  }
  Serial.println("card initialized.");

  File dataFile = SD.open(file_name, FILE_WRITE);
  if (dataFile) {
    dataFile.print("Time (milliseconds)");
    dataFile.print(",");
    dataFile.print("Altitude (meters)");
    dataFile.print(",");
    dataFile.print("Flight Stage (0-4)");
    dataFile.println(",");
    dataFile.close();
  } else { // if the file isn't open, pop up an error:
    Serial.println("error opening file.csv");
  }
  for (int i = 0; i < 3; i++) {
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);                       // wait for a second
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
    delay(500);                       // wait for a second
  }
  delay(500);
  startTime = millis();
  bme.begin();
}

void loop() {

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  File dataFile = SD.open(file_name, FILE_WRITE);
  alt = bme.readAltitude(SEALEVELPRESSURE_HPA) - altOffset;
  // if the file is available, write to it:
  if (dataFile) {
    dataFile.print(millis() - startTime);
    dataFile.print(",");
    dataFile.print(alt);
    dataFile.print(",");
    dataFile.print(bmeDecision());
    dataFile.println(",");
    dataFile.close();
    // print to the serial port too:
    Serial.print(alt);
    Serial.print(",");
    Serial.println(bmeDecision());
  } else { // if the file isn't open, pop up an error:
    Serial.println("error opening file");
  }
  delay(20);
}

float bmeDecision() {
  //map to flight stages, mapping
  if (alt < LOW_BURN) {
    return 0;
  } else {
    //w/o throttle, burn = 10 sec = 10000 ft
    //1 burn
    if (alt < LOW_EARLY) {
      return map(constrain(alt, LOW_BURN, LOW_EARLY), LOW_BURN, LOW_EARLY, 1 - FACTOR, 1 + FACTOR);
    } else if (alt < LOW_LATE) {
      //2 early coast
      return map(constrain(alt, LOW_EARLY, LOW_LATE), LOW_EARLY, LOW_LATE, 2 - FACTOR, 2 + FACTOR);
    } else if (alt < HIGH_LATE) {
      //3 late coast
      return map(constrain(alt, LOW_LATE, HIGH_LATE), LOW_LATE, HIGH_LATE, 3 - FACTOR, 3 + FACTOR);
    } else {
      //4 decent = 26067 and down
      return 4.0;//map(alt, 100, 1000, 3, 4);
    }
  }
}
