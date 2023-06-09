#define REDLED PL2 //DDRL bit 6
#define GREENLED PL1 //DDRL bit 7
#define BLUELED PL0 //DDRL bit 0
#define BITSHIFT 7<<5;  // Bitshift to turn on output ports

void setup() {
  // DDRL is the register containing the digital pins
  DDRL |= BITSHIFT;

}

void loop() {
  PORTL |= 1<<2;
  delay(333);
  PORTL &= !(1<<2);
  PORTL |= 1<<1;
  delay(333);
  PORTL &= !(1<<1);
  PORTL |= 1;
  delay(333);
  PORTL &= !(1);
}
