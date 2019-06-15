#include "Arduino.h"

#include "State.h"
#include "StateMachine.h"

StateMachine::StateMachine() {}

StateMachine::~StateMachine() {
  ClearStates();
}

void StateMachine::AddState(String stateName, StateFn f) {
    _states[_nStates] = new State(stateName, f);
    _nStates++;
}

void StateMachine::SetState(int n) {
  _currentState = _states[n];
}

void StateMachine::ClearStates() {
  for(int i=0; i<_nStates; i++)
    delete _states[i];
}

void StateMachine::RunCurrentState() {
  if(!_currentState) 
    return;

  _currentState->RunState();
}
