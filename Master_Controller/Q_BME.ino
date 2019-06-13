#define FACTOR 0.2f
#define LOW_BURN 10
#define LOW_EARLY 20 // equiv HIGH_BURN
#define LOW_LATE 30  // equiv HIGH_EARLY
#define HIGH_LATE 50

#define SEALEVELPRESSURE_HPA (1013.25)

void initBME() {
  //in setup
  //Serial.begin(9600);
  Serial.println(F("BME280 test"));

  if (!bme.begin()) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }
  initMAF();
}

float bmeDecision() {
  //map to flight stages, mapping
  if (alt < LOW_BURN) {
    return 0;
  } else {
    //w/o throttle, burn = 10 sec = 10000 ft
    //1 burn
    if (alt < LOW_EARLY) {
      return mapFloat(alt, LOW_BURN, LOW_EARLY, 1 - FACTOR, 1 + FACTOR);
    } else if (alt < LOW_LATE) {
      //2 early coast
      return mapFloat(alt, LOW_EARLY, LOW_LATE, 2 - FACTOR, 2 + FACTOR);
    } else if (alt < HIGH_LATE) {
      //3 late coast
      return mapFloat(alt, LOW_LATE, HIGH_LATE, 3 - FACTOR, 3 + FACTOR);
    } else {
      //4 decent = 26067 and down
      return 4.0;//map(alt, 100, 1000, 3, 4);
    }
  }
}

float BMEtemp() {
  return bme.readTemperature();
}

float BMEpressure() {
  return bme.readPressure() / 100.0F; //hPa
}

float BMEalt() {
  return bme.readAltitude(SEALEVELPRESSURE_HPA) - ALT_OFFSET;
}

float BMEhum() {
  return bme.readHumidity();
}

//MAF (Moving Average Filter) FUNCTIONS
// Initializes filter struct
void initMAF() {
  filter.total = 0;
  for (int i = 0; i < MAF_SIZE; i++) {
    filter.arr[i] = 0;
  }
  filter.index = 0;
}

// Updates MAF with a new value
void updateMAF(float newValue) {
  filter.total -= filter.arr[filter.index];
  filter.arr[filter.index] = newValue;
  filter.total += filter.arr[filter.index];
  filter.index = (filter.index + 1) % MAF_SIZE;
}

// Returns current average of filter as output
float getMAFAve() {
  return filter.total / MAF_SIZE; // input for second derivative function
}
