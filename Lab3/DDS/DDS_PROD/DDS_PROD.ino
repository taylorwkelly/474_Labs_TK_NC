#include "DataDriven.h";

TCB TCB_List[N_TASKS];
//TCB Sleeping_Tasks[N_TASKS];
TCB Dead_Tasks[N_TASKS];

TCB *tcb_list_ptr = &TCB_List[0];

Task t_task1;
Task t_task2;
Task t_task3;
Task t_task4_0; // Countdown
Task t_task4_1; // Music play
Task t_task4_2; // Music freq
Task t_task5;

Task *t_ptr;

int current_running_task_index, dead_task_index;
int task_count, dead_count;

Task task_arr[6] = {t_task1, t_task2, t_task3, t_task4_0, t_task4_1, t_task5};


// Contains a pointer to each of the tasks
void (*func_ptr_list[N_TASKS]) ();

void (*runningTasks[N_TASKS]) ();
void (*waitingTasks[N_TASKS]) ();
void (*deadTasks[N_TASKS]) ();

int digits[4] = {0};

void setup() {
  Serial.begin(9600);
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


  //Task ID will be equal to where it is initialized within the TASK List
  t_task1 = {0, "LED Flash", 0};
  t_task2 = {1, "Mario", 0};
  t_task3 = {2, "7 Segment LED", 0};
  t_task4_0 = {3, "7 Seg Countdown", 0};
  t_task4_1 = {4, "Music Play", 0};
  t_task5 = {5, "Supervisor", 0};

  Task t_task4 = {4, "Count Music w Freq", 0};

  
  // Adding all the tasks to the pointer list
  // Might need to add address
  func_ptr_list[0] = task1;
  func_ptr_list[1] = task2;
  func_ptr_list[2] = task3;
  func_ptr_list[3] = task4_0;
  func_ptr_list[4] = task4_1;
  func_ptr_list[5] = task5;

  // Initializing all the TCBs to defaults
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
  TCB_List[i].status = ACTIVE;
  TCB_List[i].delay = 0;
  i++;
  task_count++;

  // for(int i; i < 7; i++){
  //   TCB_List[i].task = task_arr[i];
  //   TCB_List[i].fn = func_ptr_list[i];
  //   TCB_List[i].arg_ptr = NULL;
  //   TCB_List[i].status = SLEEPING;
  //   TCB_List[i].delay = SLEEPING;
  // }
  TCB_List[i+1].fn = NULL;

  /*

    TCB_List[i].task = task_arr[5];
    TCB_List[i].fn = task4_2;
    TCB_List[i].arg_ptr = NULL;
    TCB_List[i].status = SLEEPING;
    TCB_List[i].delay = SLEEPING;

    TCB_List[i].task = task_arr[6];
    TCB_List[i].fn = task5;
    TCB_List[i].arg_ptr = NULL;
    TCB_List[i].status = SLEEPING;
    TCB_List[i].delay = SLEEPING;
  */



}

void loop() {
  // put your main code here, to run repeatedly:
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
  if(TCB_List[current_running_task_index].fn == NULL && current_running_task_index == 0){
    // Means that there are no tasks to run, and theres nothing to do
  } else{
    // Runs the tasks that are active
    while(TCB_List[current_running_task_index].fn != NULL){
      switch(TCB_List[current_running_task_index].status){

        case(ACTIVE):
        run_task(TCB_List[current_running_task_index].fn);

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

void task_start(TCB *task){
  //Adds the task back in at the end of the list
  //TCB tcb = *(task);
  task->status = ACTIVE;
  task->task.timesStarted_Restarted++;
  // Add logic to remove from the dead task list;
  //Dead_Tasks[task->task.id]
}



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
      //task_self_quit();
    }
    time++;
    if(count >= 5){
      time = 0;
      count = 0;
      task_self_quit();
      return;
    }
}

void task2() {
    // Plays the song, then sleeps for 4 seconds
    //Each note will be 100 ms
    static int time = 0;
    static int bpm = 0;
    // Goes to each note
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
      //task_start(&TCB_List[0]);
      sleep_task(4000);
      //task_self_quit();
    }
    time++;
}


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


  /*
Ard.  7-Seg Pin
 29	  11 (A)
 28	  7 (B)
 27	  4 (C)
 26	  2 (D)
 25	  1 (E)
 24	  10 (F)
 23 	  5 (G)
 22 	  3 (Dot P)

 34   12 (Dig. 1)
 35   9 (Dig 2)
 36   8 (Dig 3)
 37   6 (Dig 4)

*/
void int_to_seg(int target){
  for (int i = 0; i < 4; i++) {
    digits[i] = target % 10;
    target /= 10;
  }
}

//ID: 3

void sevenSegWrite(int digit) {
  int start = 29;
  for (int i = 0; i < 7; i++){
    digitalWrite(start, seven_seg_digits[digit][i]);
    start--;
  }
}

void turn_off_display(){
  digitalWrite(SEG_DISP4, HIGH);
  digitalWrite(SEG_DISP3, HIGH);
  digitalWrite(SEG_DISP2, HIGH);
  digitalWrite(SEG_DISP1, HIGH);
}

void task4_0(){
  static int time = 0;
  static int countdown = 5000;
  if(time = 100){
    int_to_seg(countdown);
    time = 0;
    countdown--;
  }
  for (int i = 0; i < 4; i++)
  {
    
    sevenSegWrite(digits[i]);
    digitalWrite(37-i, LOW);
    delayMicroseconds(15);
    digitalWrite(37-i, HIGH);
  }
  //turn_off_display();
  if(countdown == 0){
    time = 0;
    countdown = 5000;
    turn_off_display();
    task_self_quit();
    task_start(&TCB_List[4]);
    return;
  }
}
  //turn_off_display();

// Task to play the music
//ID: 4
void task4_1(){
  // Plays the song, then sleeps for 4 seconds
  //Each note will be 100 ms
  static int time = 0;
  static int bpm = 0;
  // Goes to each note
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
    sevenSegWrite(digits[i]);
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
Task 5: This task will be a supervisor that starts and stops other tasks. Perform the tasks
according to this schedule:
a) Task 1 runs all the time.
b) Task 2 runs at the start but stops after playing the theme 2 times.
c) After Task 2, start a count-down (on the 7-segment display) for 3 seconds
and then restarts task 2 (original definition above) for one final time.
d) Display a “smile” for 2 seconds (See Appendix B) (code this as a new task to be
controlled by Task 5). The 2 second interval begins after completion of part 5c.
e) Stop all tasks, except “a) Task 1” in this list.

*/


//ID:5
void task5(){
}