#pragma once

#include "Arduino.h"

enum class LogLevel {
  silent,
  error,
  warning,
  info,
  trace
};

static LogLevel log_level = LogLevel::info;

static void Log(String message, LogLevel level=LogLevel::info) {
  if(Serial && level <= log_level) Serial.println(message);
}

static void Warning(String message) {
  Log("WARNING: " + message, LogLevel::warning);
}

static void Error(String message) {
  Log("ERROR: " + message, LogLevel::error);
}

static void Info(String message) {
  Log("INFO: " + message, LogLevel::info);
}

static void Trace(String message) {
  Log("TRACE: " + message, LogLevel::trace);
}

static void EnableLog(int baud, LogLevel level=LogLevel::info) {
  log_level=level;
  Serial.begin(baud);
  while(!Serial) { /* wait until Serial connection is available */ }
  
  Info("Beep boop - logs operational");
}
