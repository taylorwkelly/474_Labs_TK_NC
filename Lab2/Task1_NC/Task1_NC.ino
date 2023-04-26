#include "Task1.h";

void setup() {
  if (digiwrite && !bitwrite) pinMode(REDLED_PIN, OUTPUT); pinMode(GREENLED_PIN, OUTPUT); pinMode(BLUELED_PIN, OUTPUT);
  if (bitwrite && !digiwrite) DDRL |= BIT_0; DDRL |= BIT_1; DDRL |= BIT_2;
}

void loop() {
  if (digiwrite == 1) digiWriteBlinks();
  if (bitwrite == 1) bitWriteBlinks();
}

void digiWriteBlinks() {
  for (int i = 0; i < 1000; i++) {
      if (i == 0) {
        digitalWrite(REDLED_PIN, HIGH);
      } else if (i == 333) {
        digitalWrite(REDLED_PIN, LOW);
        digitalWrite(GREENLED_PIN, HIGH);
      } else if (i == 666) {
        digitalWrite(GREENLED_PIN, LOW);
        digitalWrite(BLUELED_PIN, HIGH);
      }
      delay(1);
    }
    digitalWrite(BLUELED_PIN, LOW);
    delay(1);
}

void bitWriteBlinks() {
  for (int i = 0; i < 1000; i++) {
      if (i == 0) {
        PORTL ^= BIT_2;
      } else if (i == 333) {
        PORTL ^= BIT_2;
        PORTL ^= BIT_1;
      } else if (i == 666) {
        PORTL ^= BIT_1;
        PORTL ^= BIT_0; 
      }
      delay(1);
    }
    PORTL ^= BIT_0;
    delay(1);
}