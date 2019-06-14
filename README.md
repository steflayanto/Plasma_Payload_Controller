# Plasma-Payload_Controller
Microcontroller for SARP UW's experimental plasma actuator payload. Tasked with detecting engine shut-off, activation of payload, and logging.

# Required Libraries (From Arduino Library manager)
 - <Adafruit_Sensor.h>
 - <Adafruit_LSM9DS0.h>
 - <Adafruit_BME280.h>
 - <SparkFunTMP102.h> (Included as a zip file in the repo)
 - <Adafruit_Simple_AHRS.h>
 - <Adafruit_ADS1015.h>

# Required Boards (in Arduino IDE Board Manager)
 - Arduino SAMD
 - Adafruit SAMD (Requires additional steps: https://learn.adafruit.com/add-boards-arduino-v164/setup)