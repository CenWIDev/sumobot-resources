#include "State.h"
#include "Transition.h"

//PIN VARIABLES
//the motor will be controlled by the motor A pins on the motor driver
const int AIN1 = 13;            //control pin 1 on the motor driver for the right motor
const int AIN2 = 12;            //control pin 2 on the motor driver for the right motor
const int BIN1 = 8;            //control pin 1 on the motor driver for the right motor
const int BIN2 = 9;            //control pin 2 on the motor driver for the right motor

const int PWMA = 11;            //speed control pin on the motor driver for the right motor
const int PWMB = 10; 

const int trigPin = 6;           //connects to the echo pin on the distance sensor       
const int echoPin = 5;           //connects to the trigger pin on the distance sensor 

int switchPin = 7;             //switch to turn the robot on and off

const int IRPin = 4;

State currentState;
unsigned long long lastTransition;
int motorSpeed = 0;       //starting speed for the motor

void setup() {
  currentState = SEARCH;
  lastTransition = NONE;
  
  pinMode(switchPin, INPUT_PULLUP);   //set this as a pullup to sense whether the switch is flipped

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

  // prints title with ending line break
  Serial.println("BEGIN");
  delay(500);
}

void loop() {
  printState(currentState);
  Transition t = DetectTransition();
  currentState = NewState(currentState, t); 
  printTransition(t);
  Act(currentState);
  delay(200);
}

const float min_dist = 10;
const unsigned long long timeout = 1000;

Transition DetectTransition()
{
  float d = getDistance();
  motorSpeed = (d-10)*20;
  float t = millis();

  Serial.write(digitalRead(IRPin));

  if(digitalRead(IRPin) == LOW)
  {
    return SHOULD_DIE;
  }
  
  switch(currentState) {
    case SEARCH: 
      Serial.print("testing search: ");
      Serial.println(d);
      return (d < min_dist) ? SHOULD_RETREAT : NONE;
      break;
    case DESTROY:
      return NONE;
      break;
    case RETREAT: 
      return ((t - lastTransition) > timeout) ? SHOULD_SEARCH : NONE;
      break;
    case DEAD:
      return SHOULD_SEARCH;
      break;
    default: 
      return NONE;
  }
  
}

State NewState(State s, Transition t)
{
  if(t == NONE)
    return currentState;

  lastTransition = millis();
  if(t == SHOULD_DIE)
    return DEAD;

  if(s == SEARCH && t == SHOULD_RETREAT)
    return RETREAT;
  if(t == SHOULD_SEARCH)
    return SEARCH;
}

void Act(State s) 
{
  switch(s) {
    case DEAD:
      spinMotor(0);
      break;
    case SEARCH:
      spinMotor(motorSpeed);
      break;
    case RETREAT:
      backUp();
      break;
    case DESTROY:
      // TODO: destroy our enemies
    default:
      return;
  }
}

/********************************************************************************/

float getDistance()
{
  float echoTime;                   //variable to store the time it takes for a ping to bounce off an object
  float calculatedDistance;         //variable to store the distance calculated from the echo time
  
  //send out an ultrasonic pulse that's 10ms long
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); 
  digitalWrite(trigPin, LOW);

  echoTime = pulseIn(echoPin, HIGH);      //use the pulsein command to see how long it takes for the
                                          //pulse to bounce back to the sensor
  //calcualtedDistance = echoTime / 148.0;  //calculate the distance of the object that reflected the pulse (half the bounce time multiplied by the speed of sound)
  calculatedDistance = (echoTime * .034)/2;
  
  return calculatedDistance;              //send back the distance that was calculated
}

void spinMotor(int motorSpeed)                       //function for driving the right motor
{

  
  if (motorSpeed > 0)                                 //if the motor should drive forward (positive speed)
  {
    if(motorSpeed > 255) motorSpeed=255;
    digitalWrite(AIN1, HIGH);                         //set pin 1 to high
    digitalWrite(AIN2, LOW);                          //set pin 2 to low
    digitalWrite(BIN1, HIGH);                         //set pin 1 to high
    digitalWrite(BIN2, LOW);
  }
  else                            //if the motor should drive backward (negative speed)
  {
    if(motorSpeed < -255) motorSpeed=-255;
    digitalWrite(AIN1, LOW);                          //set pin 1 to low
    digitalWrite(AIN2, HIGH);                         //set pin 2 to high
    digitalWrite(BIN1, LOW);                          //set pin 1 to low
    digitalWrite(BIN2, HIGH);
  }

  analogWrite(PWMA, abs(motorSpeed));                 //now that the motor direction is set, drive it at the entered speed
  analogWrite(PWMB, abs(motorSpeed));
}

void backUp()
{
  int motorSpeed = 255;

  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, HIGH);
  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, HIGH);

  analogWrite(PWMA, motorSpeed/1.25);
  analogWrite(PWMB, motorSpeed);
}
