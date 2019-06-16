#pragma once

#include "Arduino.h"

void EnableLog(int baud) {
  Serial.begin(baud);
  while(!Serial) { /* wait until Serial connection is available */ }
}

void Log(String message) {
  if(Serial) Serial.println(message);
}
