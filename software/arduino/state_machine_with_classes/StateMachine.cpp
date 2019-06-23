#include "Arduino.h"
#include "Log.h"
#include "State.h"
#include "StateMachine.h"

StateMachine::StateMachine() {}

StateMachine::~StateMachine() {
  ClearStates();
}

void StateMachine::AddState(String stateName, const StateFn f) {
  if(_nStates >= MAX_STATES) {
    Error("Attempting to add more than MAX_STATES to the state machine");
    return;
  }
  
  Trace("Add state :: " + stateName);
  _states[_nStates] = new State(stateName, f);
  _nStates++;
}

void StateMachine::SetCurrentState(State* s) {
  Trace("Set current state :: " + s->Name());
  _currentState = s;
  _stateLastUpdated = millis();
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

  return _currentState->GetNextState();
}

void StateMachine::AddTransition(String from, String to, TransitionFn f) {
  if(from.equals("*"))
    return AddTransitionToAll(to, f);
  
  auto s = GetStateByName(from);
  if(s)
    s->AddTransition(to, f);
}

void StateMachine::AddTransitionToAll(String to, TransitionFn f) {
  for(auto& s : _states) {
    if(s && !s->Is(to))
      s->AddTransition(to, f);
  }
}

bool StateMachine::TimeoutSinceLastTransition(int t) {
  return (millis()-_stateLastUpdated) > t;
}
