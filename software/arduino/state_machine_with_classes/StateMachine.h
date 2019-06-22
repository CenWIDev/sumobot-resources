#pragma once

#include "Arduino.h"

#include "State.h"

#define MAX_STATES 5

class StateMachine {
public:
  StateMachine();
  ~StateMachine();
  
  void AddState(String stateName, StateFn f);
  void ClearStates();
  
  State* GetStateByName(String stateName);
  void SetCurrentState(int n);
  void SetCurrentState(String n);
  void SetCurrentState(State* s);

  void RunCurrentState();
  String GetNextState();

  void AddTransition(String from, String to, TransitionFn f);
  bool TimeoutSinceLastTransition(int t);

private:
  int _nStates = 0;
  State* _states[MAX_STATES];
  State* _currentState = nullptr;

  unsigned long long _stateLastUpdated = 0;
};
