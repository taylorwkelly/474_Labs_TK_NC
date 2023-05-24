#include "Lab3.h";

unsigned long startTime;
int songIndex, songCount, sleepCounter, displayCounter;
unsigned long stepTimeSong, stepTimeDisplay;
int digits[4] = {0,0,0,0};
void setup() {
    LED_DATA_DIR_REG |= BIT6;
    DATA_DIRECTION_REG_SPKR |= BIT3;
    TIMER_4_ALLOW_REG &= ~BIT3;

    DISP_DDR1 |= DISP_DDR1_MASK;
    DISP_DDR2 |= DISP_DDR2_MASK;

    TIMER_4_TOP = 0;

    // SET the FAST PWM MODE as well as allow OC4A to override pin
    // Also prescale the clock to clk/256
    TIMER_4_CTRL_REG_A |= TIMER_4_CTRL_REG_A_MASK;
    TIMER_4_CTRL_REG_B |= TIMER_4_CTRL_REG_B_MASK; 


    startTime = millis(), stepTimeSong = millis(), stepTimeDisplay = millis();
    songIndex = 0, songCount = 0, sleepCounter = 0, displayCounter = 0;
}

void loop() {
    task1();
    task2();
}
