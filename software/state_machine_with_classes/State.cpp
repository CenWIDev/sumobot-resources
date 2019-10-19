#include "Arduino.h"

#include "Log.h"
#include "State.h"

State::State(String stateName, StateFn f) { 
  _f = f;
  _stateName = stateName;
}

State::~State() { 
  ClearTransitions();
}

void State::AddTransition(String to, TransitionFn f) {
  if(_numTransitions >= MAX_TRANSITIONS) {
    Error("Attempting to add more than MAX_TRANSITIONS from a state");
    return;
  }
  Trace("Add transition :: from: " + _stateName + " to: " + to);
  _transitions[_numTransitions] = new Transition(to, f);
  _numTransitions++;
}

void State::ClearTransitions() {
  for(int i=0; i<_numTransitions; i++)
    delete _transitions[i];

  _numTransitions = 0;
}

String State::GetNextState() {

  for (int i=0; i<_numTransitions; i++)
  {
    auto t = _transitions[i];
    if(t->ShouldTransition())
      return t->To();
  }

  // if no transitions, next state is the current state
  return _stateName;
}

void State::RunState() {
  if (_f) 
    _f();
}

bool State::Is(String stateName){
  return _stateName.equals(stateName);
}
