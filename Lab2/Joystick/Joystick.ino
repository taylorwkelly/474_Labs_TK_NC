/*
Taylor Kelly and Noah Crouch
CSE 474
05/08/2023
*/

#define OP_DECODEMODE  8
#define OP_SCANLIMIT   10
#define OP_SHUTDOWN    11
#define OP_DISPLAYTEST 14
#define OP_INTENSITY   10
#define X_INPUT A0
#define Y_INPUT A1
#define STICK_POWER 6
#define MOTOR_ON 3
#define DIN = 12;
#define CS =  11;
#define CLK = 10;

//Transfers 1 SPI command to LED Matrix for given row
//Input: row - row in LED matrix
//       data - bit representation of LEDs in a given row; 1 indicates ON, 0 indicates OFF
void spiTransfer(volatile byte row, volatile byte data);

// Uses the spiTransfer function in order to set or clear a pixel in a given location
//Input: row - row in LED matrix
//       col - column in LED matrix
//       set - true to turn pixel on, false to turn off pixel
void setClearPixel(int row, int col, bool set);


int directions[2];

byte spidata[2]; //spi shift register uses 16 bits, 8 for ctrl and 8 for data

void setup(){
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
}

void loop(){
  getJoystick();
  int x = directions[0];
  int y = directions[1];
  setClearPixel(y, x, true);
  delay(50);
  setClearPixel(y, x, false);

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
  directions[0] = (analogRead(X_INPUT) * 8 / 1023);
  directions[1] = (analogRead(Y_INPUT) * 8 / 1023);
}