/** 
 *  \file module_handler.cpp
 *  \brief Handles all module integration. 
 *  \details See module_handler.h for details.
 *  \author Jake Rye
 */
#include "module_handler.h"

// Include Module Libraries
#include "communication.h"
//#include "sensor_dfr0161_0300.h"
/*
#include "sensor_vernier_ph.h"
#include "sensor_vernier_ec.h"
#include "sensor_ds18b20.h"
#include "sensor_tsl2561.h"
#include "sensor_dht22.h"
#include "sensor_gc0011.h"
#include "actuator_relay.h"
#include "sensor_contact_switch.h"
*/
#include "sensor_tentacle.h"
#include "sensor_stepper.h"
#include "sensor_sht31.h"
#include "sensor_relay.h"

// Declare Module Objects
Communication communication;

SensorTentacle sensorTentacle('1');
SensorStepper sensorStepper(200, 9, 8);
SensorSht31 sensorSht31 = SensorSht31();

SensorRelay relay1 = SensorRelay(22, 1);
SensorRelay relay2 = SensorRelay(23, 2);
SensorRelay relay3 = SensorRelay(24, 3);
SensorRelay relay4 = SensorRelay(25, 4);
SensorRelay relay5 = SensorRelay(26, 5);
SensorRelay relay6 = SensorRelay(27, 6);
SensorRelay relay7 = SensorRelay(28, 7);
SensorRelay relay8 = SensorRelay(29, 8);
SensorRelay relay9 = SensorRelay(30, 9);
SensorRelay relay10 = SensorRelay(31, 10);
SensorRelay relay11 = SensorRelay(32, 11);
SensorRelay relay12 = SensorRelay(33, 12);
SensorRelay relay13 = SensorRelay(34, 13);
SensorRelay relay14 = SensorRelay(35, 14);
SensorRelay relay15 = SensorRelay(36, 15);
SensorRelay relay16 = SensorRelay(37, 16);
SensorRelay relay17 = SensorRelay(38, 17);
SensorRelay relay18 = SensorRelay(39, 18);
SensorRelay relay19 = SensorRelay(40, 19);
SensorRelay relay20 = SensorRelay(41, 20);
SensorRelay relay21 = SensorRelay(42, 21);
SensorRelay relay22 = SensorRelay(43, 22);
SensorRelay relay23 = SensorRelay(44, 23);
SensorRelay relay24 = SensorRelay(45, 24);
SensorRelay relay25 = SensorRelay(46, 25);
SensorRelay relay26 = SensorRelay(47, 26);
SensorRelay relay27 = SensorRelay(48, 27);
SensorRelay relay28 = SensorRelay(49, 28);
SensorRelay relay29 = SensorRelay(50, 29);
SensorRelay relay30 = SensorRelay(51, 30);
SensorRelay relay31 = SensorRelay(52, 31);
SensorRelay relay32 = SensorRelay(53, 32);
SensorRelay relay33 = SensorRelay(A8, 33);
SensorRelay relay34 = SensorRelay(A9, 34);
SensorRelay relay35 = SensorRelay(A10, 35);
SensorRelay relay36 = SensorRelay(A11, 36);
SensorRelay relay37 = SensorRelay(A12, 37);
SensorRelay relay38 = SensorRelay(A13, 38);
SensorRelay relay39 = SensorRelay(A14, 39);
SensorRelay relay40 = SensorRelay(A15, 40);

void initializeModules(void) { 
  communication.begin();

  sensorTentacle.begin();
  sensorStepper.begin();
  sensorSht31.begin();
  
  relay1.begin();
  relay2.begin();
  relay3.begin();
  relay4.begin();
  relay5.begin();
  relay6.begin();
  relay7.begin();
  relay8.begin();
  relay9.begin();
  relay10.begin();
  relay11.begin();
  relay12.begin();
  relay13.begin();
  relay14.begin();
  relay15.begin();
  relay16.begin();
  relay17.begin();
  relay18.begin();
  relay19.begin();
  relay20.begin();
  relay21.begin();
  relay22.begin();
  relay23.begin();
  relay24.begin();
  relay25.begin();
  relay26.begin();
  relay27.begin();
  relay28.begin();
  relay29.begin();
  relay30.begin();
  relay31.begin();
  relay32.begin();
  relay33.begin();
  relay34.begin();
  relay35.begin();
  relay36.begin();
  relay37.begin();
  relay38.begin();
  relay39.begin();
  relay40.begin();
}

void updateIncomingMessage(void) {
  // Check for Message(s) And Handle If Necessary
  String response_message = "";
  while (communication.available()) { // read in message(s) until nothing in serial buffer
    response_message += handleIncomingMessage();
  }
  // Append Responses From Message(s) Then Send
  if (response_message != "") {
    response_message = "\"GTYP\":\"Response\"," + response_message;
    response_message += "\"GEND\":0";
    communication.send(response_message);
  }
}

void updateStreamMessage(void) {
  // Initialize Stream Message
  String stream_message = "\"GTYP\":\"Stream\",";
  
  stream_message += sensorTentacle.get();
  stream_message += sensorStepper.get();
  stream_message += sensorSht31.get();

  // Return Stream Message
  stream_message += "\"GEND\":0";

  // Send Stream Message
  communication.send(stream_message);
}

String handleIncomingMessage(void) {
  // Parse Message into: Instruction Code - ID - Parameter
  String return_message = "";
  String incoming_message = communication.receive();
  //Serial.println(incoming_message);
  Instruction instruction = parseIncomingMessage(incoming_message);
  //Serial.println(instruction.code);
  //Serial.println(instruction.id);
  //Serial.println(instruction.parameter);
  //Serial.println(instruction.valid);

  // Pass Parsed Message To All Objects and Update Return Message if Applicable
  if (instruction.valid) {
    return_message += sensorTentacle.set(instruction.code, instruction.id, instruction.parameter);
	  return_message += sensorStepper.set(instruction.code, instruction.id, instruction.parameter);
	  return_message += sensorSht31.set(instruction.code, instruction.id, instruction.parameter);

    return_message += SensorRelay::setBulk(instruction.code, instruction.id, instruction.parameter);

    /*
    return_message += relay1.set(instruction.code, instruction.id, instruction.parameter);
    return_message += relay2.set(instruction.code, instruction.id, instruction.parameter);
    return_message += relay3.set(instruction.code, instruction.id, instruction.parameter);
    return_message += relay4.set(instruction.code, instruction.id, instruction.parameter);
    return_message += relay5.set(instruction.code, instruction.id, instruction.parameter);
    return_message += relay6.set(instruction.code, instruction.id, instruction.parameter);
    return_message += relay7.set(instruction.code, instruction.id, instruction.parameter);
    return_message += relay8.set(instruction.code, instruction.id, instruction.parameter);
    return_message += relay9.set(instruction.code, instruction.id, instruction.parameter);
    return_message += relay10.set(instruction.code, instruction.id, instruction.parameter);
    return_message += relay11.set(instruction.code, instruction.id, instruction.parameter);
    return_message += relay12.set(instruction.code, instruction.id, instruction.parameter);
    return_message += relay13.set(instruction.code, instruction.id, instruction.parameter);
    return_message += relay14.set(instruction.code, instruction.id, instruction.parameter);
    return_message += relay15.set(instruction.code, instruction.id, instruction.parameter);
    return_message += relay16.set(instruction.code, instruction.id, instruction.parameter);
    return_message += relay17.set(instruction.code, instruction.id, instruction.parameter);
    return_message += relay18.set(instruction.code, instruction.id, instruction.parameter);
    return_message += relay19.set(instruction.code, instruction.id, instruction.parameter);
    return_message += relay20.set(instruction.code, instruction.id, instruction.parameter);
    return_message += relay21.set(instruction.code, instruction.id, instruction.parameter);
    return_message += relay22.set(instruction.code, instruction.id, instruction.parameter);
    return_message += relay23.set(instruction.code, instruction.id, instruction.parameter);
    return_message += relay24.set(instruction.code, instruction.id, instruction.parameter);
    return_message += relay25.set(instruction.code, instruction.id, instruction.parameter);
    return_message += relay26.set(instruction.code, instruction.id, instruction.parameter);
    return_message += relay27.set(instruction.code, instruction.id, instruction.parameter);
    return_message += relay28.set(instruction.code, instruction.id, instruction.parameter);
    return_message += relay29.set(instruction.code, instruction.id, instruction.parameter);
    return_message += relay30.set(instruction.code, instruction.id, instruction.parameter);
    return_message += relay31.set(instruction.code, instruction.id, instruction.parameter);
    return_message += relay32.set(instruction.code, instruction.id, instruction.parameter);
    return_message += relay33.set(instruction.code, instruction.id, instruction.parameter);
    return_message += relay34.set(instruction.code, instruction.id, instruction.parameter);
    return_message += relay35.set(instruction.code, instruction.id, instruction.parameter);
    return_message += relay36.set(instruction.code, instruction.id, instruction.parameter);
    return_message += relay37.set(instruction.code, instruction.id, instruction.parameter);
    return_message += relay38.set(instruction.code, instruction.id, instruction.parameter);
    return_message += relay39.set(instruction.code, instruction.id, instruction.parameter);
    return_message += relay40.set(instruction.code, instruction.id, instruction.parameter);
    */
  }
  return return_message;
}

Instruction parseIncomingMessage(String message) {
  // Initialize Instruction
  Instruction instruction;
  instruction.valid = 0;

  // Get Instruction Data
  int len = message.length();
  int first_space = message.indexOf(" ");
  if ((first_space > 0) && (len > first_space)) {
    int second_space = message.indexOf(" ", first_space + 1);
    if ((second_space > 0) && (second_space < len - 1)) {
      // Received good message
      instruction.code = message.substring(0, 4);
      instruction.id = (message.substring(first_space, second_space)).toInt();
      instruction.parameter = message.substring(second_space + 1, len);
      instruction.valid = 1;
    }
  }

  // Return Instruction Data
  return instruction;
}

