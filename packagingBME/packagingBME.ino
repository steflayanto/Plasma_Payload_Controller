#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define BME_SCK 13
#define BME_MISO 12
#define BME_MOSI 11
#define BME_CS 10

#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME280 bme; // I2C

void initBME() {
  //in setup
  Serial.begin(9600);
  Serial.println(F("BME280 test"));

  bool status;

  status = bme.begin();
  if (!status) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }

}

float BMEtemp() {
  float val = bme.readTemperature();
  return val;
}

float BMEpres() {
  float val = bme.readPressure() / 100.0F;
  return val;
}

float BMEalt() {
  float val = bme.readAltitude(SEALEVELPRESSURE_HPA);
  return val;
}

float BMEhum() {
  float val = bme.readHumidity();
  return val;
}

//copy whole thing
//global var, copy only calll funtion
//global var go on top of sensors
//update header
