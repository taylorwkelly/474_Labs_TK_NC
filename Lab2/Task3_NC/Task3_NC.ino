#include "Task3.h";



unsigned long stimeA;
unsigned long stimeB;
unsigned long stimeC;
unsigned int sound_index;

void setup() {
    // SET LEDS and SPKR pins to OUTPUT mode
    DATA_DIRECTION_REG_LEDS |= LEDSETMASK;
    DATA_DIRECTION_REG_SPKR |= BIT3;
    // ALLOW the timer
    TIMER_4_ALLOW_REG &= ~BIT4;

    // Set the top to 0 for now
    TIMER_4_TOP = 0;

    // SET the FAST PWM MODE as well as allow OC4A to override pin
    // Also prescale the clock to clk/256
    TIMER_4_CTRL_REG_A |= TIMER_4_CTRL_REG_A_MASK;
    TIMER_4_CTRL_REG_B |= TIMER_4_CTRL_REG_B_MASK;

}

void loop() {
    scheduler1();
    scheduler2();
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
        if (currTime < 1000) {
            TIMER_4_TOP = HZ400;
        } else if (currTime < 2000) {
            TIMER_4_TOP = HZ250;
        } else if (currTime < 3000) {
            TIMER_4_TOP = HZ800;
        } else {
            TIMER_4_TOP = 0;
        }
    }
    TIMER_4_TOP = 0;
}

void TaskBV2() { 
    stimeB = millis();
    unsigned long stepTime = stimeB;
    sound_index = 0;
    while (millis() - stimeB < 12000) {
        unsigned long currTime = millis() - stepTime;
        if (sound_index == 52) sound_index = 0;
        if (currTime > 230) {
            TIMER_4_TOP = melody[sound_index++];
            stepTime = millis();
        }
    }
    TIMER_4_TOP = 0;
}

void TaskC() {
    stimeC = millis();
    while (millis() - stimeC < 12000) {
        unsigned long currTime = millis() - stimeC;
        if (currTime % 1000 < 333) {
            LED_PORT |= BIT2;
            LED_PORT &= ~BIT0;
        }
        else if (currTime % 1000 < 666) {
            LED_PORT |= BIT1;
            LED_PORT &= ~BIT2;
        }
        else if (currTime % 1000 < 999) {
            LED_PORT |= BIT0;
            LED_PORT &= ~BIT1;
        } 
        if (currTime % 4000 < 1000) {
            TIMER_4_TOP = HZ400;
        } else if (currTime % 4000 < 2000) {
            TIMER_4_TOP = HZ250;
        } else if (currTime % 4000 < 3000) {
            TIMER_4_TOP = HZ800;
        } else {
            TIMER_4_TOP = 0;
        }
    }
}

void TaskCV2() {
    stimeC = millis();
    unsigned long stepTime = stimeC;
    sound_index = 0;
    while (millis() - stimeC < 12000) {
        unsigned long currTime = (millis() - stimeC);
        unsigned long songTime = (millis() - stepTime);
        if (currTime % 1000 < 333) {
            LED_PORT |= BIT2;
            LED_PORT &= ~BIT0;
        }
        else if (currTime % 1000 < 666) {
            LED_PORT |= BIT1;
            LED_PORT &= ~BIT2;
        }
        else if (currTime % 1000 < 999) {
            LED_PORT |= BIT0;
            LED_PORT &= ~BIT1;
        } 
        if (sound_index == 52) sound_index = 0;
        if (songTime > 230) {
            TIMER_4_TOP = melody[sound_index++];
            stepTime = millis();
        }
    }
    TIMER_4_TOP = 0;
}

void scheduler1() {
    TaskA();
    TaskB();
    TaskC();
}

void scheduler2() {
    TaskA();
    TaskBV2();
    TaskCV2();
}