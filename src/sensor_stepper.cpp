/** 
 *  \file sensor_stepper.cpp
 *  \brief Sensor module for stepper
 *  \details See sensor_stepper.h for details.
 */
#include "sensor_stepper.h"

SensorStepper::SensorStepper(int steps, int pin1, int pin2): _stepper(steps, pin1, pin2) {
	_steps = steps;
	_pin1 = pin1;
	_pin2 = pin2;
	_speed = 10;
}

void SensorStepper::begin(void) {
	_stepper.setSpeed(_speed);
}

String SensorStepper::get(void) {

	String message = "";

	message += "\"";
	message += "STEP_SPEED";
	message += "\":";
	message += String(_speed);
	message += ",";

	// Return Message
	return message;
}

String SensorStepper::set(String instruction_code, int instruction_id, String parameter) {

	String response = "";

	if (instruction_code == "STEP" && instruction_id == 0) {
		step(parameter.toInt());

		response += "\"";
		response += "STEP_SPEED";
		response += "\":";
		response += String(_speed);
		response += ",";

		response += "\"";
		response += "STEP_COUNT";
		response += "\":";
		response += parameter;
		response += ",";

		return response;
	}

	if (instruction_code == "STEP" && instruction_id == 1) {
		setSpeed(parameter.toInt());

		response += "\"";
		response += "STEP_SPEED";
		response += "\":";
		response += String(_speed);
		response += ",";

		return response;
	}
}

void SensorStepper::setSpeed(int speed) {
  _speed = speed;
	_stepper.setSpeed(_speed);
}

void SensorStepper::step(int stepCount) {
	_stepper.step(stepCount);
}
