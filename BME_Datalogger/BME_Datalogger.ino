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

//This constant and struct are all that is needed for the MAF
#define MAF_SIZE 5 // number of samples for the running avg
struct {
  float total;
  float arr[MAF_SIZE];
  int index;
} filter;

<<<<<<< HEAD


#define FACTOR 0.2
=======
#define FACTOR 0.2f
>>>>>>> 8094ab02967db1222101b5537732c35b44c8a4ae
#define LOW_BURN 10
#define LOW_EARLY 20 // equiv HIGH_BURN
#define LOW_LATE 30  // equiv HIGH_EARLY
#define HIGH_LATE 50

#define SEALEVELPRESSURE_HPA (1013.25)
Adafruit_BME280 bme; // I2C

const int chipSelect = 4;
const int altOffset = -14;
unsigned long startTime = 0;
float alt = 0, altMAF = 0;
String file_name = "bme2.csv";
float rate = 0;
unsigned long MAFTimer = 0;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  Serial.print("Initializing SD card...");
  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    //while (1);
  }
  Serial.println("card initialized.");
  writeHeaders();
  boolean status = bme.begin();
  if (!status) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }
  initMAF();
  pinMode(8, OUTPUT);
  for (int i = 0; i < 2; i++) {
    digitalWrite(8, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);                       // wait for a second
    digitalWrite(8, LOW);    // turn the LED off by making the voltage LOW
    delay(500);                       // wait for a second
  }
  digitalWrite(8, HIGH);
  Serial.println("Started");
  startTime = millis();
  delay(250);
  digitalWrite(8, LOW);
}

void writeHeaders() {
  File dataFile = SD.open(file_name, FILE_WRITE);
  if (dataFile) {
    dataFile.println(); // Print spacer
    dataFile.print("Time (milliseconds)");
    dataFile.print(",");
    dataFile.print("Altitude (meters)");
    dataFile.print(",");
    dataFile.print("Flight Stage (0-4)");
    dataFile.print(",");
    dataFile.print("Filtered Altitude");
    dataFile.print(",");
    dataFile.print("Second Derivative");
    dataFile.println(",");
    dataFile.close();
  } else { // if the file isn't open, pop up an error:
    Serial.println("error opening file.csv");
  }
}

void loop() {
  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  unsigned long interval = millis() - MAFTimer;
  if (interval > 100) {
    updateInputs(altMAF);
    rate = secondDerivative((float)interval/1000);
    Serial.println(rate);
    MAFTimer = millis();
  }
  
  File dataFile = SD.open(file_name, FILE_WRITE);
  alt = bme.readAltitude(SEALEVELPRESSURE_HPA) - altOffset;
  updateMAF(alt);
  altMAF = getMAFAve();
  // if the file is available, write to it:
  float decision = bmeDecision();

  float timeStamp = millis() - startTime;
  if (dataFile) {
    dataFile.print(timeStamp);
    dataFile.print(",");
    dataFile.print(alt);
    dataFile.print(",");
    dataFile.print(decision);
    dataFile.print(",");
    dataFile.print(altMAF);
    dataFile.print(",");
    dataFile.print(rate);
    dataFile.println(",");
    dataFile.close();
    // print to the serial port too:
  } else { // if the file isn't open, pop up an error:
    //Serial.println("error opening file");
  }
//  Serial.print(timeStamp);
//  Serial.print(",");
//  Serial.print(alt);
//  Serial.print(",");
//  Serial.print(decision);
//  Serial.print(",");
//  Serial.print(altMAF);
//  Serial.print(",");
//  Serial.print(rate);
//  Serial.println(",");
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
      return mapFloat(alt, LOW_BURN, LOW_EARLY, 1 - FACTOR, 1 + FACTOR);
    } else if (alt < LOW_LATE) {
      //2 early coast
      return mapFloat(alt, LOW_EARLY, LOW_LATE, 2 - FACTOR, 2 + FACTOR);
    } else if (alt < HIGH_LATE) {
      //3 late coast
      return mapFloat(alt, LOW_LATE, HIGH_LATE, 3 - FACTOR, 3 + FACTOR);
    } else {
      //4 decent = 26067 and down
      return 4.0;//map(alt, 100, 1000, 3, 4);
    }
  }
}

// Float map function with 3 digits precision. includes Constrain
float mapFloat(float val, float inLo, float inHi, float outLo, float outHi) { 
  return map(constrain(val, inLo, inHi) * 1000, inLo * 1000, inHi * 1000, outLo * 1000, outHi * 1000) / 1000.0;
}
