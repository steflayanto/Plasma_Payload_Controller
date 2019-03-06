  #include "Header.h"

//Global Variables
unsigned long launchTime;
boolean activated = false;  // Stores whether plasma has already been activated
float weighedFlightStage = 0;      // Stores expected flight stage:
                          /*  Flight stages:
                           *  0: pre-launch
                           *  1: engine-burn
                           *  2: early-coast-phase
                           *  3: late-coast-phase
                           *  4: apogee
                           */
//Sensor Objects
Adafruit_LSM9DS0 lsm = Adafruit_LSM9DS0();
MPU9250 mpu(Wire,0x68);

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
  if (checkTriggerConditions()) {
    activatePlasma();
    activated = true;
  }
}


//Performs all initialization of sensors
void initSensors() {
  initLSM();
  initBME();
}

//Performs all sensor updates
void updateSensors() {
  updateLSM();
  updateBME();
}

//Makes approximation of timer based on flight stage
void updateFlightStage() {
  if (flightStage == 0) {
    flightStage = checkForLaunch();
    return; //Don't do anything else if haven't launched
  }
  if (millis() - launchTime > DESCENT_TIME) {
    flightStage = 4;
  }else if (millis() - launchTime > APOGEE_TIME) {
    flightStage = 3;
  }else if (millis() - launchTime > ENGINE_CUT_TIME) {
    flightStage = 2;
  }
}

short checkForLaunch() {
  launchTime = millis();
  return 1;
}

//Interacts with slave logger device
void transmitToLogger() {
  
}

//Decides whether to activate plasma (Stefan, Lexie, & Usman)
boolean checkTriggerConditions() {
  //Code will consider sensor data and flight stage and make a decision
  return decisionAlgorithm();
}

//Activates Plasma Payload (Chris & Smriti)
boolean activatePlasma() {
  //Smriti & Chris Phan's code to activate plasma
}
