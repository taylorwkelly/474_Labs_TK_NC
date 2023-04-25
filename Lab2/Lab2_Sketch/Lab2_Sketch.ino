#define digiwrite 1
#ifndef digiwrite
  #define digiwrite 0
#endif


void setup() {
  if (digiwrite == 1) {
    pinMode(47, OUTPUT);
    pinMode(48, OUTPUT);
    pinMode(49, OUTPUT);
  }
}

void loop() {
  if (digiWrite == 1) {
    
  }
}
