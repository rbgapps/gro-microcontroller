/** 
 *  \file sensor_stepper.cpp
 *  \brief Sensor module for stepper
 *  \details See sensor_stepper.h for details.
 */
#include "sensor_sht31.h"

SensorSht31::SensorSht31() {
	temperature = -1000;
	humidity = -1000;
}

void SensorSht31::begin() {
	if (!_sht31.begin()) { 
		temperature = -1000;
		humidity = -1000;
		Serial.println("Not found...");
	}

  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  
  currentPin = 2;
  digitalWrite(2, LOW); // sets this temperature sensor as the next one to read
  digitalWrite(3, HIGH); 
}

String SensorSht31::get(void) {

  float t = _sht31.readTemperature();
  float h = _sht31.readHumidity();

  String message = "";
  
  if (currentPin == 2) {
  
    //message += t + h;
  
    if (!isnan(t)) {
      temperature = t;
    }
    else {
      temperature = -1000;
    }
  
    if (!isnan(h)) {
      humidity = h;
    }
    else {
      humidity = -1000;
    }
  
    digitalWrite(2, HIGH);
    digitalWrite(3, LOW); // sets this temperature sensor as the next one to read
    currentPin = 3;
 } else {

    //message += t + h;
  
    if (!isnan(t)) {
      temperature2 = t;
    }
    else {
      temperature2 = -1000;
    }
  
    if (!isnan(h)) {
      humidity2 = h;
    }
    else {
      humidity2 = -1000;
    }
  
    digitalWrite(2, LOW); // sets this temperature sensor as the next one to read
    digitalWrite(3, HIGH); 
    currentPin = 2;
 }  

    message += "\"";
    message += "TEMP1";  
    message += "\":";
    message += String(temperature);
    message += ",";
  
    message += "\"";
    message += "HUMID1";
    message += "\":";
    message += String(humidity);
    message += ",";

    message += "\"";
    message += "TEMP2";  
    message += "\":";
    message += String(temperature2);
    message += ",";
  
    message += "\"";
    message += "HUMID2";
    message += "\":";
    message += String(humidity2);
    message += ",";

	// Return Message
	return message;
}

String SensorSht31::set(String instruction_code, int instruction_id, String parameter) {
	return "";
}
