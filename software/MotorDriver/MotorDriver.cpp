#include "Arduino.h"
#include "MotorDriver.h"

MotorDriver::MotorDriver(MotorDriver::Config config) : _config(config) {}

void MotorDriver::Init() 
{
  pinMode(_config.AIN1, OUTPUT);
  pinMode(_config.AIN2, OUTPUT);
  pinMode(_config.PWMA, OUTPUT);  
  pinMode(_config.BIN1, OUTPUT);
  pinMode(_config.BIN2, OUTPUT);
  pinMode(_config.PWMB, OUTPUT); 
}

void MotorDriver::SetMotors(int speedA, int speedB)
{
  SetMotor(MotorId::A, speedA);
  SetMotor(MotorId::B, speedB);
}

void MotorDriver::SetMotor(MotorDriver::MotorId id, int speed)
{
  int in1, in2, pwm;

  if( id == MotorId::A )
  {
    in1 = _config.AIN1;
    in2 = _config.AIN2;
    pwm = _config.PWMA;
  } 
  else if (id == MotorId::B) 
  {
    in1 = _config.BIN1;
    in2 = _config.BIN2;
    pwm = _config.PWMB;
  }


  // set direction
  if (speed < 0)
  {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
  }
  else
  {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
  }

  analogWrite(pwm, abs(speed));

}