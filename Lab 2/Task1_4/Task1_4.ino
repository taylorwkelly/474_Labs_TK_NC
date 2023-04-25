#define REDLED PL2 //DDRD bit 6
#define GREENLED PL1 //DDRD bit 7
#define BLUELED PL0 //DDRE bit 0
#define BITSHIFT 7<<5;

void setup() {
  // put your setup code here, to run once:
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
