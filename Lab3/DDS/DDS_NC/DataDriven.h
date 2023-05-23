#include "Lab3_DDS.h";

#define DEAD 4


typedef struct Task {
    unsigned int id;
    char* name;
    unsigned int timesStarted;
    unsigned int timesRestarted;
} Task;

typedef struct TCB {
    Task task;
    void (*fn) ();    // function pointer
    void *arg_ptr;    // arg pointer
    unsigned int status;
    unsigned int delay;
} TCB;
