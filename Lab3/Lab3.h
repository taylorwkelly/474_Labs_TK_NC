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


#define LEDPORT PORTB // Contains Pin13 in Bit position 7
#define LED_DATA_DIR_REG DDRB

#define TIMER0_ALLOW PRR0 // Power Reduction Register 0
#define TIMER0_ALLOW_BIT PRTIM0 // Bit for 8 bit timer 0

#define TIMER0_CTRL_REGA TCCR0A
#define TIMER0_CTRL_REGB TCCR0B
#define TIMER0_OUTPUT_COMPARE_PORT PORTB
#define TIMER0_OC_DATA_DIR_REG DDRB

#define TIMER0_CTRLA_MASK 195 // 11000011
#define TIMER0_CTRLB_MASK 11 // 00001011 

#define TIMER0_TOP OCR0A

#define TIMER_4_CTRL_REG_A TCCR4A
#define TIMER_4_CTRL_REG_B TCCR4B
#define TIMER_4_TOP OCR4A
#define TIMER_4 TCNT4
#define TIMER_4_OUT OC4A
#define TIMER_4_ALLOW_REG PRR1

#define DATA_DIRECTION_REG_SPKR DDRH
#define TIMER_4_CTRL_REG_A_MASK 67 // 01000011
#define TIMER_4_CTRL_REG_B_MASK 27 // 00011011


void task1(unsigned long);
void task2(unsigned long);
void task3(unsigned long);
void task4(unsigned long);
void task5(unsigned long);


int compare(int, int);

// We recommend a duration of 100 ms per note
#define NOTE_E 189.6813354 //659Hz for prescaler 64
#define NOTE_C 239.0057361 //523Hz
#define NOTE_G 159.4387755 //784Hz
#define NOTE_g 318.877551 //392Hz
#define NOTE_R 0 // Rest, play no sound
float song[] = {NOTE_E, NOTE_R, NOTE_E, NOTE_R, NOTE_R, NOTE_E, NOTE_R, NOTE_R, NOTE_C, NOTE_R, NOTE_E, NOTE_R, NOTE_R, NOTE_G, NOTE_R, NOTE_R, NOTE_R, NOTE_R,
NOTE_R, NOTE_g, NOTE_R};
