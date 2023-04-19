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
int i = 0;

void spkr_click();
int8_t spkr_sound();

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LEDPIN, OUTPUT);
  pinMode(PWMPIN, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  int8_t sounded;
  if (ON_B && !OFF_B) {
    digitalWrite(LED_BUILTIN, HIGH);
  } else if (OFF_B && !ON_B) {
    digitalWrite(LEDPIN, HIGH);
  } else if (ON_B && OFF_B) {
    digitalWrite(LEDPIN, HIGH);
    digitalWrite(LED_BUILTIN, LOW);
    // spkr_click();
    if(i < 10){
      sounded = spkr_sound();
      
    }
    else
      sounded = 0;
    
  }
  if (sounded == 0)
    delay(200);

  if (ON_B && !OFF_B) {
    digitalWrite(LED_BUILTIN, LOW);
  } else if (OFF_B && !ON_B) {
    digitalWrite(LEDPIN, LOW);
  } else if (ON_B && OFF_B) {
    digitalWrite(LEDPIN, LOW);
    digitalWrite(LED_BUILTIN, HIGH);
    // spkr_click();
    if(i < 10){
      sounded = spkr_sound();
    }
    else
      sounded = 0;

  }
  if (sounded == 0)
    delay(200);
  if (i < 10)
    i += 1;
}

void spkr_click() {
  digitalWrite(PWMPIN, HIGH);
  delay(5);
  digitalWrite(PWMPIN, LOW);
}

int8_t spkr_sound() {
  for (int itr = 0; itr < 100; itr++) {
    if (itr % 2 == 0) {
      digitalWrite(PWMPIN, LOW);
      delay(2);
    } else if (itr % 2 == 1) {
      digitalWrite(PWMPIN, HIGH);
      delay(2);
    }
  }
  return 1;
}
