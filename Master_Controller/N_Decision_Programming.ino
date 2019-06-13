// Contains code that goes into comparing sensor values and making decision.
short timerStage = 0;
unsigned long launchTime;
boolean launched;

float alt = 0, altMAF = 0;;
unsigned long MAFTimer = 0;

boolean decisionAlgorithm() {
  timerStage = timerUpdate();
  weightedFlightStage = combinedSensorWeight();
  if (timerStage == 0) { //Pre-launch
    return false;
  }else if (timerStage == 4) { //descent: just trigger if still hasn't
    return false;
  }else{
    return weightedFlightStage >= 2;
  }
}

//replace center if else with a weighted average where timer is one of the contributing factors.
//keep timer as bookends

short checkForLaunch() {
  launchTime = millis();
  return 1;
}

short timerUpdate() {
  if (timerStage == 0) {
    return checkForLaunch();
  }
  unsigned long currTime = millis() - launchTime;
  if (currTime > LATE_COAST_TIME) {
    return 4;
  }else if (currTime > EARLY_COAST_TIME) {
    return 3;
  }else if (currTime > ENGINE_BURN_TIME) {
    return 2;
  }else{
    return 1;
  }
}

float combinedSensorWeight() {
  float wt[] = {0.5, 0.1, 0.1, 0.1, 0.2}; // Primary, imu, baro, accel, timer respectively
  return wt[0] * primaryTrigger() + wt[1] * imuTrigger() + wt[2] * baroTrigger() + wt[3] * accelTrigger() + wt[4] * timerStage;
}

//Rename to be actual parameters detected (constant acceleration)
float primaryTrigger() {
  return 1;
}

float imuTrigger() {
  return 1;
}

float baroTrigger() {
  return bmeDecision();
}

float accelTrigger() {
  return 1;
}

void updateTrackedValues() {
  //BME
  alt = BMEalt();
  updateMAF(alt);
  altMAF = getMAFAve();
}
