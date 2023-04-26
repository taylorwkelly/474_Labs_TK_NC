#define digiwrite 1
#ifndef digiwrite
  #define digiwrite 0
#endif

// #define bitwrite 1
#ifndef bitwrite 
  #define bitwrite 0
#endif 

#define REDLED_PIN 47
#define GREENLED_PIN 48
#define BLUELED_PIN 49

#define BIT_0 (1 << 0)
#define BIT_1 (1 << 1)
#define BIT_2 (1 << 2)
#define BIT_3 (1 << 3)
#define BIT_4 (1 << 4)
#define BIT_5 (1 << 5)
#define BIT_6 (1 << 6)
#define BIT_7 (1 << 7)


void digiWriteBlinks();
void bitWriteBlinks();
