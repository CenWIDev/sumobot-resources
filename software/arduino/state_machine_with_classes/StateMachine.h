#pragma once

#include "Arduino.h"

#include "State.h"

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
  bool CheckTimeout(int t);
  void UpdateData();

private:
  int _nStates = 0;
  State* _states[3];
  State* _currentState = nullptr;

  unsigned long long _stateLastUpdated = 0;
};
