#include "Arduino.h"
#include "Distance.h"
#include "Robot.h"

Robot::Robot() {}
Robot::~Robot() {}

void Robot::Initialize() {
  Info("Initializing killer robot...");
  pinMode(_trigPin, OUTPUT);   //the trigger pin will output pulses of electricity 
  pinMode(_echoPin, INPUT);
  pinMode(_irPin, INPUT);
}

void Robot::SetSpeed(const int left, const int right) {
  Trace("Setting motor speeds :: left: " + String(left) + " right: " + String(right));
  // TODO: set those motor speeds
}

bool Robot::DetectEdge() { 
  return digitalRead(_irPin) == LOW;
}

bool Robot::DetectOpponent() { 
  return getDistance(_trigPin, _echoPin) < 100.0f;
}
