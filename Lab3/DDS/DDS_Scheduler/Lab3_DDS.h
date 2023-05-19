#define BIT0 1;
#define BIT1 (1 << 1);
#define BIT2 (1 << 2);
#define BIT3 (1 << 3);
#define BIT4 (1 << 4);
#define BIT5 (1 << 5);
#define BIT6 (1 << 6);
#define BIT7 (1 << 7);

#define ACTIVE 0
#define DELAYED 1
#define HALTED 2
#define SLEEPING 3

#define N_TASKS 10

#define LEDPORT PORTB
#define LED_DATA_DIR_REG DDRB

#define TIMER_ALLOW PRR0
#define TIMER_ALLOW_BIT PRTIM0

#define TIMER_CTRL_REG 

// We recommend a duration of 100 ms per note
//Notes for bloody stream
#define D5 587
#define F5 698
#define A5 880
#define G5sharp 830
#define C6 1046


#define E 659 // Hz  E5
#define C 523 // Hz
#define G 784 // Hz
#define g 392 // Hz
#define R 0 // Rest, play no sound
int song[] = {E, R, E, R, R, E, R, R, C, R, E, R, R, G, R, R, R, R,
R, g, R};

byte seven_seg_digits[10][7] = { 
  { 1,1,1,1,1,1,0 },  // = 0
  { 0,1,1,0,0,0,0 },  // = 1
  { 1,1,0,1,1,0,1 },  // = 2
  { 1,1,1,1,0,0,1 },  // = 3
  { 0,1,1,0,0,1,1 },  // = 4
  { 1,0,1,1,0,1,1 },  // = 5
  { 1,0,1,1,1,1,1 },  // = 6
  { 1,1,1,0,0,0,0 },  // = 7
  { 1,1,1,1,1,1,1 },  // = 8
  { 1,1,1,0,0,1,1 }   // = 9
  };



void task1(void *p);
void task2(void *p);
void task3(void *p);
void task4_0(void *p);
void task4_1(void *p);
void task4_2(void *p);
void task5(void *p);


int compare(int, int);