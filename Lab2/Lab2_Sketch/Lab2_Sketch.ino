#include "Lab2_header.h";

void setup() {
  if (digiwrite && !bitwrite) pinMode(47, OUTPUT); pinMode(48, OUTPUT); pinMode(49, OUTPUT);
  if (bitwrite && !digiwrite) DDRL |= BIT_0; DDRL |= BIT_1; DDRL |= BIT_2;
}

void loop() {
  if (digiwrite == 1) digiWriteBlinks();
  if (bitwrite == 1) bitWriteBlinks();
}

void digiWriteBlinks() {
  for (int i = 0; i < 1000; i++) {
      if (i == 0) {
        digitalWrite(47, HIGH);
      } else if (i == 333) {
        digitalWrite(47, LOW);
        digitalWrite(48, HIGH);
      } else if (i == 666) {
        digitalWrite(48, LOW);
        digitalWrite(49, HIGH);
      }
      delay(1);
    }
    digitalWrite(49, LOW);
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