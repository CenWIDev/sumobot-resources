#include "Arduino.h"
#include "Transition.h"

Transition::Transition(String to, TransitionFn f) {
  _to = to;
  _f = f;
}

Transition::~Transition(){}

bool Transition::ShouldTransition() {
  return _f();
}

String Transition::To() {
  return _to;
}
