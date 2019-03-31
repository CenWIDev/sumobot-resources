const int LED_PIN = 13;
const int DURATION = 1000; // (in ms)

int toggle(int val);
void flipDigitalSwitch(int pin);
unsigned long last_switched = 0;

void setup() {
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  unsigned long current_time = millis();

  if( (current_time - last_switched) > DURATION ){
    flipDigitalSwitch(LED_PIN);
    last_switched = current_time;
  }
}

int toggle(int val) { (val == HIGH) ? LOW : HIGH; }

void flipDigitalSwitch(int pin) {
  int current_state = digitalRead(pin);
  int next_state = toggle(current_state);
  digitalWrite(pin, next_state);
}
