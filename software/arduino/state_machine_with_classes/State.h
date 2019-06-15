#pragma once
#include "Arduino.h"
#include "StateFn.h"

class State {
public:
  State(String stateName, StateFn f);
  ~State();

  void RunState();

private:
  StateFn _f;
  String _stateName;
};
