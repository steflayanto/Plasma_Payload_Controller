// For integration: move in with MAF sketch/struct, uncomment initLSM(), take out printlns, change MAF_SIZE

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM9DS0.h>
#include <Adafruit_Simple_AHRS.h>

#define MAF_SIZE 10 // number of samples for the running avg
//^^^^^ VALUE IS TOTALLY ARBITRARY IDK WHAT A GOOD SIZE FOR MAF IS DEPNDS ON HOW QUICK YOU WANT OT UPDATE PROBABLY WANT SIZE >=5 AT LEAST
struct {
  float total;
  float arr[MAF_SIZE];
  int index;
} filter;

Adafruit_LSM9DS0 lsm(1000);
Adafruit_Simple_AHRS ahrs(&lsm.getAccel(), &lsm.getMag());

double dangerAng = 33.0; // Highly arbitrary value
void setup() {
  Serial.begin(9600);
  initCone();
}

void loop() {
  
  updateCone();
  delay(100); 
}


void initCone() {
  //initLSM();
  if(!lsm.begin()) {
    Serial.println("shit");
  }
  lsm.setupAccel(lsm.LSM9DS0_ACCELRANGE_2G);
  lsm.setupMag(lsm.LSM9DS0_MAGGAIN_2GAUSS);
  lsm.setupGyro(lsm.LSM9DS0_GYROSCALE_245DPS);
  initMAF();
}

void updateCone() {
  sensors_vec_t orientation;
  if (ahrs.getOrientation(&orientation)) {
    double rollSq = pow(orientation.roll, 2.0);
    double pitchSq = pow(orientation.pitch, 2.0);
    double tot = rollSq + pitchSq;
    double heading = pow(tot, 0.5);
    updateMAF(abs(180 - heading));
    Serial.print(abs(180 - heading));
    Serial.println();
    if (getMAFAve() > dangerAng) {
      digitalWrite(13, HIGH);
    } else {
      digitalWrite(13, LOW);
    }
  }
}
