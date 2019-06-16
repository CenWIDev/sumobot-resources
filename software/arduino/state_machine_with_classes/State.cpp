#include "Arduino.h"

#include "State.h"

State::State(String stateName, StateFn f) { 
  _f = f;
  _stateName = stateName;
}

State::~State(){}


void State::AddTransition(String to, TransitionFn f) {
  _transitions[_numTransitions] = new Transition(to, f);
  _numTransitions++;
}

String State::GetNextState(StateMachine* sm) {

  for (int i=0; i<_numTransitions; i++)
  {
    auto t = _transitions[i];
    if(t->ShouldTransition(sm))
    {
      return t->To();
    }
  }

  return _stateName;
}

void State::RunState() {
  return _f();
}

bool State::Is(String stateName){
  return _stateName.equals(stateName);
}
