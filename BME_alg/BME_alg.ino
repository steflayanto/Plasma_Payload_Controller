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

float alt;

void setup() {
    Serial.begin(9600);
    Serial.println(F("BME280 test"));

    bool status;
    
    // default settings
    // (you can also pass in a Wire library object like &Wire2)
    status = bme.begin();  
    if (!status) {
        Serial.println("Could not find a valid BME280 sensor, check wiring!");
        while (1);
    }

    Serial.println();
}

void loop() {
  alt = bme.readAltitude(SEALEVELPRESSURE_HPA);
  Serial.println(alt); 
  //Serial.println(bmeDecision()); 
}

int bmeDecision(){
  // pull alt
  alt = bme.readAltitude(SEALEVELPRESSURE_HPA);
  //map to flight stages, mapping
  if (alt < 100){
    return 0;
  } else{
    //w/o throttle, burn = 10 sec = 10000 ft
    //1 burn
    map(alt, 100, 10000, 0, 1);
    //2 early coast
    map(alt, 100, 1000, 1, 2);
    //3 late coast
    map(alt, 100, 1000, 2, 3);
    //4 decent = 26067 and down
    map(alt, 100, 1000, 3, 4);
    
    //w/ throttle burn = 21 sec = 15000
    //1 burn
    map(alt, 100, 15000, 0, 1);
    //2 early coast
    map(alt, 100, 1000, 1, 2);
    //3 late coast
    map(alt, 100, 1000, 2, 3);
    //4 decent = 27700 and down
    map(alt, 100, 1000, 3, 4);
}
}