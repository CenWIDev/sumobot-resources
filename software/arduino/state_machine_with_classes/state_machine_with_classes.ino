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

void ConfigureStates() {
  sm.AddState("Search", SearchFn);
  sm.AddState("Attack", AttackFn);
  sm.AddState("Retreat", RetreatFn);
  
  sm.AddTransition("Search", "Attack", []() -> bool {
    return robot.DetectOpponent();
  });

  sm.AddTransition("Attack", "Retreat", []() -> bool {
    return robot.DetectEdge();
  });
  
  sm.AddTransition("Attack", "Search", []() -> bool {
    return !robot.DetectOpponent();
  });

  sm.AddTransition("Retreat", "Search", []() -> bool {
    return sm.TimeoutSinceLastTransition(500);
  });
}

void setup() {
  EnableLog(9600);
  robot.Initialize();
  ConfigureStates();
  sm.SetCurrentState("Search");

  // wait for 0.5s warmup time
  while ( millis() < 500) {/* no op */} 
}

void loop() {
  auto nextState = sm.GetNextState();
  sm.SetCurrentState(nextState);
  sm.RunCurrentState();
}
