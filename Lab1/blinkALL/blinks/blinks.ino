#define LEDPIN 10
#define PWMPIN 2
#define ON_B 
#define OFF_B
#ifdef ON_B 
  #define ON_B 1
#endif
#ifdef OFF_B 
  #define OFF_B 1
#endif
#ifndef ON_B
  #define ON_B 0
#endif
#ifndef OFF_B
  #define OFF_B 0
#endif

void spkr_click();
void spkr_sound();

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LEDPIN, OUTPUT);
  pinMode(PWMPIN, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  if (ON_B && !OFF_B) {
    digitalWrite(LED_BUILTIN, HIGH);
  } else if (OFF_B && !ON_B) {
    digitalWrite(LEDPIN, HIGH);
  } else if (ON_B && OFF_B) {
    digitalWrite(LEDPIN, HIGH);
    digitalWrite(LED_BUILTIN, LOW);
    // spkr_click();
    spkr_sound();
  }
  delay(200);

  if (ON_B && !OFF_B) {
    digitalWrite(LED_BUILTIN, LOW);
  } else if (OFF_B && !ON_B) {
    digitalWrite(LEDPIN, LOW);
  } else if (ON_B && OFF_B) {
    digitalWrite(LEDPIN, LOW);
    digitalWrite(LED_BUILTIN, HIGH);
    // spkr_click();
    spkr_sound();
  }
  delay(200);
}

void spkr_click() {
  digitalWrite(PWMPIN, HIGH);
  delay(5);
  digitalWrite(PWMPIN, LOW);
}

void spkr_sound() {
  unsigned long my_time = millis();
  unsigned long stop_time = my_time + 200;
  unsigned long HALF_PERIOD = 2;
  int state = 0;
  while (my_time < stop_time) {
    my_time = millis();
    if (my_time % HALF_PERIOD == 0) {
      state = state == 0 ? 1 : 0;
    }
    if (state) {
      digitalWrite(PWMPIN, HIGH);
    } else {
      digitalWrite(PWMPIN, LOW);
    }
  }
  
}
