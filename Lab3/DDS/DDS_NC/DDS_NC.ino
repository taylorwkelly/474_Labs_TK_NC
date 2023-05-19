#include "../../../Lab3/Lab3.h";
#include "../DDS_Scheduler/DataDriven.h";

TCB TCBs[10];
void initTask(Task);

int idCount = 0;
void setup() {
    Task task1, task2, task3, task4, task5;
    Task tasks[5] = {task1, task2, task3, task4, task5};
    for (int task = 0; task < 5; task++) {
        initTask(tasks[task]);
    }
    task1.name = "LED FLASH"; task2.name = "SPKR SOUND"; task3.name = "DISPLAY CDOWN";
    task4.name = "SMILEY"; task5.name = "CONTROLLER";
    TCB t1, t2, t3, t4, t5;
    TCBs[0]=t1; TCBs[1]=t2; TCBs[2]=t3; TCBs[3]=t4; TCBs[4]=t5; TCBs[5]=nullptr;


}

void loop() {

}


void initTask(Task task) {
    task.id = idCount++;
    task.timesRestarted = 0;
    task.timesStarted = 0;
}