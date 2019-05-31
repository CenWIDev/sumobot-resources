typedef enum {
  SEARCH,
  DESTROY,
  RETREAT,
  DEAD
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
    case DESTROY:
        Serial.write("DESTROY\n");
        break;
    case DEAD:
        Serial.write("DEAD\n");
        break;
    default: 
        Serial.write("UNKNOWN\n");
        break;
  }
}
