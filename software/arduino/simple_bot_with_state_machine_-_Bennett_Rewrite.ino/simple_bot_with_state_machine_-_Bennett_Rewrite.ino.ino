//#include "StateFn.h"
//#include "State.h"
#include "StateMachine.h"

StateMachine sm;

void setup() {
  Serial.begin(9600);
  sm.AddState("Search", []() {
    Serial.write("Searching...\n");
  });

  sm.AddState("Attack", []() {
    Serial.write("Attacking...\n");
  });

  sm.AddState("Retreat", []() {
    Serial.write("Retreating...\n");
  });

  sm.AddState("Die", []() {
    Serial.write("Dead...\n");
  });
}

int n = 0;
void loop() {
  sm.SetState("Search");
  sm.Run();
  sm.SetState("Attack");
  sm.Run();
  sm.SetState("Retreat");
  sm.Run();
  sm.SetState("Die");
  sm.Run();
  n = (n+1) %2;
}
