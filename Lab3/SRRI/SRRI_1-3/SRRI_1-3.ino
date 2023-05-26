#include "SRRI.h";

unsigned long startTime;
int songIndex, songCount, displayCounter;
unsigned long stepTimeSong, stepTimeDisplay;
Task tasks[10];
int numTasks;
int task_num;
volatile int flag;
int digits[4];

ISR(TIMER3_OVF_vect) {
    flag = DONE;
    TCNT3 = 0;
    TIFR3 &= ~BIT0;
}

void setup() {
    numTasks = 3;
    initTasks(tasks, numTasks);
    LED_DATA_DIR_REG |= BIT6;
    DATA_DIRECTION_REG_SPKR |= BIT3;
    TIMER_4_ALLOW_REG &= ~BIT4;
    TIMER3_ALLOW_REG &= ~BIT3;

    DISP_DDR1 |= DISP_DDR1_MASK;
    DISP_DDR2 |= DISP_DDR2_MASK;

    TIMER3_ALLOW_REG &= ~BIT3;

    TIMER_4_TOP = 0;

    // SET the FAST PWM MODE as well as allow OC4A to override pin
    // Also prescale the clock to clk/64
    TIMER3_CTRLREGA |= T3CTRLA_MASK;
    TIMER3_CTRLREGB |= T3CTRLB_MASK;

    TIMER_4_CTRL_REG_A |= TIMER_4_CTRL_REG_A_MASK;
    TIMER_4_CTRL_REG_B |= TIMER_4_CTRL_REG_B_MASK; 

    TCNT3 = 0;
    startTime = millis(), stepTimeSong = millis(), stepTimeDisplay = millis();
    songIndex = 0, songCount = 0, displayCounter = 0;
    // digits[4] = {0,0,0,0};
    flag = PENDING;
    TIMER3_OVF_ALLOW_REG |= BIT0;
    TIMER3_TOP = hz500;    
    scheduler();

}

void loop() {

}

void scheduler() {
    while (1) {
        task_num = 0;
        for (; task_num < numTasks; task_num++) {
            if (flag == PENDING && tasks[task_num].status == READY) {
                tasks[task_num].status = RUNNING;
                tasks[task_num].function();
            }
        }
        tasks[numTasks].function();
    }
}
