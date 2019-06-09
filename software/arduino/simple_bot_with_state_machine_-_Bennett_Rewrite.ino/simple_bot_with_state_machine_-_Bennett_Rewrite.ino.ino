#include "State.h"
#include "Transition.h"

//PIN VARIABLES
//the motor will be controlled by the motor A pins on the motor driver
const int AIN1 = 13;           //control pin 1 on the motor driver for the right motor
const int AIN2 = 12;           //control pin 2 on the motor driver for the right motor
const int BIN1 = 8;            //control pin 1 on the motor driver for the right motor
const int BIN2 = 9;            //control pin 2 on the motor driver for the right motor

const int PWMA = 11;           //speed control pin on the motor driver for the right motor
const int PWMB = 10; 

const int trigPin = 6;         //connects to the echo pin on the distance sensor       
const int echoPin = 5;         //connects to the trigger pin on the distance sensor 

int switchPin = 7;             //switch to turn the robot on and off

const int IRPin = 4;           // data pin for IR sensor

State currentState;
unsigned long long lastTransition;

const unsigned long long retreatTimeout = 1000;

void setup(){
  currentState = SEARCH;
  lastTransition = NONE; //How can you set a long to a Transition?

  //set the motor contro pins as outputs
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(PWMA, OUTPUT);  
  pinMode(PWMB, OUTPUT);

  pinMode(trigPin, OUTPUT);   //the trigger pin will output pulses of electricity 
  pinMode(echoPin, INPUT);    //the echo pin will measure the duration of pulses coming back from the distance sensor

  pinMode(IRPin, INPUT);

  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  Serial.println("BEGIN");
  delay(5000);
}

void loop(){
  printState(currentState);
  State s = DetectNewState();
  Serial.write("New ");
  printState(s);
  currentState = s;
  ActCurrState();
}

State DetectNewState(){
  float t = millis();

  if(digitalRead(IRPin) == LOW)
  {
    return RETREAT;
    //need to update this to handle multiple IRs
  }

  switch(currentState){
    case SEARCH:
      return (GetDistance()<30) ? ATTACK : currentState;
      break;
    case ATTACK:
      return (GetDistance()>=30) ? SEARCH : currentState;
      break;
    case RETREAT:
      return ((t-lastTransition)>retreatTimeout) ? SEARCH : currentState;
      break;
    default:
      return currentState;
  }
}

void ActCurrState(){
  switch(currentState){
    case SEARCH:
      Search(100);
      break;
    case RETREAT:
      Retreat(HIGH);
      break;
    case ATTACK:
      Forward(HIGH);
      break;
    default:
      return;
  }
}

/*******Helper Methods**********/

float GetDistance(){ //This will change with new sensors
  float echoTime;
  float calculatedDistance;

    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    echoTime = pulseIn(echoPin, HIGH);

    calculatedDistance = (echoTime * .034)/2;

    return calculatedDistance;
}

void Forward(int motorSpeed){ //check if these ifs are all needed
  if(motorSpeed > 0){
    if(motorSpeed > 255) motorSpeed = 255;
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);
    digitalWrite(BIN1, HIGH);
    digitalWrite(BIN2, LOW);
  }
  else{
    if(motorSpeed < -255) motorSpeed = -255;
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, HIGH);
    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, HIGH);
  }

  analogWrite(PWMA, abs(motorSpeed));
  analogWrite(PWMB, abs(motorSpeed));
}

void Retreat(int motorSpeed){ //will change to take into account multiple IRs
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, HIGH);
  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, HIGH);

  analogWrite(PWMA, motorSpeed/1.25);
  analogWrite(PWMB, motorSpeed);
}

void Search(int motorSpeed){
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, HIGH);
  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, LOW);

  analogWrite(PWMA, motorSpeed);
  analogWrite(PWMB, motorSpeed);  
}
