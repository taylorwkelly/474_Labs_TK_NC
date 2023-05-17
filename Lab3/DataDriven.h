#include "Lab3.h";
#define DEAD 4

typedef struct Task {
    unsigned int id;
    char* name;
    unsigned int timesStarted;
    unsigned int timesRestarted;
} Task;

typedef struct TCB {
    Task task;
    (void) (*fn) (void);
    unsigned int status;
} TCB;