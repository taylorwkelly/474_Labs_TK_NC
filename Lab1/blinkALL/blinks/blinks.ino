/*
  Macro Definitions:

  LEDPIN, PWMPIN <= Pin mappings
  ON_B, OFF_B <= Status Flags
    if ON_B undefined set it as 0
    if OFF_B undefined set it as 0
    else if the are defined, they will be 1
*/
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
// Global variable for number of cycles
int i = 0;

// Function Prototypes

/*********************************************
* spkr_click() A function that clicks the speaker
*   Args: None
*   Returns: None
*
*   This function behaves as a coroutine for the loop function. 
* The primary purpose of this function is to enhance the readability of
* the main function by encapsulating the code in a branch allowing for 
* streamlined transition between spkr_click() and spkr_sound() (commenting
* and uncommenting either one) as shown in the lab.
*
*   Authors: Noah Crouch, Taylor Kelly
*/
void spkr_click();

/*********************************************
* spkr_sound() A function that emits a 250Hz sound from the speaker
*   Args: None
*   Returns: 8 bit integer denoting if the sound was fired off or not.
* This is used in the loop function to determine when to delay between blinks.
* If this function was called, the loop function must not delay any further, but
* if this function was not called the loop function must delay 200 seconds between
* alternating blinks.
*
*   This function behaves as a coroutine for the loop function. 
* The primary purpose of this function is to enhance the readability of
* the main function by encapsulating the code in a branch allowing for 
* streamlined transition between spkr_click() and spkr_sound() (commenting
* and uncommenting either one) as shown in the lab.
*
*   Authors: Noah Crouch, Taylor Kelly
*/
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
  // 8 bit integer to denote if the speaker was sounded off
  int8_t sounded;
  // Conditional logic to choose which routine to do
    // If ON_B is the sole option defined
      // toggle the on board LED only
    // If OFF_B is the sole option defined
      // toggle the off board LED only
    // If both are defined
      // alternate toggling one off and the other on
  if (ON_B && !OFF_B) {
    digitalWrite(LED_BUILTIN, HIGH);
  } else if (OFF_B && !ON_B) {
    digitalWrite(LEDPIN, HIGH);
  } else if (ON_B && OFF_B) {
    digitalWrite(LEDPIN, HIGH);
    digitalWrite(LED_BUILTIN, LOW);
    // comment out spkr_click() and uncomment the spkr_sound()
    // method to enable the speaker to sound off the 250 hz tone
    // Else, comment out spkr_sound() and uncomment spkr_click()
    // to enable the speaker to click
    spkr_click();
    // Only allow the speaker to sound for 10 cycles, 2 seconds
    if(i < 10){
      // get the bit flag from spkr_sound whilst sounding off the speaker
      sounded = spkr_sound();
    }
    else
      // if we are past the 10 cycles then do not sound the speaker and delay
      // using the delay(200)
      sounded = 0;
    
  }
  // if the sounded state is 0 'manually' delay
  if (sounded == 0)
    delay(200);

  // Conditional logic to choose which routine to do
    // If ON_B is the sole option defined
      // toggle the on board LED only
    // If OFF_B is the sole option defined
      // toggle the off board LED only
    // If both are defined
      // alternate toggling one off and the other on
  if (ON_B && !OFF_B) {
    digitalWrite(LED_BUILTIN, LOW);
  } else if (OFF_B && !ON_B) {
    digitalWrite(LEDPIN, LOW);
  } else if (ON_B && OFF_B) {
    digitalWrite(LEDPIN, LOW);
    digitalWrite(LED_BUILTIN, HIGH);
    // comment out spkr_click() and uncomment the spkr_sound()
    // method to enable the speaker to sound off the 250 hz tone
    // Else, comment out spkr_sound() and uncomment spkr_click()
    // to enable the speaker to click
    spkr_click();
    // Only allow the speaker to sound for 10 cycles, 2 seconds
    if(i < 10){
      sounded = spkr_sound();
    }
    else
      // if we are past the 10 cycles then do not sound the speaker and delay
      // using the delay(200)
      sounded = 0;

  }
  // if the sounded state is 0 'manually' delay
  if (sounded == 0)
    delay(200);
  // if the cycle counter is less than 10, increment the cycle counter
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
