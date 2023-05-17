#define BIT0 1;
#define BIT1 (1 << 1);
#define BIT2 (1 << 2);
#define BIT3 (1 << 3);
#define BIT4 (1 << 4);
#define BIT5 (1 << 5);
#define BIT6 (1 << 6);
#define BIT7 (1 << 7);

#define ACTIVE 0
#define DELAYED 1
#define HALTED 2
#define SLEEPING 3

typedef struct Task
{
    unsigned int status;
    (void)(*function)(void);
    unsigned int sleepCounter;
    unsigned int delayCounter;
    unsigned int deadlineUS;
};

typedef struct Scheduler
{
    struct Task tasks[];
    unsigned int numTasks;
};


int compare(int, int);