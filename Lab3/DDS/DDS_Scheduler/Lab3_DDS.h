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


#define LEDPORT PORTB
#define LED_DATA_DIR_REG DDRB

#define TIMER_ALLOW PRR0
#define TIMER_ALLOW_BIT PRTIM0

#define TIMER_CTRL_REG 



void task1(unsigned long);
void task2(unsigned long);
void task3(unsigned long);
void task4(unsigned long);
void task5(unsigned long);


int compare(int, int);