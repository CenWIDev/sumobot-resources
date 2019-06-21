#pragma once

//#include "Arduino.h"

//#include "Transition.h"

typedef void (*StateFn)();

class State {
public:
  State(String stateName, StateFn f){
    _f = f;
    _stateName = stateName;
  }
  //~State();

  //void AddTransition(String to, TransitionFn f);
  void RunState(){
    _f();
  }
  //bool Is(String stateName);
  
  //String GetNextState(StateMachine* sm);

  String GetName(){
    return _stateName;
  }

private:
  StateFn _f;
  String _stateName;
  //int _numTransitions = 0;
  //Transition* _transitions[3];
};
