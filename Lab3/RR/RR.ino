
#include "../Lab3.h";
void setup() {

}

void loop() {
    
}


void task1(unsigned long startTime) {
    unsigned long currTime = millis() - startTime;
    if (currTime % 1000 < 250) {
        LEDPORT |= BIT7;
    } else if (currTime % 1000 < 1000) {
        LEDPORT &= ~BIT7;
    }
}

void task2(unsigned long startTime) {
    unsigned long currTime = millis() - startTime;
    
}