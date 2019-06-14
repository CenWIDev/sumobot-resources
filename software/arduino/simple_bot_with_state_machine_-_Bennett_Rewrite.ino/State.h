#pragma once

#include "StateFn.h"

class State {
public:
  State(String stateName, StateFn f){ 
    _f = f;
    _stateName = stateName;
  }
  ~State(){}

  void Run() {
    _f();
  }

  String GetName()  {
    return _stateName;
  }

private:
  StateFn _f;
  String _stateName;
};
