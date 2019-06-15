#include "StateMachine.h"

StateMachine sm;

const auto SearchFn = []() {
  if(Serial) Serial.write("Searching...\n");
};

const auto AttackFn =  []() {
  if(Serial) Serial.write("Attacking...\n");
};

const auto RetreatFn =  []() {
  if(Serial) Serial.write("Retreating...\n");
};

void ConfigureSerial(int baud) {
  Serial.begin(baud);
  while(!Serial) { /* wait until Serial connection is available */ }
}

void setup() {
  ConfigureSerial(9600);
  
  sm.AddState("Search", SearchFn);
  sm.AddState("Attack", AttackFn);
  sm.AddState("Retreat", RetreatFn);
}

int n = 0;
void loop() {
  sm.SetState(n);
  sm.RunCurrentState();
  n = (n+1) %3;
  delay(500);
}
