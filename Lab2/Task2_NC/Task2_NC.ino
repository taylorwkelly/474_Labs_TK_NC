void setup() {
    DDRH |= (1 << 3);
    PRR1 &= ~(1 << 4);
    OCR4AH = 400;
    TCCR4B |= (1 << 3) | (1 << 4) | (1 << 7) | (1 << 6);
    TCCR4A |= (1 << 1) | 1;
}

void loop() {
    
}