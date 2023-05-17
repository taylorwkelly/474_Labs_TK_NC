#define SPEAKER_OUT OC4A    // Output pin, Digital pin 6, or PH3
#define TIMER_4_ONBIT PRR1    // Pin to control time on
#define TIMER_4      TCNT4
#define TIMER_4_INPUT_CAPTURE PL0
#define TIMER_4_CONTROL_A TCCR4A //Compare Output Mode. 7:6 is A, 5:4 is B, 3:2 is C
#define TIMER_4_CONTROL_B TCCR4B //Controls prescalar
#define TIMER_4_CONTROL_C TCCR4C //Force outputcompare
#define TIMER_4_COMP_COUNT OCR4A  //Only Need this one for the output

#define TIMER_4_INPUT_CAPTURE PL0

unsigned long time;

void setup() {
  time = millis();
  //Setting PH3/OCR4A to output mode
  DDRH |= 1<<3;
  
  //Set Power Reduction Reg to 0;
  TIMER_4 = 0;

  //Initializes Control registers
  TIMER_4_CONTROL_A = 0;
  TIMER_4_CONTROL_B = 0;


  //Enabling timer
  TIMER_4_ONBIT &= ~(1<<4);

  //Sets the on compare match
  //Setting the prescalar to clk/256, and clock to CTC mode
  TIMER_4_CONTROL_A |= 1 << COM4A0;
  //TIMER_4_CONTROL_A |= 1<<COM4A1;

  //TIMER_4_CONTROL_A |= 1 << WGM40;
  //TIMER_4_CONTROL_A |= 1 << WGM41;
  TIMER_4_CONTROL_B |= 1 << WGM42;
  //TIMER_4_CONTROL_B |= 1 << WGM43;
  
  TIMER_4_CONTROL_B |= 1 << CS42;
}

void loop() {
  task_b();
  delay(1);
}

void task_b(){
  static int time;
  if(time == 0){  //400 hz
    TIMER_4 = 0;
    TIMER_4_COMP_COUNT = 77.125;
  }
  time++;
  if(time == 1000){ //250 hz
    TIMER_4 = 0;
    TIMER_4_COMP_COUNT = 124;
  }
  if(time == 2000){ // 800 hz
    TIMER_4 = 0;
    TIMER_4_COMP_COUNT = 38.0625;
  }
  if(time == 3000){ // 0 hz
    TIMER_4 = 0;
    TIMER_4_COMP_COUNT = 0;
  }
  if(time == 4000){
    time = 0;
  }
}