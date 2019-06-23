#pragma once

#include "Arduino.h"

#include "Transition.h"

#define MAX_TRANSITIONS 5

typedef void (*StateFn)();

class State {
public:
  State(String stateName, StateFn f);
  ~State();

  void AddTransition(String to, TransitionFn f);
  void ClearTransitions();
  void RunState();
  bool Is(String stateName);

  String GetNextState();

private:
  StateFn _f;
  String _stateName;
  int _numTransitions = 0;
  Transition* _transitions[MAX_TRANSITIONS];
};
