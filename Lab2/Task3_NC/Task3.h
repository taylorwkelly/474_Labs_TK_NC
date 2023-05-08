#define BIT0 1;
#define BIT1 1 << 1;
#define BIT2 1 << 2;
#define BIT3 1 << 3;
#define BIT4 1 << 4;
#define BIT5 1 << 5;
#define BIT6 1 << 6;
#define BIT7 1 << 7;

#define LEDSETMASK 3 // 00000111
#define TIMER_4_CTRL_REG_A TCCR4A
#define TIMER_4_CTRL_REG_B TCCR4B
#define TIMER_4_TOP OCR4A
#define TIMER_4 TCNT4
#define TIMER_4_OUT OC4A
#define TIMER_4_ALLOW_REG PRR1

#define LED_PORT PORTL
#define DATA_DIRECTION_REG_LEDS DDRL 
#define DATA_DIRECTION_REG_SPKR DDRH
#define TIMER_4_CTRL_REG_A_MASK 67 // 01000011
#define TIMER_4_CTRL_REG_B_MASK 26 // 00011010


#define HZ250 500
#define HZ400 312.75
#define HZ800 156.325

void TaskA();
void TaskB();
void TaskC();
void TaskBV2();
void TaskCV2();

void scheduler1();
void scheduler2();

#define NOTE_c 478.75 //3830 // 261 Hz
#define NOTE_d 425 //3400 // 294 Hz
#define NOTE_e 379.75 //3038 // 329 Hz
#define NOTE_f 358 //2864 // 349 Hz
#define NOTE_g 318.75 //2550 // 392 Hz
#define NOTE_a 284 //2272 // 440 Hz
#define NOTE_b 253.5 //2028 // 493 Hz
#define NOTE_C 239 //1912 // 523 Hz
#define NOTE_R 0

float melody[] = { NOTE_e, NOTE_R, NOTE_d, NOTE_R, NOTE_c, NOTE_R, NOTE_d, NOTE_R, NOTE_e, NOTE_R,NOTE_e, NOTE_R,NOTE_e, NOTE_R,NOTE_d, NOTE_R,NOTE_d, NOTE_R,NOTE_d, NOTE_R,NOTE_e, NOTE_R,NOTE_g,
NOTE_R,NOTE_g, NOTE_R,NOTE_e, NOTE_R,NOTE_d, NOTE_R,NOTE_c, NOTE_R,NOTE_d, NOTE_R,NOTE_e, NOTE_R,NOTE_e, NOTE_R,NOTE_e, NOTE_R,NOTE_e, NOTE_R,NOTE_d, NOTE_R,NOTE_d, NOTE_R,NOTE_e, NOTE_R,NOTE_d, NOTE_R,NOTE_c, NOTE_R,NOTE_c };