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

float temp, pressure, alt, hum;

//Example for performing Loop Speed analysis

unsigned long timer;
//  'unsigned long' means two things: 
//  in C, 'long' means a big integer (can store MUCH bigger numbers than 'int'). with Arduino, an 'int' uses 2 bytes. and a long uses 4 bytes.
//  'unsigned' means everything is assumed to be positive, and no negative numbers..
//    ...doing this enables you to have a lot more capacity, because you don't waste a bit to store whether the value is positive or negative.

void setup() {
   Serial.begin(74880);
  //The millis function returns the time that has passed since the program started in milliseconds. millis() returns an unsigned long, so our timer has to be an unsigned long too.
   timer = millis();
  //When starting, set timer equal to millis()
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
//  unsigned long loopTime = millis() - timer; //time that has passed since last loop is the current 'millis()' value subtracted by the previous millis() value which we saved in 'timer'
//  Serial.println("loop took " + String(loopTime) + " milliseconds."); //Print that value to the monitor
//  timer = millis();  //Update the timer to be the current millis value

  //The rest of the code goes here


    temp = bme.readTemperature();

    pressure = bme.readPressure() / 100.0F; //hPa
   
    alt = bme.readAltitude(SEALEVELPRESSURE_HPA);

    hum = bme.readHumidity();


    Serial.println();
  
}
