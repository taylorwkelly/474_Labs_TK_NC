#include "Lab3.h";

#define TIMER3_ALLOW_REG PRR1
#define TIMER3_CTRLREGA TCCR3A
#define TIMER3_CTRLREGB TCCR3B

#define TIMER3_TOP OCR3A
#define TIMER3_OVF_ALLOW_REG TIMSK3

#define T3CTRLA_MASK B00000011
#define T3CTRLB_MASK B00011011

// prescaler 64 
#define hz500 500

#define READY 0
#define RUNNING 1
#define SLEEPING 2

#define PENDING 0
#define DONE 1


extern int numTasks;
extern int task_num;
extern volatile int flag;

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
        tasks[0] = t1, tasks[1] = t2, tasks[2] = t3;
        for (int i = 0; i < 3; i++) {
            tasks[i].status = READY;
            tasks[i].delay = 0;
            tasks[i].delay = 0;
        }
        tasks[0].function = task1;
        tasks[1].function = task2SRRI;
        tasks[2].function = scheduler_sync;
    } else {
        tasks[0] = t1, tasks[1] = t2, tasks[2] = t3, tasks[3] = t4;
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
void initialize();

void sleep_474(int t) {
    tasks[task_num].sleep_count = t;
    tasks[task_num].status = SLEEPING;
}

void task2SRRI() {
    unsigned long currTimeFromStep = millis() - stepTimeSong;
    if (currTimeFromStep > time_array[songIndex]) {
        TIMER_4_TOP = stream[songIndex++];
        stepTimeSong = millis();
    }
    if (songIndex > 44) {
        songCount++;
        songIndex = 0;
    }
    if (songCount >= 2){
        songCount = 0;
        sleep_474(4000);
    }
}



void scheduler_sync() {
    while (flag != DONE) {
        ;
    }
    for (int i = 0; i < numTasks; i++) {
        if (tasks[i].status == SLEEPING) {
            if (tasks[i].sleep_count > 0) tasks[i].sleep_count -= 2;
            if (tasks[i].sleep_count <= 0) tasks[i].status = READY;
        } else {
            tasks[i].status = READY;
        }
    }    
    flag = PENDING;
}