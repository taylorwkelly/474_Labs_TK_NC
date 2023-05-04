#define SPEAKER_OUT OC4A    // Output pin, Digital pin 6, or PH3
#define TIMER_4_ONBIT PRR1    // Pin to control time on
#define TIMER_4      TCNT4
#define TIMER_4_INPUT_CAPTURE PL0
#define TIMER_4_CONTROL_A TCCR4A //Compare Output Mode. 7:6 is A, 5:4 is B, 3:2 is C
#define TIMER_4_CONTROL_B TCCR4B //Controls prescalar
#define TIMER_4_CONTROL_C TCCR4C //Force outputcompare
#define TIMER_4_COMP_COUNT OCR4A  //Only Need this one for the output

#define REDLED PL2 //DDRL bit 6
#define GREENLED PL1 //DDRL bit 7
#define BLUELED PL0 //DDRL bit 0
#define BITSHIFT_LED 7<<5;

#define TIMER_4_INPUT_CAPTURE PL0

void bit_set_portH(int bit, bool set);

unsigned long time = millis();


void setup() {
  // put your setup code here, to run once:


  //Setting PH3/OCR4A to output mode
  DDRH |= 1<<3;
  DDRL |= BITSHIFT_LED;
  


  //Set Power Reduction Reg to 0;
  TIMER_4 = 0;

  TIMER_4_CONTROL_A = 0;
  TIMER_4_CONTROL_B = 0;


  //Enabling timer
  //TIMER_4_ONBIT |= 1<<4;
  TIMER_4_ONBIT &= ~(1<<4);

  // 800hz is 38.0625
  // 400hz  77.125
  // 250hz is 124
  //TIMER_4_COMP_COUNT = 124;

  //31249

  //Sets the on compare match
  //Setting the prescalar to clk/256, and clock to CTC mode
  TIMER_4_CONTROL_A |= 1<<COM4A0;
  //TIMER_4_CONTROL_A |= 1<<COM4A1;

  
  //TIMER_4_CONTROL_A |= 1 << WGM40;
  //TIMER_4_CONTROL_A |= 1 << WGM41;
  TIMER_4_CONTROL_B |= 1 << WGM42;
  //TIMER_4_CONTROL_B |= 1 << WGM43;
  

  TIMER_4_CONTROL_B |= 1 << CS42;

  //TIMSK4 |= 1<<OCIE4A;
  //interrupts();
  
}


void loop() {
  // task_a();
  // task_b();
  task_c();
  delay(1);

}


void bit_set_portH(int bit, bool set){
  if(set){
    PORTH |= (1<<bit);
  }
  else{
    PORTH &= !(1<<bit);
  }

}

void run_function(void (*functPTR)()){
  functPTR();
}

void task_a(){
  static int time;
  if(time == 0){
    PORTL |= 1<<2;
  }

  time++;

  if(time == 333){
    PORTL &= !(1<<2);
    PORTL |= 1<<1;
  }
  if(time == 666){
    PORTL &= !(1<<1);
    PORTL |= 1;
  }
  if(time == 1000){
    PORTL &= !(1);
    time = 0;
  }
  return;
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
  return;
}

void task_c(){
  static int time;
  if(time == 0){
    run_function(task_a);
  }
  time++;
  // if(time == 2000){
  //   task_b();
  // }
  // // if(time == 6000){
    
  // // }
  if(time == 7000){
    time = 0;
  }
  return;
}

