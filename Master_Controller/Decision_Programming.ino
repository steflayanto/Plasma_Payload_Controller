// Contains code that goes into comparing sensor values and making decision.

boolean decisionAlgorithm() {
  if (flightStage == 0) { //Pre-launch
    return false;
  }else if (flightStage == 1) { //engine-burn: all must trigger
    return primaryTrigger() && imuTrigger() && baroTrigger() && accelTrigger();
  }else if (flightStage == 2) { //early-coast-phase: primary triggers, or 2/3 secondary sensors trigger
    return primaryTrigger() || ((int) imuTrigger() + (int) baroTrigger() + (int) accelTrigger() > 1);
  }else if (flightStage == 3) { //late-coast-phase: any sensors can trigger
    return primaryTrigger() || imuTrigger() || baroTrigger() || accelTrigger();
  }else if (flightStage >= 4) { //descent: just trigger if still hasn't
    return false;
  }
}

boolean primaryTrigger() {
  return false;
}

boolean imuTrigger() {
  return true;
}

boolean baroTrigger() {
  return true;
}

boolean accelTrigger() {
  return false;
}
