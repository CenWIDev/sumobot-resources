#include "Log.h"
#include "StateMachine.h"

StateMachine sm;

const auto SearchFn = []() {
  Log("Searching...");
  // Todo: search for other bot, e.g. by rotating in place or following a pattern
  digitalWrite(LED_BUILTIN, LOW);
};

/*const auto AttackFn =  []() {
  Log("Attacking...");
  digitalWrite(LED_BUILTIN, digitalRead(LED_BUILTIN) == HIGH ? LOW : HIGH);
  // Todo: full steam ahead!
};

const auto RetreatFn =  []() {
  Log("Retreating...");
  digitalWrite(LED_BUILTIN, HIGH);
  // Todo: backup and turn
};*/

void ConfigureStates(StateMachine* sm) {
  Log("Configuring states...");
  sm.AddState("Search", SearchFn);
  sm.AddState("Attack", AttackFn);
  sm.AddState("Retreat", RetreatFn);
  
  /*sm->AddTransition("Search", "Attack", [](StateMachine* sm) -> bool {
    return sm->CheckTimeout(500);
  });

  sm->AddTransition("Attack", "Retreat", [](StateMachine* sm) -> bool {
    return sm->CheckTimeout(500);
  });

  sm->AddTransition("Retreat", "Search", [](StateMachine* sm) -> bool {
    return sm->CheckTimeout(250);
  });*/
}

void ConfigurePins() {
  Log("Configuring pins...");
  pinMode(LED_BUILTIN, OUTPUT);
}

void setup() {
  EnableLog(9600);
  ConfigurePins();
  ConfigureStates(sm); //this was "ConfigureStates(&sm);"
  sm.SetCurrentState(sm.GetStateByName("Search"));
}

void loop() {
  //sm.UpdateData();
  //auto nextState = sm.GetNextState();
  //sm.SetCurrentState(nextState);
  sm.RunCurrentState();
  delay(20);
}
