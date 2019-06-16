#pragma once

#include "Arduino.h"

#include "Transition.h"

typedef void (*StateFn)();

class State {
public:
  State(String stateName, StateFn f);
  ~State();

  void AddTransition(String to, TransitionFn f);
  void RunState();
  bool Is(String stateName);

  String GetNextState(StateMachine* sm);

private:
  StateFn _f;
  String _stateName;
  int _numTransitions = 0;
  Transition* _transitions[3];
};
