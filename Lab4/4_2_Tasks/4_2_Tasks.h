#define LED_OFFBOARD 13

// PySerial to get output from computer to SErial monitor, running python script from computer
// Output data from computer into serial
// ChatGPT to generate the words


#define BIT0 1;
#define BIT1 (1 << 1);
#define BIT2 (1 << 2);
#define BIT3 (1 << 3);
#define BIT4 (1 << 4);
#define BIT5 (1 << 5);
#define BIT6 (1 << 6);
#define BIT7 (1 << 7);

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

#define D5 212.947
#define F5 179.083
#define A5 142.045
#define G5sharp 150.602
#define C6 119.503
#define G5 159.441

//28 ms per 16th note
#define quickRest 50
#define rest16 200
#define rest8 400
#define rest2 1600

#define NOTE_E 189.6813354 //659Hz for prescaler 64
#define NOTE_C 239.0057361 //523Hz
#define NOTE_G 159.4387755 //784Hz
#define NOTE_g 318.877551 //392Hz
#define NOTE_R 0 // Rest, play no sound

int songIndex, songCount;

int time_array[] = {rest16, rest16, rest16, quickRest, rest8, rest16, rest16, rest16, rest16, rest16, rest16, rest8, rest16, rest16,
                    rest16, rest16, rest16, quickRest, rest8, rest16, rest16, rest16, rest16, rest16, rest16, rest8, rest16, rest16,
                    rest16, rest16, rest16, quickRest, rest8, rest16, rest16, rest16, rest16, rest16, rest16, rest16, rest16, rest16, rest2, rest16, rest16};

float stream[] = {D5, F5, A5, NOTE_R, G5sharp, D5,  G5, NOTE_R, G5, NOTE_R, D5, F5,  G5, NOTE_R,
                  D5, F5, A5, NOTE_R, G5sharp, D5,  G5, NOTE_R, G5, NOTE_R, D5, F5,  G5, NOTE_R, 
                  D5, F5, A5, NOTE_R, G5sharp, D5,  G5, NOTE_R, G5, NOTE_R, D5, F5, NOTE_R, C6, C6, NOTE_R, NOTE_R};


void offBoardLED_task(void *parameters);
void bloodyStream_task(void *parameters);
void FFT_task(void *parameters);
void dataRead_FFT_task(void *parameters);