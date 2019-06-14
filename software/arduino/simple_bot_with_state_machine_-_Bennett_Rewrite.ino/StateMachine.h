#pragma once

#include "StateFn.h"
#include "State.h"

class StateMachine {
public:
  StateMachine(){}
  ~StateMachine(){}
  
  void AddState(String stateName, StateFn f) {
      _states[_nStates] = new State(stateName, f);
      _nStates++;
  }

  void SetState(String newStateName){
    for(State* state: _states){
      if(state->GetName().equals(newStateName))
        _currentState = state;
    }
  }

  void Run() {
    if(!_currentState) 
      return;

    _currentState->Run();
  }

private:
  int _nStates = 0;
  State* _states[3];
  State* _currentState = nullptr;
};