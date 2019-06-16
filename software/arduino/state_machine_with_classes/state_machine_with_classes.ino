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

  sm.AddTransition("Search", "Attack", [](StateMachine* sm) -> bool {
    return sm->CheckTimeout(500); 
  });

  sm.AddTransition("Attack", "Retreat", [](StateMachine* sm) -> bool {
    return sm->CheckTimeout(200);
  });

  sm.AddTransition("Retreat", "Search", [](StateMachine* sm) -> bool {
    return sm->CheckTimeout(100);
  });

  sm.SetCurrentState("Search");
}

void loop() {
  sm.RunCurrentState();
  auto nextState = sm.GetNextState();
  sm.SetCurrentState(nextState);
}
