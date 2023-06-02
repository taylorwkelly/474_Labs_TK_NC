/* University of Washington
 * ECE/CSE 474,  05/26/2023
 *
 *   Noah Crouch
 *   Taylor Kelly
 *
 *   Lab 3: Schedulers
 *
 */
#include "DataDriven.h";

void task_start(TCB *task);

// Defining the Task List, and list for dead tasks
TCB TCB_List[N_TASKS];
TCB Dead_Tasks[N_TASKS];

TCB *tcb_list_ptr = &TCB_List[0];

Task t_task1; //LED Flash
Task t_task2; // Plays Bloody Stream
Task t_task3; // Counts up on 7 Seg
Task t_task4_0; // Countdown to music play
Task t_task4_1; // Play music with frequency
Task t_task5; //Supervisor
Task t_task6; // Display Smile

// Global variables for various tasks
int current_running_task_index, dead_task_index;
int task_count, dead_count;

Task task_arr[7] = {t_task1, t_task2, t_task3, t_task4_0, t_task4_1, t_task5, t_task6};

int digits[4] = {0};

void setup() {
  Serial.begin(9600);

  // Setting the various Pins for output
  pinMode(13, OUTPUT);

  pinMode(PIN_A, OUTPUT);
  pinMode(PIN_B, OUTPUT);
  pinMode(PIN_C, OUTPUT);
  pinMode(PIN_D, OUTPUT);
  pinMode(PIN_E, OUTPUT);
  pinMode(PIN_F, OUTPUT);
  pinMode(PIN_G, OUTPUT);
  pinMode(PIN_DOT, OUTPUT);

  pinMode(SEG_DISP4, OUTPUT);
  pinMode(SEG_DISP3, OUTPUT);
  pinMode(SEG_DISP2, OUTPUT);
  pinMode(SEG_DISP1, OUTPUT);

  stepTimeDisplay = millis();
  displayCounter = 0;

  DATA_DIRECTION_REG_SPKR |= BIT3;
  TIMER_4_ALLOW_REG &= ~BIT3;

  DISP_DDR1 |= DISP_DDR1_MASK;
  DISP_DDR2 |= DISP_DDR2_MASK;

  TIMER_4_TOP = 0;

  // SET the FAST PWM MODE as well as allow OC4A to override pin
  // Also prescale the clock to clk/256
  TIMER_4_CTRL_REG_A |= TIMER_4_CTRL_REG_A_MASK;
  TIMER_4_CTRL_REG_B |= TIMER_4_CTRL_REG_B_MASK;

  songIndex = 0;
  songCount = 0;
  task_count = 0;
  dead_count = 0;

  //Task ID will be equal to where it is initialized within the Task List
  t_task1 = {0, "LED Flash", 0};
  t_task2 = {1, "Bloody Stream", 0};
  t_task3 = {2, "7 Segment LED", 0};
  t_task4_0 = {3, "7 Seg Countdown", 0};
  t_task4_1 = {4, "Music Play", 0};
  t_task5 = {5, "Supervisor", 0};
  t_task6 = {6, "Smile", 0};
  

  // Initializing all the TCBs. Task 5 Currently Active
  int i = 0;
  TCB_List[i].task = task_arr[0];
  TCB_List[i].fn = task1;
  TCB_List[i].arg_ptr = NULL;
  TCB_List[i].status = DEAD;
  TCB_List[i].delay = 0;
  i++;
  task_count++;

  TCB_List[i].task = task_arr[1];
  TCB_List[i].fn = task2;
  TCB_List[i].arg_ptr = NULL;
  TCB_List[i].status = DEAD;
  TCB_List[i].delay = 0;
  i++;
  task_count++;

  TCB_List[i].task = task_arr[2];
  TCB_List[i].fn = task3;
  TCB_List[i].arg_ptr = NULL;
  TCB_List[i].status = DEAD;
  TCB_List[i].delay = 0;
  i++;
  task_count++;

  TCB_List[i].task = task_arr[3];
  TCB_List[i].fn = task4_0;
  TCB_List[i].arg_ptr = NULL;
  TCB_List[i].status = DEAD;
  TCB_List[i].delay = 0;
  i++;
  task_count++;

  TCB_List[i].task = task_arr[4];
  TCB_List[i].fn = task4_1;
  TCB_List[i].arg_ptr = NULL;
  TCB_List[i].status = DEAD;
  TCB_List[i].delay = 0;
  i++;
  task_count++;

  TCB_List[i].task = task_arr[5];
  TCB_List[i].fn = task5;
  TCB_List[i].arg_ptr = NULL;
  TCB_List[i].status = ACTIVE;
  TCB_List[i].delay = 0;
  i++;
  task_count++;

  TCB_List[i].task = task_arr[6];
  TCB_List[i].fn = display_smile;
  TCB_List[i].arg_ptr = NULL;
  TCB_List[i].status = DEAD;
  TCB_List[i].delay = 0;
  i++;
  task_count++;
  TCB_List[i+1].fn = NULL;

}

// Loop for the scheduler
void loop() {
  while(1){
    scheduler();
    delay(1);
  }
}


//This is going to loop through the TCB List, and run the task if it's state is ACTIVE
void scheduler(){
  // Restarts the list for the scheduler
  if(TCB_List[current_running_task_index].fn == NULL && current_running_task_index != 0){
    current_running_task_index = 0;
  }
  // Means that there are no tasks to run, and theres nothing to do
  if(TCB_List[current_running_task_index].fn == NULL && current_running_task_index == 0){
    exit(1);
  } else{
    // Runs the tasks that are active
    while(TCB_List[current_running_task_index].fn != NULL){
      switch(TCB_List[current_running_task_index].status){
        case(ACTIVE):
        run_task(TCB_List[current_running_task_index].fn);

        // If a task is sleeping, decrement the sleep counter by 1
        // If delay is 0, turns the task back on
        case(SLEEPING):
        TCB_List[current_running_task_index].delay -= 1;
        if(TCB_List[current_running_task_index].delay == 0){
          TCB_List[current_running_task_index].status = ACTIVE;
          TCB_List[current_running_task_index].task.timesStarted_Restarted++;
        }
      }
      current_running_task_index++;
    }
  }
}

void quit_task(int task_id){
  TCB_List[task_id].status = DEAD;
}

void run_task(void (*fctptr) () ){
  fctptr();
}

void sleep_task(int timeToSleep){
  TCB_List[current_running_task_index].delay = timeToSleep;
  TCB_List[current_running_task_index].status = SLEEPING;

}

void task_self_quit(){
  TCB_List[current_running_task_index].status = DEAD;
  Dead_Tasks[current_running_task_index] = TCB_List[current_running_task_index];
  task_count--;
  dead_count++;
  
}

// Takes a Pointer, and starts that task again (from DEAD to ALIVE)
void task_start(TCB *task){
  task->status = ACTIVE;
  task->task.timesStarted_Restarted++;
}

// ID = 0
// LED task
void task1() {
    static int time = 0;
    static int count = 0;
    if (time < 250) {
        digitalWrite(13, HIGH);
    } else if (time < 1000) {
        digitalWrite(13, LOW);
    } else{
      time = 0;
      count++;
    }
    time++;
}

// ID = 1
// Plays the song twice, then sleeps for 4 seconds
void task2() {
    static int time = 0;
    static int bpm = 0;
    if (time == time_array[bpm]) {
        TIMER_4_TOP = stream[songIndex++];
        time = 0;
        bpm++;
    }
    if (songIndex > 44 || bpm > 44) {
        songIndex = 0;
        bpm = 0;
        songCount++;
    } 
    if (songCount >= 2) {
      songCount = 0;
      sleep_task(4000);
    }
    time++;
}

// ID = 2
// Counts up using the 7 segment display, incrementing every 100 ms
void task3() {
  unsigned long currTimeFromStep = millis() - stepTimeDisplay;
  if (currTimeFromStep > 100) {
    int countCopy = displayCounter + 1;
    for (int i = 0; i < 4; i++) {
        digits[i] = countCopy % 10;
        countCopy /= 10;
    }
    displayCounter++;
    stepTimeDisplay = millis();
  }  
    for (int i = 0; i < 4; i++)
    {   
        DISP_PORT1 &= 0;
        DISP_PORT2 = disp_select[i];
        DISP_PORT1 |= disp_digits[digits[i]];
        delayMicroseconds(5);
    }
    DISP_PORT2 &= 0;
    DISP_PORT1 &= 0;
}

//ID = 3
// Counts down on the 7 segment display, from 3 to 0 seconds
void task4_0(){
  static int time = 0;
  static int countdown = 3000;
  if(time = 100){
    int_to_seg(countdown);
    time = 0;
    countdown--;
  }
  for (int i = 0; i < 4; i++)
  {
    sevenSeg_Digit_Write(digits[i]);
    digitalWrite(37-i, LOW);
    delayMicroseconds(15);
    digitalWrite(37-i, HIGH);
  }
  if(countdown == 0){
    time = 0;
    countdown = 3000;
    turn_off_display();
    //FOR TASK 4: Add the following line
    //task_start(&TCB_List[4])
    task_self_quit();
    return;
  }
}

//ID: 4
// Plays the song and displays each note's frequency
void task4_1(){
  static int time = 0;
  static int bpm = 0;
  if (time == time_array[bpm]) {
      float temp = stream[songIndex];
      temp = 16000000/(2*64 * temp);
      int_to_seg(temp);
      TIMER_4_TOP = stream[songIndex++];
      time = 0;
      bpm++;
  }
  for (int i = 0; i < 4; i++)
  {
    turn_off_display();
    sevenSeg_Digit_Write(digits[i]);
    digitalWrite(37-i, LOW);
    delayMicroseconds(5);
  }
  turn_off_display();
  if (songIndex > 44 || bpm > 44) {
      songIndex = 0;
      bpm = 0;
      songCount++;
  } 
  if (songCount >= 1) {
    songCount = 0;
    task_self_quit();
    task_start(&TCB_List[3]);
    return;
  }
  time++;
}
/*
ID:5
Supervisor task that follows this schedule (from lab document):
a) Task 1 runs all the time.
b) Task 2 runs at the start but stops after playing the theme 2 times.
c) After Task 2, start a count-down (on the 7-segment display) for 3 seconds
and then restarts task 2 (original definition above) for one final time.
d) Display a “smile” for 2 seconds (See Appendix B) (code this as a new task to be
controlled by Task 5). The 2 second interval begins after completion of part 5c.
e) Stop all tasks, except “a) Task 1” in this list.   */
void task5(){
  static int stage = 0;
  //5a
  if(TCB_List[5].task.timesStarted_Restarted == 0){
    task_start(&TCB_List[0]);
    task_start(&TCB_List[1]);
    TCB_List[5].task.timesStarted_Restarted++;
    stage++;
  }
  //5b
  if(TCB_List[1].status == SLEEPING && TCB_List[1].task.timesStarted_Restarted == 1 && stage == 1){
    quit_task(1);
    //TCB_List[1].delay = 0;
    task_start(&TCB_List[3]);
    stage++;
  }
  //5C
  if(TCB_List[3].status == DEAD && stage == 2){
    task_start(&TCB_List[1]);
    stage++;
  }
  //5D
  if(TCB_List[1].status == SLEEPING && TCB_List[1].task.timesStarted_Restarted >= 2 && stage == 3){
    quit_task(1);
    task_start(&TCB_List[6]);
    stage++;    
  }
  //5E
  if(stage >= 4 && TCB_List[6].status == DEAD){
    quit_task(1);
    quit_task(2);
    quit_task(3);
  }
}

//ID = 6
// Task to display a smile on the 7 segment display for 2 seconds
void display_smile(){
  static int countdown = 2000;
  for (int i = 0; i < 4; i++)
  {
    int disp_pin = 37-i;
    turn_off_display();
    for(int j = 0; j < 7; j++){
      digitalWrite(29-j, smile[i][j]);
    }
    digitalWrite(disp_pin, LOW);
  }
  countdown--;
  if(countdown <= 0){
    countdown = 3000;
    task_self_quit();
  }

}

// Helper function for the 7 segment display
// Takes an int, converts it into 4 numbers for the display
void int_to_seg(int target){
  for (int i = 0; i < 4; i++) {
    digits[i] = target % 10;
    target /= 10;
  }
}

// Takes in a number, and writes it to the 7 segment display
void sevenSeg_Digit_Write(int digit) {
  int start = 29;
  for (int i = 0; i < 7; i++){
    digitalWrite(start, seven_seg_digits[digit][i]);
    start--;
  }
}

// Resets the 7 segment display
void turn_off_display(){
  digitalWrite(SEG_DISP4, HIGH);
  digitalWrite(SEG_DISP3, HIGH);
  digitalWrite(SEG_DISP2, HIGH);
  digitalWrite(SEG_DISP1, HIGH);
}
