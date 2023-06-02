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

#define LEDPORT PORTH // Contains PIN7 in Port 4
#define LED_DATA_DIR_REG DDRH

#define TIMER_4_CTRL_REG_A TCCR4A
#define TIMER_4_CTRL_REG_B TCCR4B
#define TIMER_4_TOP OCR4A
#define TIMER_4 TCNT4
#define TIMER_4_OUT OC4A
#define TIMER_4_ALLOW_REG PRR1

#define DATA_DIRECTION_REG_SPKR DDRH
#define TIMER_4_CTRL_REG_A_MASK 67 // 01000011
#define TIMER_4_CTRL_REG_B_MASK 27 // 00011011

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
#define SEG_TWO B01011110
#define SEG_THREE B01110110
#define SEG_FOUR B11100010
#define SEG_FIVE B10110110
#define SEG_SIX B10111110
#define SEG_SEVEN B11100100 
#define SEG_EIGHT B11111110
#define SEG_NINE B11100110

#define SEG_C B10011100
#define SEG_S B10110110
#define SEG_E B10011110
#define SEG_BLANK B0

int sign_values[11] = {SEG_BLANK, SEG_BLANK, SEG_BLANK, SEG_BLANK, SEG_FOUR, SEG_SEVEN, SEG_FOUR, SEG_BLANK, SEG_E, SEG_S, SEG_C};


int disp_digits[10] = {SEG_ZERO, SEG_ONE, SEG_TWO, SEG_THREE, SEG_FOUR, SEG_FIVE, SEG_SIX, SEG_SEVEN, SEG_EIGHT, SEG_NINE};
uint8_t disp_select[4] = {DISP0_BIT, DISP1_BIT, DISP2_BIT, DISP3_BIT};


extern unsigned long startTime, stepTimeSong, stepTimeDisplay;
extern int songCount, songIndex, sleepCounter, displayCounter;
extern int digits[4];

// We recommend a duration of 100 ms per note
// We recommend a duration of 100 ms per note
//Notes for bloody stream

//targ_freq = 16000000/(2*N * TOP)  n is prescalar, top is frequency value

#define D5 212.947
#define F5 179.083
#define A5 142.045
#define G5sharp 150.602
#define C6 119.503
#define G5 159.441
#define NOTE_R 0

//28 ms per 16th note
#define quickRest 25
#define rest16 100
#define rest8 200
#define rest2 800

int time_array[] = {rest16, rest16, rest16, quickRest, rest8, rest16, rest16, rest16, rest16, rest16, rest16, rest8, rest16, rest16,
                    rest16, rest16, rest16, quickRest, rest8, rest16, rest16, rest16, rest16, rest16, rest16, rest8, rest16, rest16,
                    rest16, rest16, rest16, quickRest, rest8, rest16, rest16, rest16, rest16, rest16, rest16, rest16, rest16, rest16, rest2, rest16, rest16};

float stream[] = {D5, F5, A5, NOTE_R, G5sharp, D5,  G5, NOTE_R, G5, NOTE_R, D5, F5,  G5, NOTE_R,
                  D5, F5, A5, NOTE_R, G5sharp, D5,  G5, NOTE_R, G5, NOTE_R, D5, F5,  G5, NOTE_R, 
                  D5, F5, A5, NOTE_R, G5sharp, D5,  G5, NOTE_R, G5, NOTE_R, D5, F5, NOTE_R, C6, C6, NOTE_R, NOTE_R};
void task1() {
    unsigned long currTime = millis() - startTime;
    if (currTime % 1000 < 250) {
        LEDPORT |= BIT4;
    } else if (currTime % 1000 < 1000) {
        LEDPORT &= ~BIT4;
    }
}

void task2() {
    unsigned long currTime = millis() - startTime;
    unsigned long currTimeFromStep = millis() - stepTimeSong;
    if (sleepCounter > 0 && (currTimeFromStep) > 1000) {
        sleepCounter--;
        stepTimeSong = millis();
    }
    if (currTimeFromStep > time_array[songIndex] && sleepCounter == 0) {
        TIMER_4_TOP = stream[songIndex++];
        stepTimeSong = millis();
    }
    if (songIndex > 21 && sleepCounter == 0) {
        songIndex = 0;
        songCount++;
    } 
    if (songCount >= 2 && sleepCounter == 0) {
        sleepCounter = 4;
        songCount = 0;
        stepTimeSong = millis();
    }
}


void task3() {
  unsigned long currTimeFromStep = millis() - stepTimeDisplay;
  if (currTimeFromStep > 100) {
    int countCopy = displayCounter + 1;
    for (int i = 0; i < 4; i++) {
        digits[i] = countCopy % 10;
        countCopy /= 10;
    }
    displayCounter++;
    stepTimeDisplay = millis();
  }  
    for (int i = 0; i < 4; i++)
    {   
        DISP_PORT1 &= 0;
        DISP_PORT2 = disp_select[i];
        // DISP_PORT1 |= disp_digits[digits[i]];
        DISP_PORT1 |= digits[i];
        delayMicroseconds(5);
    }
    DISP_PORT2 &= 0;
    DISP_PORT1 &= 0;
}
