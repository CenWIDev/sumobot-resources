typedef enum {
  SHOULD_RETREAT,
  SHOULD_SEARCH,
  SHOULD_ATTACK,
  NONE
} Transition;

void printTransition(Transition t)
{
  Serial.write("Transition: ");

  switch(t){
    case SHOULD_RETREAT:
        Serial.write("SHOULD_RETREAT\n");
        break;
    case SHOULD_SEARCH:
        Serial.write("SHOULD_SEARCH\n");
        break;
    case SHOULD_ATTACK:
        Serial.write("SHOULD_ATTACK\n");
        break;
    case NONE:
        Serial.write("NONE\n");
        break;
    default: 
        Serial.write("UNKNOWN\n");
        break;
  }
}
