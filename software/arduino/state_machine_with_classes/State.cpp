#include "Arduino.h"
#include "StateFn.h"
#include "State.h"

void State::RunState() {
  return _f();
}
