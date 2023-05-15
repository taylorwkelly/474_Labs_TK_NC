
int numZeros16BitInt(int num) {
    unsigned int inverted = num;
    int count = 0;
    while (inverted != 0) {
        if (inverted & 1 == 0) {
            count++;
        }
        inverted = inverted >> 1;
    }
    return count;

    /* Instructor solution

    int count = 0;
    for (int i = 0; i < 16; i++) {
        if (!(x&(1<<i))) {
            count++;
        }
    }
    return count;
    */
}

void shiftOnesToEnd16Bit(unsigned int num) {
    int numOnes = 0;
    for (int i = 0; i < 16; i++) {
        if (num & 1 == 1) {
            numOnes++;
        }
        num = num >> 1;
    }
    for (int i = 0; i < numOnes; i++) {
        num++;
        num = num << 1;
    }
}

/* Logical operators
A 01010101 -> 0x55
B 11110000 -> 0xF0
C 00111010 -> 0x38
D 01010101 -> 0x55
E 00010001 -> 0x11

parentheses first, inversions, then left to right
! = invert, falsify if true, make it true if it is false
~ = ones compliment
a = A | B | ~C -> 11110101 | 11000101 -> 11110101
b = (B & C) << 2 -> 00110000 -> 11000000
c = (B && !C) | C -> 00000000 | 00111010 -> 00111010
d = (A << 1) | D -> 11111111
e = (B & C & A) >> 4 -> 00110000 & 01010101 -> 00010000 -> 00000001
*/

