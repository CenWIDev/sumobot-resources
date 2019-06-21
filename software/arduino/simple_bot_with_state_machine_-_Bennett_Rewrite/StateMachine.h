#pragma once

//#include "Arduino.h"

#include "State.h"

class StateMachine {
public:
  StateMachine(){}
  //~StateMachine();
  
  void AddState(String stateName, StateFn f){
    _states[_nStates] = new State(stateName, f);
    _nStates++;
  }
  //void ClearStates();
  
  State GetStateByName(String stateName){
    for(auto s : _states){
      if(s.GetName().equals(stateName))
        return s;
    }
  }
  //void SetCurrentState(int n);
  //void SetCurrentState(String n);
  void SetCurrentState(State s){
    _currentState = s;
  }

  void RunCurrentState(){
    if(!_currentState)
      return;

    _currentState.RunState();
  }
  //String GetNextState();

  //void AddTransition(String from, String to, TransitionFn f);
  //bool CheckTimeout(int t);
  //void UpdateData();

private:
  int _nStates = 0;
  State _states[3];
  State _currentState = _states[0];

  //unsigned long long _stateLastUpdated = 0;
};
