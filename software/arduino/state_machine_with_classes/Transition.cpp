#include "Arduino.h"
#include "Log.h"
#include "Transition.h"

Transition::Transition(String to, TransitionFn f) {
  _to = to;
  _f = f;
}

Transition::~Transition(){}

bool Transition::ShouldTransition() {
  auto shouldTransition = _f();

  if(shouldTransition)
    Info("Transitioning to state: " + _to);
    
  return shouldTransition;
}

String Transition::To() {
  return _to;
}
