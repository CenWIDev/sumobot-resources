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
}

int n = 0;
void loop() {
  sm.SetState(n);
  sm.Run();
  n = (n+1) %2;
}
