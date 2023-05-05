#include "Task3.h";



unsigned long stimeA;
unsigned long stimeB;
unsigned long stimeC;

uint8_t taskStatusFlags;

void setup() {
    // SET LEDS and SPKR pins to OUTPUT mode
    DATA_DIRECTION_REG_LEDS |= LEDSETMASK;
    DATA_DIRECTION_REG_SPKR |= BIT3;
    // ALLOW the timer
    TIMER_4_ALLOW_REG &= ~BIT3;

    // Set the top to 0 for now
    TIMER_4_TOP = 0;

    // SET the FAST PWM MODE as well as allow OC4A to override pin
    // Also prescale the clock to clk/256
    TIMER_4_CTRL_REG_A |= TIMER_4_CTRL_REG_A_MASK;
    TIMER_4_CTRL_REG_B |= TIMER_4_CTRL_REG_B_MASK;
}

void loop() {
    TaskA();
    TaskB();

}

void TaskA() {
    stimeA = millis();
    while (millis() - stimeA < 1000) {
        unsigned long currTime = (millis() - stimeA);
        if (currTime < 333) {
            LED_PORT |= BIT2;
            LED_PORT &= ~BIT0;
        }
        else if (currTime < 666) {
            LED_PORT |= BIT1;
            LED_PORT &= ~BIT2;
        }
        else if (currTime  < 999) {
            LED_PORT |= BIT0;
            LED_PORT &= ~BIT1;
        } 
    }
}

void TaskB() {
    stimeB = millis();
    while (millis() - stimeB < 4000) {
        unsigned long currTime = millis() - stimeB;
        if (currTime % 4000 < 1000) {
            TIMER_4_TOP = 0;
            TIMER_4_TOP = HZ400;
        } else if (currTime % 4000 < 2000) {
            TIMER_4_TOP = 0;
            TIMER_4_TOP = HZ250;
        } else if (currTime% 4000 < 3000) {
            TIMER_4_TOP = 0;
            TIMER_4_TOP = HZ800;
        } else {
            TIMER_4_TOP = 0;
        }
    }
}

void TaskC() {

}
