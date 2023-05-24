#include "Lab3.h";

typedef struct Task
{
    int status;
    void (*function) (void);
    unsigned int delay;
    unsigned int sleep_count;
};

void initTasks(Task tasks[], int num) {
    Task t1, t2, t3;
    tasks[0] = t1, tasks[1] = t2, tasks[2] = t3;
    for (int i = 0; i < num; i++) {
        tasks[i].status = ACTIVE;
        tasks[i].delay = 0;
        tasks[i].sleep_count = 0;
    }
    tasks[0].function = &task1;
    tasks[1].function = &task2;
    if (num > 2)    tasks[2].function = &task3;
}