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


void setup() {
  // put your setup code here, to run once:


  //Setting PH3/OCR4A to output
  //DDRH |= 1<<3;
  pinMode(6, OUTPUT);


  //Set Power Reduction Reg to 0;

  //TCNT4 = 0;
  TIMER_4_CONTROL_A = 0;
  TIMER_4_CONTROL_B = 0;


  //Enabling timer
  //TIMER_4_ONBIT |= 1<<4;
  TIMER_4_ONBIT &= !(1<<4);


  TIMER_4_COMP_COUNT = 249;

  

  //Sets the on compare match
  //Setting the prescalar to clk/256, and clock to CTC mode
  TIMER_4_CONTROL_A |= 1<<COM4A0;
  
  TIMER_4_CONTROL_B |= 1 << WGM42;
  TIMER_4_CONTROL_B |= 1 << CS42;

  //Setting compare count
  


  //TIMSK4 |= 1<<OCIE4A;
  //interrupts();
  
}


void loop() {
  // put your main code here, to run repeatedly:
  //TIMER_4_COMP_COUNT = 155.25;
  // bit_set_portH(3, true);
  // delay(2);
  // bit_set_portH(3, false);
  // delay(2);
  // //bit_set_portH(3, false);
  // TIMER_4_COMP_COUNT = 249;
  // //bit_set_portH(3, true);
  // delay(1000);
  // TIMER_4_COMP_COUNT = 77.125;
  // //bit_set_portH(3, true);
  // delay(1000);
  // TIMER_4_COMP_COUNT = 0;
  // //bit_set_portH(3, true);
  // delay(1000);



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

