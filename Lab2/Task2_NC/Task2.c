#include "Task2.h"

void bit_set(int location, int16_t sel) {
    int16_t bit = (1 << sel);
    location |= bit;
}

void bit_clr(int location, int16_t sel) {
    int16_t bit = (1 << sel);
    location &= !bit;
}

void bit_tog(int location, int16_t sel) {
    int16_t bit = (1 << sel);
    location ^= bit;
}