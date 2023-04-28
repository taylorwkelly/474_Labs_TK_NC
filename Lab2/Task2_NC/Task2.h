typedef enum State 
{
    INACTIVE, READY, RUNNING, WAITING
};

typedef struct SynchronousTask
{
    State state;
    unsigned int delay;
    void (*fptr) (void *p);
    unsigned int* arg_ptr;
};

typedef struct ScheduleArray 
{
    int N_TASKS;    
    SynchronousTask tasks[];
};
