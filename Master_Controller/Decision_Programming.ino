// Contains code that goes into comparing sensor values and making decision.
short timerStage = 0;

boolean decisionAlgorithm() {
  if (timerStage == 0) { //Pre-launch
    return false;
  }else if (timerStage >= 4) { //descent: just trigger if still hasn't
    return false;
  }else{
    return weightedFlightStage >= 2;
  }
}

//replace center if else with a weighted average where timer is one of the contributing factors.
//keep timer as bookends

//Rename to be actual parameters detected (constant acceleration)
float primaryTrigger() {
  return false;
}

float imuTrigger() {
  return true;
}

float baroTrigger() {
  return true;
}

float accelTrigger() {
  return false;
}

//  }else if (timerStage == 1) { //engine-burn: all must trigger
//    return primaryTrigger() && imuTrigger() && baroTrigger() && accelTrigger();
//  }else if (timerStage == 2) { //early-coast-phase: primary triggers, or 2/3 secondary sensors trigger
//    return primaryTrigger() || ((int) imuTrigger() + (int) baroTrigger() + (int) accelTrigger() > 1);
//  }else if (timerStage == 3) { //late-coast-phase: any sensors can trigger
//    return primaryTrigger() || imuTrigger() || baroTrigger() || accelTrigger();
