#include "Log.h"
#include "StateMachine.h"
#include "Robot.h"

StateMachine sm;
Robot robot;

void ConfigureStates() {
  Info("Configuring State Machine...");
  
  sm.AddState("Search", []() {
    robot.SetSpeed(80, -80);
  });
  
  sm.AddState("Attack",  []() {
    robot.SetSpeed(255, 255);
  });
  
  sm.AddState("Retreat",  []() {
    robot.SetSpeed(-100, -155);
  });
  
  sm.AddTransition("*", "Retreat", []() -> bool {
    // if the edge of the arena is detected, transition to the "Retreat" state
    return robot.DetectEdge();
  });
  
  sm.AddTransition("Search", "Attack", []() -> bool {
    // If in "Search" state and you detect the opponent, transition to the "Attack" state
    return robot.DetectOpponent();
  });
  
  sm.AddTransition("Attack", "Search", []() -> bool {
    // if in "Attack" state but you no longer detect the opponent, transition to the "Search" state
    return !robot.DetectOpponent();
  });

  sm.AddTransition("Retreat", "Search", []() -> bool {
    // if in "Retreat" state and you timeout AND no longer detect edge, then transition  into "Search" state
    return sm.TimeoutSinceLastTransition(500) && !robot.DetectEdge();
  });
}

void countdown() {
  // wait for 0.5s warmup time
  while ( millis() < 500) {
    Info("beep...");
    delay(50);
  }
  
  Info("BEEEEEP");
}

void setup() {
  EnableLog(9600, LogLevel::trace);

  ConfigureStates();
  robot.Initialize();
  countdown();
  
  sm.SetCurrentState("Search");
}

void loop() {
  auto nextState = sm.GetNextState();
  sm.SetCurrentState(nextState);
  sm.RunCurrentState();
}
