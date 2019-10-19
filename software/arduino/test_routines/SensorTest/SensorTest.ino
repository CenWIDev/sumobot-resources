#include "Arduino.h"

const int ultrasonicDelayMs = 0; 
unsigned long long lastUpdated = 0;
float cachedDistance = 1000.0f;

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


// For motor speed incrementation
int incrementation = 0; 

void setup() {

  Serial.begin(9600);
  while(!Serial) { /* wait until Serial connection is available */ }
  
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

void loop()
{
  incrementation+=10;
  Serial.print("Incrementation is: ");
  Serial.println(incrementation%255);
  testMotors(incrementation);
  testSensors();
}

void testMotors(int velocity)
{
  spinLeft(velocity);
  spinRight(velocity);
}

void testSensors()
{
  Serial.print("Distance is: ");
  Serial.println(getDistance(_trigPin, _echoPin));

  Serial.print("IR sensor says: ");
  Serial.println(digitalRead(_irPin));
}

void spinLeft(int velocity)
{
  digitalWrite(_AIN1, HIGH);
  digitalWrite(_AIN2, LOW);
  analogWrite(_PWMA, velocity);
}

void spinRight(int velocity)
{
  digitalWrite(_BIN1, HIGH);
  digitalWrite(_BIN2, LOW);
  analogWrite(_PWMB, velocity);
}

float getDistance(int trigPin, int echoPin)
{
  // don't try to update more quickly than the delay... in the meantime, return a cached value.
  if(millis() - lastUpdated < ultrasonicDelayMs)
    return cachedDistance;

  float echoTime;
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); 
  digitalWrite(trigPin, LOW);

  echoTime = pulseIn(echoPin, HIGH);
  cachedDistance = (echoTime * .034)/2;
  
  lastUpdated = millis();
  return cachedDistance;
}
