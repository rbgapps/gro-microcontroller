#include <Event.h>
#include <Timer.h>

/** 
 *  \file src.ino
 *  \brief Enables project to run in arduino IDE.
 *  \details See module_handler.h for introductory documentation.
 *  \author Jake Rye
 */
#include "module_handler.h"

Timer timer;

void setup() { // runs once
  initializeModules();
  timer.every(10000, updateStreamMessage);
}

void loop() { // runs FOREVER!
  updateIncomingMessage();
  timer.update();
  //updateStreamMessage();
  //delay(100);
}
