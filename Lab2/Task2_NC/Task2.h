#define INACTIVE 0
#define READY 1
#define RUNNING 2
#define WAITING 3

typedef struct SynchronousTask
{
    int8_t status;
    unsigned int delay;
    void (*fptr) (void *p);
    unsigned int* arg_ptr;
} SynchronousTask;

typedef struct ScheduleArray 
{
    int N_TASKS;    
    struct SynchronousTask tasks[];
} ScheduleArray;

typedef short int16_t;
typedef unsigned char int8_t;


void bit_set(int, int8_t);
void bit_clr(int, int8_t);
void bit_tog(int, int8_t);

void sleep(struct SynchronousTask*, int);
void run(struct SynchronousTask*, int);
int8_t getTask(struct SynchronousTask*);
