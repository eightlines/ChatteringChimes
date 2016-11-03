#include <VirtualWire.h>

const int MOTOR_PIN = 5;
const int RX_PIN = 6;
const int TX_PIN = 7;
const int MY_ID = 49;
const int MOTOR_TIMESPAN = 1000;

bool trigger = false;
unsigned long pMillis = 0;

String inputString = "";
boolean stringComplete = false;

void setup() {
  Serial.begin(9600);
  Serial.println("Chattering Chimes Init");
  
  pinMode(MOTOR_PIN, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  vw_set_rx_pin(RX_PIN);
  vw_set_tx_pin(TX_PIN);
  vw_setup(1000);
  vw_rx_start();

  inputString.reserve(200);
  pMillis = millis();
}

void loop() {
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;

  if (vw_get_message(buf, &buflen)) {
    digitalWrite(LED_BUILTIN, HIGH);
    for (int i = 0; i < buflen; i++) {
      if (buf[i] == MY_ID) {
        Serial.println("Trigger Motor");
        trigger = true;
        pMillis = millis();
      }
    }
    digitalWrite(LED_BUILTIN, LOW);
  }

  if (trigger) {
    if (millis() - pMillis < MOTOR_TIMESPAN) {
      digitalWrite(MOTOR_PIN, HIGH);
    } else {
      digitalWrite(MOTOR_PIN, LOW);
      Serial.println("Stop Motor");
      trigger = false;
      pMillis = millis();

      Serial.println("Broadcast ID");
      vw_send((uint8_t *)MY_ID, strlen(MY_ID));
      vw_wait_tx();
    }
  }

  if (stringComplete) {
    Serial.println("Trigger Motor");
    inputString = "";
    stringComplete = false;
    trigger = true;
    pMillis = millis();
  }
}

void serialEvent() {
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    inputString += inChar;
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}

