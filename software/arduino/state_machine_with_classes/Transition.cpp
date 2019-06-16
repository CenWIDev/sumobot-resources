#include "Arduino.h"
#include "Transition.h"

Transition::Transition(String to, TransitionFn f) {
  _to = to;
  _f = f;
}

bool Transition::ShouldTransition(StateMachine* sm) {
  return _f(sm);
}

String Transition::To() {
  return _to;
}
