#include "Arduino.h"
#include "StateFn.h"
#include "State.h"

State::State(String stateName, StateFn f) { 
  _f = f;
  _stateName = stateName;
}

State::~State(){}

void State::RunState() {
  return _f();
}
