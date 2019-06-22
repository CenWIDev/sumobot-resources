#include "Log.h"
#include "StateMachine.h"
#include "Robot.h"

StateMachine sm;
Robot robot;

const auto SearchFn = []() {
  Log("Searching...");
  robot.SetMotors(128, -128);
};

const auto AttackFn =  []() {
  Log("Attacking...");
  robot.SetMotors(256, 256);
};

const auto RetreatFn =  []() {
  Log("Retreating...");
  robot.SetMotors(-128, -256);
};

void ConfigureStates(StateMachine* sm) {
  sm->AddState("Search", SearchFn);
  sm->AddState("Attack", AttackFn);
  sm->AddState("Retreat", RetreatFn);
  
  sm->AddTransition("Search", "Attack", [](StateMachine* sm) -> bool {
    return sm->CheckTimeout(500);
  });

  sm->AddTransition("Attack", "Retreat", [](StateMachine* sm) -> bool {
    return sm->CheckTimeout(500);
  });

  sm->AddTransition("Retreat", "Search", [](StateMachine* sm) -> bool {
    return sm->CheckTimeout(250);
  });
}

void setup() {
  EnableLog(9600);
  robot.Initialize();
  ConfigureStates(&sm);
  sm.SetCurrentState("Search");

  // wait for 0.5s warmup time
  while ( millis() < 500) {/* no op */} 
}

void loop() {
  auto nextState = sm.GetNextState();
  sm.SetCurrentState(nextState);
  sm.RunCurrentState();
}
