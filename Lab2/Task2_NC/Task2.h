typedef enum State 
{
    INACTIVE, READY, RUNNING, WAITING
};

typedef struct SynchronousTask
{
    enum State state;
    unsigned int delay;
    void (*fptr) (void *p);
    unsigned int* arg_ptr;
};

typedef struct ScheduleArray 
{
    int N_TASKS;    
    struct SynchronousTask tasks[];
};

typedef short int16_t;


#define DELAY_400 delayMicroseconds(2500 / 2)
#define DELAY_250 delayMicroseconds(2000)
#define DELAY_800 delayMicroseconds(2500)


void bit_set(int, int16_t);
void bit_clr(int, int16_t);
void bit_tog(int, int16_t);


