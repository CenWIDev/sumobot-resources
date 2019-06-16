#include "Arduino.h"

#include "State.h"
#include "StateMachine.h"

StateMachine::StateMachine() {}

StateMachine::~StateMachine() {
  ClearStates();
}

void StateMachine::AddState(String stateName, const StateFn f) {
    _states[_nStates] = new State(stateName, f);
    _nStates++;
}

void StateMachine::SetCurrentState(State* s){
  _currentState = s;
  _stateLastUpdated = millis();
}

void StateMachine::SetCurrentState(const int n) {
  if(n >= _nStates) 
    return;
    
  SetCurrentState(_states[n]);
}

State* StateMachine::GetStateByName(String stateName) {
  for(auto s : _states) {
    if(s->Is(stateName)) {
      return s;
    }
  }

  return nullptr;
}

void StateMachine::SetCurrentState(String stateName) {
  if(_currentState && _currentState->Is(stateName))
    return;

  SetCurrentState(GetStateByName(stateName));
}

void StateMachine::ClearStates() {
  for(int i=0; i<_nStates; i++)
    delete _states[i];

  _nStates = 0;
}

void StateMachine::RunCurrentState() {
  if(!_currentState) 
    return;

  _currentState->RunState();
}

String StateMachine::GetNextState() {
  if(!_currentState) {
    return "";
  }

  return _currentState->GetNextState(this);
}

void StateMachine::AddTransition(String from, String to, TransitionFn f) {
  auto s = GetStateByName(from);
  s->AddTransition(to, f);
}

bool StateMachine::CheckTimeout(int t) {
  return (millis()-_stateLastUpdated) > t;
}
