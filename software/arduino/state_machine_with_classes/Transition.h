#pragma once

#include "Arduino.h"

class StateMachine;
typedef bool (*TransitionFn)(StateMachine* sm);

class Transition {
public:
  Transition(String to, TransitionFn f);
  ~Transition();

  bool ShouldTransition(StateMachine* sm);
  String To();

private:
  String _to;
  TransitionFn _f;
};
