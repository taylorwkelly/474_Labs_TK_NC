#include "Task3.h";


#define OP_DECODEMODE  8
#define OP_SCANLIMIT   10
#define OP_SHUTDOWN    11
#define OP_DISPLAYTEST 14
#define OP_INTENSITY   10
#define X_INPUT A0
#define Y_INPUT A1
#define STICK_POWER 6
#define MOTOR_ON 3
#define DIN 12
#define CS 11
#define CLK 10


unsigned long stimeA;
unsigned long stimeB;
unsigned long stimeC;
//unsigned long joystickTime;
unsigned int sound_index;

int directions[2]; // Holds the last read data for the x, y directions

byte spidata[2]; //spi shift register uses 16 bits, 8 for ctrl and 8 for data


//Transfers 1 SPI command to LED Matrix for given row
//Input: row - row in LED matrix
//       data - bit representation of LEDs in a given row; 1 indicates ON, 0 indicates OFF
void spiTransfer(volatile byte row, volatile byte data);

// Uses the spiTransfer function in order to set or clear a pixel in a given location
//Input: row - row in LED matrix
//       col - column in LED matrix
//       set - true to turn pixel on, false to turn off pixel
void setClearPixel(int row, int col, bool set);

void setup() {
    Serial.begin(9600);

    //must do this setup
    pinMode(DIN, OUTPUT);
    pinMode(CS, OUTPUT);
    pinMode(CLK, OUTPUT);

    pinMode(MOTOR_ON, OUTPUT);
    pinMode(STICK_POWER, OUTPUT);
    pinMode(X_INPUT, INPUT);
    pinMode(Y_INPUT, INPUT);

    //digitalWrite(STICK_POWER, HIGH);
    digitalWrite(CS, HIGH);

    spiTransfer(OP_DISPLAYTEST,0);
    spiTransfer(OP_SCANLIMIT,7);
    spiTransfer(OP_DECODEMODE,0);
    spiTransfer(OP_SHUTDOWN,1);

    for(int i = 0; i < 8; i++){
      spiTransfer(i, 0b00000000);
    }

    // SET LEDS and SPKR pins to OUTPUT mode
    DATA_DIRECTION_REG_LEDS |= LEDSETMASK;
    DATA_DIRECTION_REG_SPKR |= BIT3;
    // ALLOW the timer
    TIMER_4_ALLOW_REG &= ~BIT3;

    // Set the top to 0 for now
    TIMER_4_TOP = 0;

    // SET the FAST PWM MODE as well as allow OC4A to override pin
    // Also prescale the clock to clk/256
    TIMER_4_CTRL_REG_A |= TIMER_4_CTRL_REG_A_MASK;
    TIMER_4_CTRL_REG_B |= TIMER_4_CTRL_REG_B_MASK;

    sound_index = 0;
    //getJoystick();
}

void loop() {
    //TaskA();
    //TaskBV2();
    //TaskC();
    JoystickTask();
    //delay(1);
}

void TaskA() {
    stimeA = millis();
    while (millis() - stimeA < 1000) {
        unsigned long currTime = (millis() - stimeA);
        if (currTime < 333) {
            LED_PORT |= BIT2;
            LED_PORT &= ~BIT0;
        }
        else if (currTime < 666) {
            LED_PORT |= BIT1;
            LED_PORT &= ~BIT2;
        }
        else if (currTime  < 999) {
            LED_PORT |= BIT0;
            LED_PORT &= ~BIT1;
        } 
    }
}

void TaskB() {
    stimeB = millis();
    while (millis() - stimeB < 4000) {
        unsigned long currTime = millis() - stimeB;
        if (currTime < 1000) {
            TIMER_4_TOP = HZ400;
        } else if (currTime < 2000) {
            TIMER_4_TOP = HZ250;
        } else if (currTime < 3000) {
            TIMER_4_TOP = HZ800;
        } else {
            TIMER_4_TOP = 0;
        }
    }
    TIMER_4_TOP = 0;
}

void TaskBV2() { 
    stimeB = millis();
    while (millis() - stimeB < 100000) {
        unsigned long currTime = millis() - stimeB;
        if (sound_index == 52) {
            sound_index = 0;
        }
        if (currTime % 500 == 0) {
            TIMER_4_TOP = melody[sound_index];
            sound_index++;
        }
    }
    TIMER_4_TOP = 0;
}

void TaskC() {
    stimeC = millis();
    while (millis() - stimeC < 12000) {
        unsigned long currTime = millis() - stimeC;
        if (currTime % 1000 < 333) {
            LED_PORT |= BIT2;
            LED_PORT &= ~BIT0;
        }
        else if (currTime % 1000 < 666) {
            LED_PORT |= BIT1;
            LED_PORT &= ~BIT2;
        }
        else if (currTime % 1000 < 999) {
            LED_PORT |= BIT0;
            LED_PORT &= ~BIT1;
        } 
        if (currTime % 4000 < 1000) {
            TIMER_4_TOP = HZ400;
        } else if (currTime % 4000 < 2000) {
            TIMER_4_TOP = HZ250;
        } else if (currTime % 4000 < 3000) {
            TIMER_4_TOP = HZ800;
        } else {
            TIMER_4_TOP = 0;
        }
    }
    //return;    
}

void spiTransfer(volatile byte opcode, volatile byte data){
  int offset = 0; //only 1 device
  int maxbytes = 2; //16 bits per SPI command
  
  for(int i = 0; i < maxbytes; i++) { //zero out spi data
    spidata[i] = (byte)0;
  }
  //load in spi data
  spidata[offset+1] = opcode+1;
  spidata[offset] = data;
  digitalWrite(CS, LOW); //
  for(int i=maxbytes;i>0;i--)
    shiftOut(DIN,CLK,MSBFIRST,spidata[i-1]); //shift out 1 byte of data starting with leftmost bit
  digitalWrite(CS,HIGH);
}



void setClearPixel(int row, int col, bool set){
  col = 7-col;
  int select = 1<<col;  
  if(set){
    spiTransfer(row, select);
  } else{
    select &= !(select);
    spiTransfer(row, select);
  }  
}

void getJoystick(){
  directions[0] = (int) (analogRead(X_INPUT) * 8 / 1024);
  directions[1] = (int) (analogRead(Y_INPUT) * 8 / 1024);
}

void JoystickTask(){
  static int joystickTime;
  joystickTime++;
  if(joystickTime == 5){
    getJoystick();
    setClearPixel(directions[1], directions[0], true);
  }
  if(joystickTime == 10){
    setClearPixel(directions[1], directions[0], false);
    joystickTime = 0;
  }
  return;
}