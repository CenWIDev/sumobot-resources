#pragma once

#include "Arduino.h"

typedef bool (*TransitionFn)();

class Transition {
public:
  Transition(String to, TransitionFn f);
  ~Transition();

  bool ShouldTransition();
  String To();

private:
  String _to;
  TransitionFn _f;
};
