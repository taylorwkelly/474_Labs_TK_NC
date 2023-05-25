#include "Lab3.h";

#define TIMER3_ALLOW_REG PRR1
#define TIMER3_CTRLREGA TCCR3A
#define TIMER3_CTRLREGB TCCR3B

#define TIMER3_TOP OCR3A

#define T3CTRLA_MASK B00000011
#define T3CTRLB_MASK B00011011

// prescaler 64 
#define hz500 250

#define READY 0
#define RUNNING 1
#define SLEEPING 2

#define PENDING 0
#define DONE 1


extern unsigned long startTime;
extern int songIndex, songCount, displayCounter;
extern unsigned long stepTimeSong, stepTimeDisplay;
extern int numTasks;
extern int task_num;
extern volatile int flag;
extern int digits[4];

typedef struct Task
{
    int status;
    void (*function) (void);
    unsigned int delay;
    unsigned int sleep_count;
};

extern Task tasks[10];

void scheduler_sync();
void task2SRRI();

void initTasks(Task tasks[], int num) {
    Task t1, t2, t3, t4;
    if (num == 2) {
        tasks[0] = t1, tasks[1] = t2, tasks[3] = t3;
        for (int i = 0; i < 3; i++) {
            tasks[i].status = READY;
            tasks[i].delay = 0;
            tasks[i].delay = 0;
        }
        tasks[0].function = task1;
        tasks[1].function = task2SRRI;
        tasks[2].function = scheduler_sync;
    } else {
        tasks[0] = t1, tasks[1] = t2, tasks[3] = t3, tasks[4] = t4;
        for (int i = 0; i < 4; i++) {
            tasks[i].status = READY;
            tasks[i].delay = 0;
            tasks[i].delay = 0;
        }
        tasks[0].function = task1;
        tasks[1].function = task2SRRI;
        tasks[2].function = task3;
        tasks[3].function = scheduler_sync;
    }
}

void scheduler();

void init() {
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


    startTime = millis(), stepTimeSong = millis(), stepTimeDisplay = millis();
    songIndex = 0, songCount = 0, displayCounter = 0;
    for (int i = 0; i < 4; i++) {
        digits[i] = 0;
    }
    TIMER3_TOP = hz500;
}

void sleep_474(int t) {
    tasks[task_num].sleep_count += t;
}

void task2SRRI() {
    unsigned long currTimeFromStep = millis() - stepTimeSong;
    if (currTimeFromStep > time_array[songIndex]) {
        TIMER_4_TOP = stream[songIndex++];
    }
    if (songIndex > 44) {
        songCount++;
        songIndex = 0;
        stepTimeSong = millis();
    }
    if (songCount == 2){
        songCount = 0;
        sleep_474(4000);
    }
}



void scheduler_sync() {
    while (!flag) {
        ;
    }
    for (int i = 0; i < numTasks; i++) {
        if (tasks[i].status == SLEEPING) {
            if (tasks[i].sleep_count > 0) tasks[i].sleep_count -= 2;
            if (tasks[i].sleep_count < 0) tasks[i].sleep_count = 0;
            if (tasks[i].sleep_count == 0) tasks[i].status = READY;
        } else {
            tasks[i].status = READY;
        }
    }
    flag = PENDING;

}