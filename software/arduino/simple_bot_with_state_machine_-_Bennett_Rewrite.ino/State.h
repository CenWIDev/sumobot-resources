typedef enum {
  SEARCH,
  ATTACK,
  RETREAT
} State;

void printState(State s)
{
  Serial.write("State: ");

  switch(s){
    case SEARCH:
        Serial.write("SEARCH\n");
        break;
    case RETREAT:
        Serial.write("RETREAT\n");
        break;
    case ATTACK:
        Serial.write("ATTACK\n");
        break;
    default: 
        Serial.write("UNKNOWN\n");
        break;
  }
}
