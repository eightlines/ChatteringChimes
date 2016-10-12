const int MOTOR_PIN = 5;
const int LED_PIN = 13;

void setup() {
  pinMode(MOTOR_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  digitalWrite(MOTOR_PIN, HIGH);
  digitalWrite(LED_PIN, HIGH);
  delay(5000); 
  digitalWrite(MOTOR_PIN, LOW);
  digitalWrite(LED_PIN, LOW);
  delay(5000);
}
