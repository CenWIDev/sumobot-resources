const int LED_PIN = 13;
const int DURATION = 1000; // (ms)

void setup() {
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  digitalWrite(LED_PIN, HIGH);
  delay(DURATION);
  digitalWrite(LED_PIN, LOW);
  delay(DURATION);
}
