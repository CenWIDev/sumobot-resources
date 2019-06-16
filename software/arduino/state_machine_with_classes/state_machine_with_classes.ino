#include "Log.h"
#include "StateMachine.h"

StateMachine sm;

const auto SearchFn = []() {
  Log("Searching...");
  // Todo: search for other bot, e.g. by rotating in place or following a pattern
};

const auto AttackFn =  []() {
  Log("Attacking...");
  // Todo: full steam ahead!
};

const auto RetreatFn =  []() {
  Log("Retreating...");
  // Todo: backup and turn
};

void setup() {
  //EnableLog(9600);
  
  sm.AddState("Search", SearchFn);
  sm.AddState("Attack", AttackFn);
  sm.AddState("Retreat", RetreatFn);

  sm.AddTransition("Search", "Retreat", [](StateMachine* sm) -> bool {
    // TODO: detect edge of ring
  });

  sm.AddTransition("Search", "Attack", [](StateMachine* sm) -> bool {
    // TODO: detect other bot 
    return sm->CheckTimeout(500);
  });

  sm.AddTransition("Attack", "Retreat", [](StateMachine* sm) -> bool {
    // TODO: detect edge of ring
    return sm->CheckTimeout(200);
  });

  sm.AddTransition("Retreat", "Search", [](StateMachine* sm) -> bool {
    return sm->CheckTimeout(250);
  });

  sm.SetCurrentState("Search");
}

void loop() {
  auto nextState = sm.GetNextState();
  sm.SetCurrentState(nextState);
  sm.RunCurrentState();
  delay(100);
}
