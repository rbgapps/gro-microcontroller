/** 
 *  \file sensor_stepper.h
 *  \brief Sensor module for stepper motor
 */

// Modified by: Mikael von Ketelhodt

#ifndef SensorStepper_H
#define SensorStepper_H
#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

#include "module_handler.h"
#include <Stepper.h>

/** 
 *  \brief Sensor module for stepper motor.
 */
class SensorStepper : SensorActuatorModule {
  public:
    // Public Functions
	SensorStepper(int steps, int pin1, int pin2);
    void begin(void);
    String get(void);
    String set(String instruction_code, int instruction_id, String parameter);
    
  private:
    // Private Functions
	void setSpeed(int speed);
	void step(int stepCount);
	
	Stepper _stepper; // TODO: Instantiate properly...

	int _steps;
	int _pin1;
	int _pin2;
	int _speed;
};

#endif // SensorStepper_H_