#include <Wire.h>
#include <SPI.h>
#include <Adafruit_LSM9DS0.h>
#include <Adafruit_Sensor.h>  // not used in this demo but required!

/*  Flight stages:
                           *  0: pre-launch
                           *  1: engine-burn
                           *  2: early-coast-phase
                           *  3: late-coast-phase
                           *  4: descent
*/

// i2c
Adafruit_LSM9DS0 lsm = Adafruit_LSM9DS0();

// You can also use software SPI
//Adafruit_LSM9DS0 lsm = Adafruit_LSM9DS0(13, 12, 11, 10, 9);
// Or hardware SPI! In this case, only CS pins are passed in
//Adafruit_LSM9DS0 lsm = Adafruit_LSM9DS0(10, 9);

void setupSensor()
{
  // 1.) Set the accelerometer range
  lsm.setupAccel(lsm.LSM9DS0_ACCELRANGE_2G);
  //lsm.setupAccel(lsm.LSM9DS0_ACCELRANGE_4G);
  //lsm.setupAccel(lsm.LSM9DS0_ACCELRANGE_6G);
  //lsm.setupAccel(lsm.LSM9DS0_ACCELRANGE_8G);
  //lsm.setupAccel(lsm.LSM9DS0_ACCELRANGE_16G);
  
  // 2.) Set the magnetometer sensitivity
  lsm.setupMag(lsm.LSM9DS0_MAGGAIN_2GAUSS);
  //lsm.setupMag(lsm.LSM9DS0_MAGGAIN_4GAUSS);
  //lsm.setupMag(lsm.LSM9DS0_MAGGAIN_8GAUSS);
  //lsm.setupMag(lsm.LSM9DS0_MAGGAIN_12GAUSS);

  // 3.) Setup the gyroscope
  lsm.setupGyro(lsm.LSM9DS0_GYROSCALE_245DPS);
  //lsm.setupGyro(lsm.LSM9DS0_GYROSCALE_500DPS);
  //lsm.setupGyro(lsm.LSM9DS0_GYROSCALE_2000DPS);
}

void setup() 
{
#ifndef ESP8266
  while (!Serial);     // will pause Zero, Leonardo, etc until serial console opens
#endif
  Serial.begin(9600);
  Serial.println("LSM raw read demo");
  
  // Try to initialise and warn if we couldn't detect the chip
  if (!lsm.begin())
  {
    Serial.println("Oops ... unable to initialize the LSM9DS0. Check your wiring!");
    while (1);
  }
  Serial.println("Found LSM9DS0 9DOF");
  Serial.println("");
  Serial.println("");
}

int flightStage = 0;
boolean activate = false;
boolean safetyEnvelope = true;

void loop() 
{
  lsm.read();

  sensors_event_t accel, mag, gyro, temp;

  lsm.getEvent(&accel, &mag, &gyro, &temp); 
  
  int xAccel = accel.acceleration.x;
  int yAccel = accel.acceleration.y;
  int zAccel = accel.acceleration.z;

  int xMax = 5000; //arbitrary number for now
  int yMax = 5000; 

  
  Serial.print(xAccel); Serial.print(", ");
  Serial.print(yAccel); Serial.print(", ");
  Serial.print(zAccel);
  delay(50);

  //Safety Envelope
  if(xAccel >= xMax || yAccel >= yMax){
    safetyEnvelope = false;
    } 

   //maybe I should change this to <=-12 or something because during burn the IMU will feel multiple g's
   //using near() function you can create a buffer
   if(zAccel == -9.81){ //need to include noise buffer
      flightStage == 0;
    } else if(zAccel < -9.81){
      flightStage == 1;
    } else if(zAccel >= 0){
      flightStage == 2;
    }

    if(flightStage == 2 && safetyEnvelope){
      activate = true;
      }

    Serial.print("     Flight Stage: ");
    Serial.print(flightStage);
    Serial.println();

  
}
