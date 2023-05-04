#define SPEAKER_OUT OC4A    // Output pin, Digital pin 6, or PH3
#define TIMER_4_ONBIT PRR1    // Pin to control time on
#define TIMER_4      TCNT4
#define TIMER_4_INPUT_CAPTURE PL0
#define TIMER_4_CONTROL_A TCCR4A //Compare Output Mode. 7:6 is A, 5:4 is B, 3:2 is C
#define TIMER_4_CONTROL_B TCCR4B //Controls prescalar
#define TIMER_4_CONTROL_C TCCR4C //Force outputcompare
#define TIMER_4_COMP_COUNT OCR4A  //Only Need this one for the output

#define TIMER_4_INPUT_CAPTURE PL0

void bit_set_portH(int bit, bool set);

unsigned long time = millis();


void setup() {
  // put your setup code here, to run once:


  //Setting PH3/OCR4A to output mode
  DDRH |= 1<<3;
  


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
  TIMER_4_CONTROL_A |= 1 << COM4A0;
  //TIMER_4_CONTROL_A |= 1<<COM4A1;

  
  //TIMER_4_CONTROL_A |= 1 << WGM40;
  //TIMER_4_CONTROL_A |= 1 << WGM41;
  TIMER_4_CONTROL_B |= 1 << WGM42;
  //TIMER_4_CONTROL_B |= 1 << WGM43;
  

  TIMER_4_CONTROL_B |= 1 << CS42;

  //Setting compare count
  


  //TIMSK4 |= 1<<OCIE4A;
  //interrupts();
  
}


void loop() {
  // put your main code here, to run repeatedly:
  // unsigned long timeNow = millis();
  // if(timeNow - time < 2000){
  //   TIMER_4_COMP_COUNT = 77.125;
  // }
  // else if(timeNow - time < 4000){
  //   TIMER_4_COMP_COUNT = 124;
  // }
  // else if(timeNow - time < 6000){
  //   TIMER_4_COMP_COUNT = 38.0625;
  // }
  // else{
  //   time = millis();
  // }

  TIMER_4_COMP_COUNT = 77.125;
  delay(1000);
  TIMER_4_COMP_COUNT = 0;
  TIMER_4_COMP_COUNT = 124;
  delay(1000);
  TIMER_4_COMP_COUNT = 0;
  TIMER_4_COMP_COUNT = 38;
  delay(1000);
  TIMER_4_COMP_COUNT = 0;
  delay(1000);


  // //delay(250);
  // TIMER_4_COMP_COUNT = 249;
  // //delay(250);
  // TIMER_4_COMP_COUNT = 77.125;
  // //delay(250);
  // TIMER_4_COMP_COUNT = 0;
  // //delay(250);

}


void bit_set_portH(int bit, bool set){
  if(set){
    PORTH |= (1<<bit);
  }
  else{
    PORTH &= !(1<<bit);
  }

}

// void set_freq(int freq){
//   TIMER_4_COMP_COUNT = ((16000000)/(freq*256)) - 1;
// }

