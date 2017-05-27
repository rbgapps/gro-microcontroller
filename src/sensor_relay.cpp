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
 //Serial.println(String(_pin) + " " + String(_instruction_id) + " LOW");
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

    //Serial.println(String(_pin) + " " + String(_instruction_id) + " LOW");
  }

  if (instruction_parameter == "OFF") {
    digitalWrite(_pin, HIGH);

    response += "\"";
    response += "ROFF";
    response += "\":";
    response += instruction_id;
    response += ",";

    //Serial.println(String(_pin) + " " + String(_instruction_id) + " HIGH");
  }
  
  return response;
}

String SensorRelay::setBulk(String instruction_code, int instruction_id, String instruction_parameter) {

  String response = "";
  
  if (instruction_code != "BULK") {
    return response;
  }

  /*
  if (instruction_id != 1 || instruction_id != 0) {
    return response;
  }
  */

  int strLength = instruction_parameter.length() + 1;
  char strArr[strLength];

  instruction_parameter.toCharArray(strArr, strLength);

  char *p = strArr;
  char *relayNumber;

  while ((relayNumber = strtok_r(p, ",", &p)) != NULL) {
     //Serial.println(relayNumber);

     if (instruction_id == 1) {
       //Serial.println("Turning on " + atoi(relayNumber));
       digitalWrite(atoi(relayNumber), LOW);
     } else {
       //Serial.println("Turning off ");
       digitalWrite(atoi(relayNumber), HIGH);
     }
  }
  
  return response;
}

//-------------------------------------------------PRIVATE-------------------------------------------//
bool SensorRelay::getData(void) {
  return digitalRead(_pin);
}

