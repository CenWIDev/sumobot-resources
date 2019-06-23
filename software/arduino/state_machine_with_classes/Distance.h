#pragma once

#include "Arduino.h"
#include "Log.h"

int ultrasonicDelayMs = 50; 
unsigned long long _distanceLastUpdated = 0;
float lastDistanceMeasured = 1000.0f;
float getDistance(int trigPin, int echoPin)
{
  if(millis() - _distanceLastUpdated < ultrasonicDelayMs)
    return lastDistanceMeasured;
  
  float echoTime;                   //variable to store the time it takes for a ping to bounce off an object

  //send out an ultrasonic pulse that's 10ms long
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); 
  digitalWrite(trigPin, LOW);

  echoTime = pulseIn(echoPin, HIGH);      //use the pulsein command to see how long it takes for the
                                          //pulse to bounce back to the sensor
  //calcualtedDistance = echoTime / 148.0;  //calculate the distance of the object that reflected the pulse (half the bounce time multiplied by the speed of sound)
  lastDistanceMeasured = (echoTime * .034)/2;

  Trace("distance updated :: " + String(lastDistanceMeasured) + "cm");
  
  return lastDistanceMeasured;              //send back the distance that was calculated
}
