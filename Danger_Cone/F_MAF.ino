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
