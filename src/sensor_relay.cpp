/** 
 *  \file sensor_relay.cpp
 *  \brief Sensor module for a Relay.
 *  \author Mikael von Ketelhodt
 */
#include "sensor_relay.h"

//--------------------------------------------------PUBLIC-------------------------------------------//
SensorRelay::SensorRelay(int pin, int instruction_id) {
 _pin = pin;
 _instruction_id = instruction_id;
}

void SensorRelay::begin(void) {
 pinMode(_pin, OUTPUT);
 digitalWrite(_pin, HIGH);
}

String SensorRelay::get(void) {
  /*
  // Get Sensor Data
  _is_connected = getData();

  // Initialize Message
  String message = "";

  // Append Actuator State
  message += "REL_";
  message += _instruction_id;
  message += ":";
  message += _is_connected;
  message += ",";

  // return "";
  return message;
  */
  return "";
}

String SensorRelay::set(String instruction_code, int instruction_id, String instruction_parameter) {

  String response = "";

  if (instruction_code != "RELA") {
    return response;
  }

  if (instruction_id != _instruction_id) {
    return response;
  }
  
  if (instruction_parameter == "ON") {
    digitalWrite(_pin, LOW);

    response += "\"";
    response += "RON";
    response += "\":";
    response += instruction_id;
    response += ",";
  }

  if (instruction_parameter == "OFF") {
    digitalWrite(_pin, HIGH);

    response += "\"";
    response += "ROFF";
    response += "\":";
    response += instruction_id;
    response += ",";
  }
  
  return response;
}

//-------------------------------------------------PRIVATE-------------------------------------------//
bool SensorRelay::getData(void) {
  return digitalRead(_pin);
}

