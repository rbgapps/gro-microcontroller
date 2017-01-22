/** 
 *  \file sensor_tentacle.h
 *  \brief Sensor module for tentacle shield (liquid temperature, PH, EC and DO)
 */

// Modified by: Mikael von Ketelhodt

#ifndef SensorTentacle_H
#define SensorTentacle_H
#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

#include "module_handler.h"
#include "support_software_serial.h" 

/** 
 *  \brief Sensor module for air temperature and humidity.
 */
class SensorTentacle : SensorActuatorModule {
  public:
    // Public Functions
    SensorTentacle(char);
    void begin(void);
    String get(void);
    String set(String instruction_code, int instruction_id, String parameter);

    // Public Variables
    float doValue;
    float liquidTemperatureValue;
    float ecValue;
    float phValue;
    
  private:
    // Private Functions
	void updateChannel();
	String processChannelMessage(String message);

    SoftwareSerial *_ss;             // RX, TX  - Name the software serial library sftSerial (this cannot be omitted) assigned to pins 10 and 11 for maximum compatibility
    int _softwareSerialPin0;         // Tentacle uses pin 7 for multiplexer control S0
    int _softwareSerialPin1;         // Tentacle uses pin 6 for multiplexer control S1
    int _enable1;                    // Tentacle uses pin 5 to control pin E on shield 1
    int _enable2;                    // Tentacle uses pin 4 to control pin E on shield 2

    char _channel;                      // Char pointer used in string parsing
};

#endif // SensorTentacle_H_
