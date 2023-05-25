#include "SRRI.h";

unsigned long startTime;
int songIndex, songCount;
unsigned long stepTimeSong;
Task tasks[10];
int numTasks;
int task_num;
volatile int flag;

ISR(TIMER3_OVF) {
    flag = DONE;
}

void setup() {
    numTasks = 2;
    initTasks(tasks, numTasks);

    init();
    scheduler();

}

void loop() {

}

void scheduler() {
    flag = PENDING;
    while (1) {
        task_num = 0;
        for (; task_num < numTasks; task_num++) {
            if (!flag && tasks[task_num].status == READY) {
                tasks[task_num].function;
            }
        }
    }
}