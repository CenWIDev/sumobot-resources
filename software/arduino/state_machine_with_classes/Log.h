#pragma once

#include "Arduino.h"

static void EnableLog(int baud) {
  Serial.begin(baud);
  while(!Serial) { /* wait until Serial connection is available */ }
}

static void Log(String message) {
  if(Serial) Serial.println(message);
}
