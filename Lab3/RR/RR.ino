
#include "C:\\Users\\noah-\\Documents\\EE-CSE-474\\474_Labs_TK_NC\\Lab3\\Lab3.h";

unsigned long startTime;
int songIndex, songCount;
unsigned long startTime2;
void setup() {
    LED_DATA_DIR_REG |= BIT6;
    DATA_DIRECTION_REG_SPKR |= BIT3;
    TIMER_4_ALLOW_REG &= ~BIT3;

    TIMER_4_TOP = 0;

    // SET the FAST PWM MODE as well as allow OC4A to override pin
    // Also prescale the clock to clk/256
    TIMER_4_CTRL_REG_A |= TIMER_4_CTRL_REG_A_MASK;
    TIMER_4_CTRL_REG_B |= TIMER_4_CTRL_REG_B_MASK; 


    startTime = millis(), startTime2 = millis();
    songIndex = 0;
    songCount = 0;
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
    unsigned long currTime = millis() - startTime2;
    if (currTime > 100 && songCount < 2) {
        TIMER_4_TOP = song[songIndex++];
        startTime2 = millis();
    }
    if (songIndex > 21 && songCount < 2) {
        songIndex = 0;
        songCount++;
    }
}