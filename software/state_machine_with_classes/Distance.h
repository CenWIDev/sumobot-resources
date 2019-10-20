#pragma once

#include "Arduino.h"

#include "Log.h"

const int ultrasonicDelayMs = 0; 
unsigned long long lastUpdated = 0;
float cachedDistance = 1000.0f;

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

  Info("distance updated :: " + String(cachedDistance) + "cm");
  
  lastUpdated = millis();
  return cachedDistance;
}
