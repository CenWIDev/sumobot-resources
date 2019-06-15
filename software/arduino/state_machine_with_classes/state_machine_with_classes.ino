#include "StateMachine.h"

StateMachine sm;

const auto SearchFn = []() {
  Serial.write("Searching...\n");
};

const auto AttackFn =  []() {
  Serial.write("Attacking...\n");
};

const auto RetreatFn =  []() {
  Serial.write("Retreating...\n");
};

void setup() {
  Serial.begin(9600);
  
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
