#include "Header.h"

//Global Variables
boolean activated = false;  // Stores whether plasma has already been activated
int flightStage = 0;      // Stores expected flight stage:
                          /*  Flight stages:
                           *  0: pre-launch
                           *  1: engine-burn
                           *  2: coast-phase
                           *  3: apogee
                           *  4: descent
                           */
//Sensor Objects
Adafruit_LSM9DS0 lsm = Adafruit_LSM9DS0();

void setup() {
#ifndef ESP8266
  while (!Serial);     // For running on ESP boards. Will pause until serial console opens
#endif
  Serial.begin(116200);
  initSensors();
}

void loop() {
  updateSensors();
  transmitToLogger();
  updateFlightStage();
  if (activated) {
    return; //if already running, don't do anything below
  }
  if (triggerConditionsMet()) {
    activatePlasma();
    activated = true;;
  }
}


//Performs all initialization of sensors
void initSensors() {
  //put all sensor initialization code here
}

//Performs all sensor updates
void updateSensors() {
  //put all sensor initialization code here
}

//Interacts with slave logger device
void updateFlightStage() {
  //put all sensor initialization code here
}

//Interacts with slave logger device
void transmitToLogger() {
  //put all sensor initialization code here
}

//Decides whether to activate plasma
boolean triggerConditionsMet() {
  //Code will consider sensor data and flight stage and make a decision
}

//Activates Plasma Payload
boolean activatePlasma() {
  //Code will consider
}
