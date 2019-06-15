#pragma once
#include "Arduino.h"
#include "StateFn.h"
#include "State.h"

class StateMachine {
public:
  StateMachine() { }

  ~StateMachine() {
    ClearStates();
  }
  
  void AddState(String stateName, StateFn f);
  void SetState(int n);
  void ClearStates();
  void RunCurrentState();

private:
  int _nStates = 0;
  State* _states[3];
  State* _currentState = nullptr;
};
