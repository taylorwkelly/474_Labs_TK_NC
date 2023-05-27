/* University of Washington
 * ECE/CSE 474,  05/26/2023
 *
 *   Noah Crouch
 *   Taylor Kelly
 *
 *   Lab 3: Schedulers
 *   Acknowledgement: Array seven_seg_digits courtesy of Hacktronics.com sample code.
 *
 */

// Defines Bits for bit manipulation
#define BIT0 1;
#define BIT1 (1 << 1);
#define BIT2 (1 << 2);
#define BIT3 (1 << 3);
#define BIT4 (1 << 4);
#define BIT5 (1 << 5);
#define BIT6 (1 << 6);
#define BIT7 (1 << 7);

// Defines pin numbers for the 7 Seg. Display
#define PIN_A 29
#define PIN_B 28
#define PIN_C 27
#define PIN_D 26
#define PIN_E 25
#define PIN_F 24
#define PIN_G 23
#define PIN_DOT 22
#define SEG_DISP4 34
#define SEG_DISP3 35
#define SEG_DISP2 36
#define SEG_DISP1 37

// Defining Task States
#define ACTIVE 0
#define DELAYED 1
#define HALTED 2
#define SLEEPING 3

// Max number of tasks at a time
#define N_TASKS 10

// Timer Definitions
#define TIMER_ALLOW PRR0
#define TIMER_ALLOW_BIT PRTIM0

#define TIMER_4_CTRL_REG_A TCCR4A
#define TIMER_4_CTRL_REG_B TCCR4B
#define TIMER_4_TOP OCR4A
#define TIMER_4 TCNT4
#define TIMER_4_OUT OC4A
#define TIMER_4_ALLOW_REG PRR1

#define DATA_DIRECTION_REG_SPKR DDRH
#define TIMER_4_CTRL_REG_A_MASK 67 // 01000011
#define TIMER_4_CTRL_REG_B_MASK 27 // 00011011

#define TIMER_CTRL_REG 

// Task 3 Specific, using bit manipulation for the display
#define DISP_PORT1 PORTA
#define DISP_PORT2 PORTC

#define DISP_DDR1 DDRA
#define DISP_DDR2 DDRC
#define DISP_DDR1_MASK 0xFF // 11111111
#define DISP_DDR2_MASK 0x0F // 00001111

#define DISP0_BIT B00001110
#define DISP1_BIT B00001101 
#define DISP2_BIT B00001011 
#define DISP3_BIT B00000111

#define SEG_ZERO B11111100
#define SEG_ONE B01100000
#define SEG_TWO B11011010
#define SEG_THREE B11110010
#define SEG_FOUR B01100110
#define SEG_FIVE B10110110
#define SEG_SIX B10111110
#define SEG_SEVEN B11100100 
#define SEG_EIGHT B11111110
#define SEG_NINE B11100110

// Defining Digits for the display
int disp_digits[10] = {SEG_ZERO, SEG_ONE, SEG_TWO, SEG_THREE, SEG_FOUR, SEG_FIVE, SEG_SIX, SEG_SEVEN, SEG_EIGHT, SEG_NINE};
uint8_t disp_select[4] = {DISP0_BIT, DISP1_BIT, DISP2_BIT, DISP3_BIT};

/*
Pins used in order to wire the 7 segment display
22: Dot
23: G
24: F
25 E
26 D
27 C
28 B
29 A

34: Display 4
35 Disp 3
36 Disp 2
37 Disp 1
*/

// Bit mask for the 7 segment display
byte seven_seg_digits[10][7] = { { 1,1,1,1,1,1,0 },  // = 0
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


// Bit mask for the smile on the 7 segment display
byte smile[4][7] = {{0, 0, 0, 0, 0, 0, 0},
                    {0, 0, 1, 1, 0, 1, 0},
                    {0, 1, 0, 1, 1, 0, 0},
                    {0, 0, 0, 0, 0, 0, 0}
                   };

//Counters for various tasks
unsigned long stepTimeDisplay;
int displayCounter;


// Notes for the song
#define D5 212.947
#define F5 179.083
#define A5 142.045
#define G5sharp 150.602
#define C6 119.503
#define G5 159.441
#define NOTE_E 189.6813354
#define NOTE_C 239.0057361
#define NOTE_G 159.4387755
#define NOTE_g 318.877551
#define NOTE_R 0 // Rest, play no sound

// Rest timing for the song
#define quickRest 50
#define rest16 200
#define rest8 400
#define rest2 1600

// Mario Theme
float song[] = {NOTE_E, NOTE_R, NOTE_E, NOTE_R, NOTE_R, NOTE_E, NOTE_R, NOTE_R, NOTE_C, NOTE_R, NOTE_E, NOTE_R, NOTE_R, NOTE_G, NOTE_R, NOTE_R, NOTE_R, NOTE_R,
NOTE_R, NOTE_g, NOTE_R};

// TIme array for Bloody Stream
int time_array[] = {rest16, rest16, rest16, quickRest, rest8, rest16, rest16, rest16, rest16, rest16, rest16, rest8, rest16, rest16,
                    rest16, rest16, rest16, quickRest, rest8, rest16, rest16, rest16, rest16, rest16, rest16, rest8, rest16, rest16,
                    rest16, rest16, rest16, quickRest, rest8, rest16, rest16, rest16, rest16, rest16, rest16, rest16, rest16, rest16, rest2, rest16, rest16};

// Notes for Bloody Stream
float stream[] = {D5, F5, A5, NOTE_R, G5sharp, D5,  G5, NOTE_R, G5, NOTE_R, D5, F5,  G5, NOTE_R,
                  D5, F5, A5, NOTE_R, G5sharp, D5,  G5, NOTE_R, G5, NOTE_R, D5, F5,  G5, NOTE_R, 
                  D5, F5, A5, NOTE_R, G5sharp, D5,  G5, NOTE_R, G5, NOTE_R, D5, F5, NOTE_R, C6, C6, NOTE_R, NOTE_R};

// Variables for tasks that play the songs
int songIndex, songCount;


// Function Prototypes
void scheduler();
void quit_task(int task_id);
void run_task(void (*fctptr) () );
void sleep_task(int timeToSleep);
void task_self_quit();

void task1();
void task2();
void task3();
void task4_0();
void task4_1();
void task5();
void display_smile();


void int_to_seg(int target);
void sevenSeg_Digit_Write(int digit);
void turn_off_display();
void display_smile();