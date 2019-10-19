#include "Arduino.h"

#include "Log.h"
#include "Distance.h"
#include "Robot.h"

Robot::Robot() {}
Robot::~Robot() {}

void Robot::Initialize() {
  Info("Initializing killer robot...");
  
  // ultrasonic distance sensor
  pinMode(_trigPin, OUTPUT);
  pinMode(_echoPin, INPUT);

  // IR edge detector
  pinMode(_irPin, INPUT);

  // motors
  pinMode(_AIN1, OUTPUT);
  pinMode(_AIN2, OUTPUT);
  pinMode(_BIN1, OUTPUT);
  pinMode(_BIN2, OUTPUT);
  pinMode(_PWMA, OUTPUT);  
  pinMode(_PWMB, OUTPUT);
}

void Robot::SetSpeed(int left, int right) {
  Trace("Setting motor speeds :: left: " + String(left) + " right: " + String(right));

  if (left > 0)
  {
    if(left > 255) left=255;
    digitalWrite(_AIN1, HIGH);
    digitalWrite(_AIN2, LOW);
  }
  else
  {
    if(left < -255) left=-255;
    digitalWrite(_AIN1, LOW);
    digitalWrite(_AIN2, HIGH);
  }
  analogWrite(_PWMA, abs(left));

  if (right > 0)
  {
    if(right > 255) right=255;
    digitalWrite(_BIN1, HIGH);
    digitalWrite(_BIN2, LOW);
  }
  else
  {
    if(right < -255) right=-255;
    digitalWrite(_BIN1, LOW);
    digitalWrite(_BIN2, HIGH);
  }

  analogWrite(_PWMB, abs(right));
}

bool Robot::DetectEdge() { 
  return digitalRead(_irPin) == LOW;
}

bool Robot::DetectOpponent() { 
  return getDistance(_trigPin, _echoPin) < 100.0f;
}
