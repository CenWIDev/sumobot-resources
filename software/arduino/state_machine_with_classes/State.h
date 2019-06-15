#pragma once
#include "Arduino.h"
#include "StateFn.h"

class State {
public:
  State(String stateName, StateFn f) { 
    _f = f;
    _stateName = stateName;
  }
  ~State() {}

  void RunState();

private:
  StateFn _f;
  String _stateName;
};
