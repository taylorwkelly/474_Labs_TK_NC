#include "Task4_lamb.h";

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

bool set_stick;
unsigned long stimeA;
unsigned long stimeB;
unsigned long stimeC;
unsigned long joystickTime;
unsigned int sound_index;

int directions[2]; // Holds the last read data for the x, y directions

byte spidata[2]; //spi shift register uses 16 bits, 8 for ctrl and 8 for data

void setup() {
    set_stick = true;
    sound_index = 0;

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

    //must do this setup for the joystick
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
}

// Calls the scheduler function to execute the Joystick and Mary
// Had a Little Lamb Tasks, tehn synchronizes it.
void loop() {
    scheduler3();
    delay(1);
}

void scheduler3(){
  JoystickTask_sched();
  TaskBV2_sched();
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

// 8 rows, 0-7
void setClearPixel(int row, int col, bool set){
  // gets the bitshift for the column
  // Onboard: col 0 is fully right, col 7 is fully left
  col = 7-col;
  int select = 1<<col;
  // Set determines whether to write or clear pixel
  if(set){
    spiTransfer(row, select);
  } else{
    select &= !(select);
    spiTransfer(row, select);
  }  
}

// goes [x, y] like coordinate system
void getJoystick(bool set){
  if(set){
    directions[0] = (int) (analogRead(X_INPUT) * 8 / 1024);
    directions[1] = (int) (analogRead(Y_INPUT) * 8 / 1024);
  }
  else return;
}

void JoystickTask_sched(){
  static int joystickTime;
  joystickTime++;
  getJoystick(set_stick);
  if(joystickTime == 1){
    //getJoystick(set_stick);
    setClearPixel(directions[1], directions[0], true);
    set_stick = false;
  }
  if(joystickTime == 50){
    setClearPixel(directions[1], directions[0], false);
    joystickTime = 0;
    set_stick = true;
  }
}

void TaskBV2_sched(){ 
    static int lamb_time;
    //static int step_time;
    //sound_index = 0;
    lamb_time++;
    if (sound_index == 52){
      sound_index = 0;
      TIMER_4_TOP = 0;
    }

    if(lamb_time == 230){
      TIMER_4_TOP = melody[sound_index++];
      lamb_time = 0;
    }
}
