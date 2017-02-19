/** 
 *  \file sensor_sht31.h
 *  \brief Sensor module for air temperature and humidity
 */

// Modified by: Mikael von Ketelhodt

#ifndef SensorSht31_H
#define SensorSht31_H
#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

#include "module_handler.h"
#include "Adafruit_SHT31.h"

/** 
 *  \brief Sensor module for stepper motor.
 */
class SensorSht31 : SensorActuatorModule {
  public:
    // Public Functions
	  SensorSht31();
    void begin();
    String get(void);
    String set(String instruction_code, int instruction_id, String parameter);
    
	float temperature;
	float humidity;

  float temperature2;
  float humidity2;

  private:
	  int currentPin;
	  Adafruit_SHT31 _sht31 = Adafruit_SHT31();
};

#endif // SensorSht31_H_
