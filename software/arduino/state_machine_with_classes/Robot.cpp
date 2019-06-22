#include "Arduino.h"
#include "Robot.h"

Robot::Robot() {}
Robot::~Robot() {}

void Robot::Initialize() {
  // TODO: set pinMode() for all the robot's pins
}

void Robot::SetMotors(const int left, const int right) {
  // TODO: set those motor speeds
}

bool Robot::DetectEdge() { 
  // TODO: detect those edges
  return true;
}

bool Robot::DetectOpponent() { 
  // TODO: detect that opponent
  return true;
}
