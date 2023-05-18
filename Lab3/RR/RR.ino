
#include "C:\\Users\\noah-\\Documents\\EE-CSE-474\\474_Labs_TK_NC\\Lab3\\Lab3.h";

unsigned long startTime;
int songIndex, songCount, sleeping;
unsigned long stepTime;
unsigned long sleepTime;
void setup() {
    LED_DATA_DIR_REG |= BIT6;
    DATA_DIRECTION_REG_SPKR |= BIT3;
    TIMER_4_ALLOW_REG &= ~BIT3;

    TIMER_4_TOP = 0;

    // SET the FAST PWM MODE as well as allow OC4A to override pin
    // Also prescale the clock to clk/256
    TIMER_4_CTRL_REG_A |= TIMER_4_CTRL_REG_A_MASK;
    TIMER_4_CTRL_REG_B |= TIMER_4_CTRL_REG_B_MASK; 


    startTime = millis(), stepTime = millis();
    sleepTime = 0, songIndex = 0, songCount = 0, sleeping = 0;
}

void loop() {
    task1(startTime);
    task2(startTime);
}


void task1(unsigned long startTime) {
    unsigned long currTime = millis() - startTime;
    if (currTime % 1000 < 250) {
        LEDPORT |= BIT6;
    } else if (currTime % 1000 < 1000) {
        LEDPORT &= ~BIT6;
    }
}

void task2(unsigned long startTime) {
    unsigned long currTime = millis() - startTime;
    unsigned long currTimeFromStep = millis() - stepTime;
    if (sleepTime - millis() < 0 && sleeping == 1) {
        songCount = 0;
        sleeping = 0;
    }
    if (currTimeFromStep > 100 && sleeping == 0) {
        TIMER_4_TOP = song[songIndex++];
        stepTime = millis();
    }
    if (songIndex > 21 && sleeping == 0) {
        songIndex = 0;
        songCount++;
    }
    if (songCount >= 2 && sleeping == 0) {
        sleepTime = millis() + 4000;
        sleeping = 1;
    }
}