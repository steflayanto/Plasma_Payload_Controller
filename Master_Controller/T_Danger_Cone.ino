void updateCone() {
  sensors_vec_t orientation;
  if (ahrs.getOrientation(&orientation)) {
    
    double rollSq = pow(invert(orientation.roll), 2.0);
    double pitchSq = pow(orientation.pitch, 2.0);
    double tot = rollSq + pitchSq;
    double heading = pow(tot, 0.5);
    updateConeMAF(heading);
    if (getConeMAFAve() > dangerAngle) {
      inCone = false;
      digitalWrite(13, HIGH);
    } else {
      inCone = true;
      digitalWrite(13, LOW);
    }
//    Serial.print(invert(orientation.roll));
//    Serial.print(",");
//    Serial.print(orientation.pitch);
//    Serial.print(",");
//    Serial.print(heading);
//    Serial.println();
  }
}


// Adds 180 to an euler value, and wraps to +-180. Assumes input is within +-180
double invert(double input) {
  if (input >= 0) {
    return input - 180;
  }else{ //if less than 0
    return input + 180;
  }
}

// Initializes filter struct
void initConeMAF() {
  coneFilter.total = 0;
  for (int i = 0; i < MAF_SIZE; i++) {
    coneFilter.arr[i] = 0;
  }
  coneFilter.index = 0;
}

// Updates MAF with a new value
void updateConeMAF(float newValue) {
  coneFilter.total -= coneFilter.arr[coneFilter.index];
  coneFilter.arr[coneFilter.index] = newValue;
  coneFilter.total += coneFilter.arr[coneFilter.index];
  coneFilter.index = (coneFilter.index + 1) % MAF_SIZE;
}

// Returns current average of filter as output
float getConeMAFAve() {
  return coneFilter.total / MAF_SIZE; // input for second derivative function
}
