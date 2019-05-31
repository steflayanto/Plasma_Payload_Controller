#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <Adafruit_LSM9DS0.h>
#include <Adafruit_Sensor.h>  // not used in this demo but required!

//i2c
Adafruit_LSM9DS0 lsm = Adafruit_LSM9DS0();
//sensors_event_t accel, mag, gyro, temp;

//variables
int flightStage = 0;
/*  Flight stages:
    0: pre-launch
    1: engine-burn
    2: early-coast-phase
    3: late-coast-phase
    4: descent
*/
double maxDrag = 0;
boolean isSafe = true;
unsigned long startTime = 0;

//constants
const float noiseBuffer = 0.5; //arbitrary value for now

const int chipSelect = 4;
String file_name = "imu.csv";

void setup() {
  Serial.begin(115200);
  while (!Serial) {
    ;     // will pause until serial console opens
  }
  
  Serial.print("Initializing SD card...");
  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    while (1);
  }
  Serial.println("card initialized.");
  printLegend();
  setupLSM();
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

void loop() {
  lsm.read();
  //lsm.getEvent(&accel, &mag, &gyro, &temp);
  float xAccel = lsm.accelData.x;
  float yAccel = lsm.accelData.y;
  float zAccel = lsm.accelData.z;
//  float zAccel = accel.acceleration.z;

  delay(50); //this delay value can be changed, but might lead to more/less noise
  
  updateMaxDrag(zAccel);
  flightStage = flightStageDecision(zAccel);
  File dataFile = SD.open(file_name, FILE_WRITE);
  if (dataFile) {
    dataFile.print(millis() - startTime);
    dataFile.print(", ");
    dataFile.print(zAccel);
    dataFile.print(", ");
    dataFile.print(flightStage);
    dataFile.print(", ");
    dataFile.print(maxDrag);
    dataFile.print(", ");
    dataFile.print(xAccel);
    dataFile.print(", ");
    dataFile.print(yAccel);
    dataFile.println();
    dataFile.close();
    plotReadings(xAccel, yAccel, zAccel);  
  } else {
    Serial.print(zAccel);
    Serial.print('\t');
    Serial.print(flightStage);
    Serial.print('\t');
    Serial.println("Error opening file for logging");
  }
  //logData(zAccel, flightStage, maxDrag, xAccel, yAccel);
  
}
