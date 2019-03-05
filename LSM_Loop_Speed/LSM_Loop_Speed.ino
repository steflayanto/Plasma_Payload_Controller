//Example for performing Loop Speed analysis
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_LSM9DS0.h>
#include <Adafruit_Sensor.h>  
Adafruit_LSM9DS0 lsm = Adafruit_LSM9DS0();


unsigned long timer;

//  'unsigned long' means two things: 

//  in C, 'long' means a big integer (can store MUCH bigger numbers than 'int'). with Arduino, an 'int' uses 2 bytes. and a long uses 4 bytes.

//  'unsigned' means everything is assumed to be positive, and no negative numbers..

//    ...doing this enables you to have a lot more capacity, because you don't waste a bit to store whether the value is positive or negative.



void setup() {

  Serial.begin(115200); //115k is good
  if (!lsm.begin())
  {
    Serial.println("Oops ... unable to initialize the LSM9DS0. Check your wiring!");
    while (1);
  }
  Serial.println("Hello World");
  //The millis function returns the time that has passed since the program started in milliseconds. millis() returns an unsigned long, so our timer has to be an unsigned long too.

  timer = millis();

  //When starting, set timer equal to millis()
    // 1.) Set the accelerometer range
  lsm.setupAccel(lsm.LSM9DS0_ACCELRANGE_2G);
//  lsm.setupAccel(lsm.LSM9DS0_ACCELRANGE_4G);
//  lsm.setupAccel(lsm.LSM9DS0_ACCELRANGE_6G);
//  lsm.setupAccel(lsm.LSM9DS0_ACCELRANGE_8G);
//  lsm.setupAccel(lsm.LSM9DS0_ACCELRANGE_16G);
  
  // 2.) Set the magnetometer sensitivity
  lsm.setupMag(lsm.LSM9DS0_MAGGAIN_2GAUSS);
//  lsm.setupMag(lsm.LSM9DS0_MAGGAIN_4GAUSS);
//  lsm.setupMag(lsm.LSM9DS0_MAGGAIN_8GAUSS);
//  lsm.setupMag(lsm.LSM9DS0_MAGGAIN_12GAUSS);

  // 3.) Setup the gyroscope
  lsm.setupGyro(lsm.LSM9DS0_GYROSCALE_245DPS);
//  lsm.setupGyro(lsm.LSM9DS0_GYROSCALE_500DPS);
//  lsm.setupGyro(lsm.LSM9DS0_GYROSCALE_2000DPS);

}


void loop() {

  lsm.read();

  unsigned long loopTime = millis() - timer; //time that has passed since last loop is the current 'millis()' value subtracted by the previous millis() value which we saved in 'timer'

  Serial.println("loop took " + String(loopTime) + " milliseconds."); //Print that value to the monitor

  timer = millis();  //Update the timer to be the current millis value

//  Serial.print("Temp: "); Serial.print((int)lsm.temperature);    Serial.println(" ");


  //The rest of the code goes here
  
  

}
