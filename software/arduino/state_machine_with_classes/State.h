#pragma once

#include "Arduino.h"

typedef void (*StateFn)();

class State {
public:
  State(String stateName, StateFn f);
  ~State();

  void RunState();

private:
  StateFn _f;
  String _stateName;
};
