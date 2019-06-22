#pragma once

class Robot {
public: 
  Robot();
  ~Robot();

  void Initialize();
  void SetMotors(int left, int right);
  bool DetectEdge();
  bool DetectOpponent();

private:
  // left motor
  const int _AIN1 = 13;
  const int _AIN2 = 12;
  const int _PWMA = 11;

  // right motor
  const int _BIN1 = 8;
  const int _BIN2 = 9;
  const int _PWMB = 10;

  // ultrasonic sensor
  const int _trigPin = 6;
  const int _echoPin = 5;

  // IR sensors
  const int _irPin = 4;
};
