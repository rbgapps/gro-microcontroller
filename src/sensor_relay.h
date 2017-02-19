/** 
 *  \file sensor_relay.h
 *  \brief Sensor module for a relay.
 *  \author Mikael von Ketelhodt
 */
#ifndef SENSOR_RELAY_H
#define SENSOR_RELAY_H

#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

#include "module_handler.h"

/** 
 *  \brief Sensor module for a relay.
 */
class SensorRelay : SensorActuatorModule {
  public:
    // Public Functions
    SensorRelay(int pin, int instruction_id);
    void begin(void); 
    String get(void); 
    String set(String instruction_code, int instruction_id, String instruction_parameter);

    // Public Variables
    bool is_connected_;
    
  private:
    // Private Functions
    bool getData(void);
    
    // Private Variables
    int _pin;
    int _instruction_id;
};

#endif // SENSOR_RELAY_H_

