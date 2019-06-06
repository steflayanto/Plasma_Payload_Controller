#include <SPI.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM9DS0.h>
#include <Adafruit_Simple_AHRS.h>

Adafruit_LSM9DS0 lsm(1000);
Adafruit_Simple_AHRS ahrs(&lsm.getAccel(), &lsm.getMag());

#define MAF_SIZE 10 // number of samples for the running avg
struct {
  float total;
  float arr[MAF_SIZE];
  int index;
} filter;

void setup() {
    initCone();
}

void loop() {
    updateCone();
}

void initCone() {
    initLSM();
    initMAF();
}

void updateCone() {
    sensors_vec_t orientation;
    if (ahrs.getOrientation(&orientation)) {
        float heading = pow(pow(orientation.roll, 2) + pow(orientation.pitch, 2)), 1/2)
        updateMAF(heading)
        if (getMAFAve()) > 50.0) {
            // Shut off
        }
    }
}

