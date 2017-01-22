/** 
 *  \file sensor_tentacle.cpp
 *  \brief Sensor module for tentacle shield
 *  \details See sensor_tentacle.h for details.
 */
#include "sensor_tentacle.h"

SensorTentacle::SensorTentacle(char channel) {
  _softwareSerialPin0 = 7;         // Tentacle uses pin 7 for multiplexer control S0
  _softwareSerialPin1 = 6;         // Tentacle uses pin 6 for multiplexer control S1
  _enable1 = 5;                    // Tentacle uses pin 5 to control pin E on shield 1
  _enable2 = 4;                    // Tentacle uses pin 4 to control pin E on shield 2
  _channel = channel;
}

void SensorTentacle::begin(void) {
	pinMode(_softwareSerialPin0, OUTPUT);             // set the digital output pins for the serial multiplexer
	pinMode(_softwareSerialPin1, OUTPUT);
	pinMode(_enable1, OUTPUT);
	pinMode(_enable2, OUTPUT);

	_ss = new SoftwareSerial(11, 10);
	_ss->begin(9600);
}

void SensorTentacle::updateChannel() {

	if (_channel == '0') {
		digitalWrite(_enable1, LOW);
		digitalWrite(_enable2, HIGH);
		digitalWrite(_softwareSerialPin0, LOW);
		digitalWrite(_softwareSerialPin1, LOW);
		return;
	}

	if (_channel == '1') {
		digitalWrite(_enable1, LOW);
		digitalWrite(_enable2, HIGH);
		digitalWrite(_softwareSerialPin0, HIGH);
		digitalWrite(_softwareSerialPin1, LOW);
		return;
	}

	if (_channel == '2') {
		digitalWrite(_enable1, LOW);
		digitalWrite(_enable2, HIGH);
		digitalWrite(_softwareSerialPin0, LOW);
		digitalWrite(_softwareSerialPin1, HIGH);
		return;
	}

	if (_channel == '3') {
		digitalWrite(_enable1, LOW);
		digitalWrite(_enable2, HIGH);
		digitalWrite(_softwareSerialPin0, HIGH);
		digitalWrite(_softwareSerialPin1, HIGH);
		return;
	}

}

String SensorTentacle::processChannelMessage(String message) {
	String response = "";
	//Serial.println(_channel + " " + message);
	float value = message.toFloat(); // returns 0 if not parsable

	response += "\"";
	response += "DO";
	response += "\":";
	response += String(doValue, 1);
	response += ",";

	response += "\"";
	response += "LTMP";
	response += "\":";
	response += String(liquidTemperatureValue, 1);
	response += ",";

	response += "\"";
	response += "EC";
	response += "\":";
	response += String(ecValue, 1);
	response += ",";

	response += "\"";
	response += "PH";
	response += "\":";
	response += String(phValue, 1);
	response += ",";

	if (_channel == '0') {
		phValue = value;
		_channel = '1';
		return response;
	}

	if (_channel == '1') {
		doValue = value;
		_channel = '2';
		return response;
	}

	if (_channel == '2') {
		liquidTemperatureValue = value;
		_channel = '3';
		return response;
	}

	if (_channel == '3') {
		// TODO: Parse correctly
		// 0.00,0,0.00,1.000
		ecValue = value;
		_channel = '0';
		return response;
	}
}

String SensorTentacle::get(void) {

	// Initialize Message
	String message = "";
	char incoming_char;

	updateChannel();

	_ss->write('r');
	_ss->write('\r');

	while (_ss->available()) {
		incoming_char = _ss->read();
		message += incoming_char;
		if (incoming_char == '\r') {
			if (message.indexOf("OK") == -1) {
				break;
			}
			else {
				message = "";
			}
		}
	}
	message = processChannelMessage(message);

  // Return Message
  return message;
}

String SensorTentacle::set(String instruction_code, int instruction_id, String parameter) {
  return "";
}

/*
void SensorDht22::getRawSensorData(void) {
  humidity_raw_ = 0;
  temperature_raw_ = 0;
  if (read()) {
    humidity_raw_ = data[0];
    humidity_raw_ *= 256;
    humidity_raw_ += data[1];
    humidity_raw_ /= 10;
    
    temperature_raw_ = data[2] & 0x7F;
    temperature_raw_ *= 256;
    temperature_raw_ += data[3];
    temperature_raw_ /= 10;
    if (data[2] & 0x80) {
      temperature_raw_ *= -1;
    }    
  }
}

void SensorDht22::getSensorData(void) {
  getRawSensorData();
  filterSensorData();
}

void SensorDht22::filterSensorData(void) {
  humidity = humidity_raw_;
  temperature = temperature_raw_;
}

boolean SensorDht22::read(void) {
  uint8_t last_state = HIGH;
  uint8_t counter = 0;
  uint8_t j = 0, i;
  unsigned long current_time;

  digitalWrite(pin_, HIGH);
  delay(2); // old delay time was 250

  current_time = millis();
  if (current_time < last_read_time_) {
    // ie there was a rollover
    last_read_time_ = 0;
  }
  if (!first_reading_ && ((current_time - last_read_time_) < 2000)) {
    return true; // return last correct measurement
    // delay(2000 - (currenttime - _lastreadtime));
  }
  first_reading_ = false;
  last_read_time_ = millis();

  data[0] = data[1] = data[2] = data[3] = data[4] = 0;
  
  // now pull it low for ~20 milliseconds
  pinMode(pin_, OUTPUT);
  digitalWrite(pin_, LOW);
  delay(20);
  //cli();
  digitalWrite(pin_, HIGH);
  delayMicroseconds(40);
  pinMode(pin_, INPUT);

  // read in timings
  for ( i=0; i< MAXTIMINGS; i++) {
    counter = 0;
    while (digitalRead(pin_) == last_state) {
      counter++;
      delayMicroseconds(1);
      if (counter == 255) {
        break;
      }
    }
    last_state = digitalRead(pin_);

    if (counter == 255) break;

    // ignore first 3 transitions
    if ((i >= 4) && (i%2 == 0)) {
      // shove each bit into the storage bytes
      data[j/8] <<= 1;
      if (counter > count_)
        data[j/8] |= 1;
      j++;
    }
  }

  // check we read 40 bits and that the checksum matches
  if ((j >= 40) && 
      (data[4] == ((data[0] + data[1] + data[2] + data[3]) & 0xFF)) ) {
    return true;
  }
  return false;
}


String SensorDht22::floatToString( double val, unsigned int precision) {
// prints val with number of decimal places determine by precision
// NOTE: precision is 1 followed by the number of zeros for the desired number of decimial places
// example: printDouble( 3.1415, 100); // prints 3.14 (two decimal places)
  String str = "";
  str += int(val);  //prints the int part
  str += "."; // print the decimal point
  unsigned int frac;
  if(val >= 0) {
    frac = (val - int(val)) * precision;
  }
  else {
    frac = (int(val)- val ) * precision;
  }
  str += int(frac);
  return str;
} 
*/
