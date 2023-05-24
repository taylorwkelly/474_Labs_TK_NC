#include "DataDriven.h";


TCB TCB_List[N_TASKS];
//TCB Sleeping_Tasks[N_TASKS];
TCB Dead_Tasks[N_TASKS];


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

Task task_arr[7] = {t_task1, t_task2, t_task3, t_task4_0, t_task4_1, t_task4_2, t_task5};


// Contains a pointer to each of the tasks
void (*func_ptr_list[N_TASKS]) ();

void (*runningTasks[N_TASKS]) ();
void (*waitingTasks[N_TASKS]) ();
void (*deadTasks[N_TASKS]) ();

int digits[4];

void setup() {
  pinMode(13, OUTPUT);

  pinMode(22, OUTPUT);
  pinMode(23, OUTPUT);
  pinMode(24, OUTPUT);
  pinMode(25, OUTPUT);
  pinMode(26, OUTPUT);
  pinMode(27, OUTPUT);
  pinMode(28, OUTPUT);
  pinMode(29, OUTPUT);
  pinMode(30, OUTPUT);
  pinMode(31, OUTPUT);
  pinMode(32, OUTPUT);
  pinMode(33, OUTPUT);

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


  t_task1 = {1, "LED Flash", 0, 0};
  t_task2 = {2, "Mario", 0, 0};
  t_task3 = {3, "7 Segment LED", 0, 0};
  t_task4_0 = {4, "7 Seg Countdown", 0, 0};
  t_task4_1 = {5, "Music Play", 0, 0};
  t_task4_2 = {6, "Music Freq", 0, 0};
  t_task5 = {7, "Supervisor", 0, 0};

  
  // Adding all the tasks to the pointer list
  // Might need to add address
  func_ptr_list[0] = task1;
  func_ptr_list[1] = task2;
  func_ptr_list[2] = task3;
  func_ptr_list[3] = task4_0;
  func_ptr_list[4] = task4_1;
  func_ptr_list[5] = task4_2;
  func_ptr_list[6] = task5;

  // Initializing all the TCBs to defaults
  int i = 0;
  TCB_List[i].task = task_arr[0];
  TCB_List[i].fn = task1;
  TCB_List[i].arg_ptr = NULL;
  TCB_List[i].status = ACTIVE;
  TCB_List[i].delay = 0;
  i++;
  task_count++;

  TCB_List[i].task = task_arr[1];
  TCB_List[i].fn = task2;
  TCB_List[i].arg_ptr = NULL;
  TCB_List[i].status = ACTIVE;
  TCB_List[i].delay = 0;
  i++;
  task_count++;

  TCB_List[i].task = task_arr[2];
  TCB_List[i].fn = task3;
  TCB_List[i].arg_ptr = NULL;
  TCB_List[i].status = ACTIVE;
  TCB_List[i].delay = 0;
  i++;
  task_count++;

  // TCB_List[i].task = t_task3;
  // TCB_List[i].fn = task3;
  // TCB_List[i].arg_ptr = NULL;
  // TCB_List[i].status = ACTIVE;
  // TCB_List[i].delay = 0;
  //i++;
  // for(int i; i < 7; i++){
  //   TCB_List[i].task = task_arr[i];
  //   TCB_List[i].fn = func_ptr_list[i];
  //   TCB_List[i].arg_ptr = NULL;
  //   TCB_List[i].status = SLEEPING;
  //   TCB_List[i].delay = SLEEPING;
  // }
  TCB_List[i+1].fn = NULL;

  /*

    TCB_List[i].task = task_arr[2];
    TCB_List[i].fn = task3;
    TCB_List[i].arg_ptr = NULL;
    TCB_List[i].status = SLEEPING;
    TCB_List[i].delay = SLEEPING;

    TCB_List[i].task = task_arr[3];
    TCB_List[i].fn = task4_0;
    TCB_List[i].arg_ptr = NULL;
    TCB_List[i].status = SLEEPING;
    TCB_List[i].delay = SLEEPING;

    TCB_List[i].task = task_arr[4];
    TCB_List[i].fn = task4_1;
    TCB_List[i].arg_ptr = NULL;
    TCB_List[i].status = SLEEPING;
    TCB_List[i].delay = SLEEPING;

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
        }
      }
      current_running_task_index++;
    }
  }
}

void run_task(void (*fctptr) () ){
  fctptr();
}


/*
If a task calls task_self_quit() it should be removed from the TCB list and
its status set to DEAD. Keep a separate list of the dead tasks.

3.6. Another task can revive a dead task by calling task_start( tsk ) where
tsk here is a pointer to the TCB of a DEAD task. The task_start(tsk)
function should do this by changing tsk’s status to READY.


*/
void sleep_task(int timeToSleep){
  TCB_List[current_running_task_index].delay = timeToSleep;
  TCB_List[current_running_task_index].status = SLEEPING;
}


/*
halt_me() {
TaskList[t_curr].state = STATE_INACTIVE;
}
start_task(int task_id) {
TaskList[task_id].state = STATE_READY;
}
delay(int d) {
TaskList[t_curr].delay = d;
TaskList[t_curr].state = STATE_WAITING;
}
*/

/*
pseudocode for task_quit
halt_me() {
// 1. Identify which task is currently running (i.e.
// look at task_index)
// 2. Copy the function pointer from
// readytasks[task_index] to the
// haltedtasks array
// 3. Move the remaining tasks up in readytasks[] to
// fill the empty hole and copy NULL into the
// last element.
return;
}

*/
void task_self_quit(){
  TCB_List[current_running_task_index].status = DEAD;
  Dead_Tasks[dead_count] = TCB_List[current_running_task_index];
  //Need to remove the task instead of nulling it
  //TCB_List[current_running_task_index].fn = NULL;

  // Goes to spot where the task is to be removed
  // int i = current_running_task_index;
  // while(TCB_List[i + 1].fn != NULL && i < N_TASKS){
  //   TCB_List[i] = TCB_List[i + 1];
  //   i++;
  // }
  task_count--;
  dead_count++;
  
}

void task_start(TCB *task){
  //Adds the task back in at the end of the list
  task->status = ACTIVE;
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
      sleep_task(2000);
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
 22	  11 (A)
 23	  7 (B)
 24	  4 (C)
 25	  2 (D)
 26	  1 (E)
 27	  10 (F)
 28 	  5 (G)
 29 	  3 (Dot P)

 30   12 (Dig. 1)
 31   9 (Dig 2)
 32   8 (Dig 3)
 33   6 (Dig 4)
}
*/


int* int_to_7Seg(int target){
  int digits[4] = {0};
  int* ptr;
  ptr = &(digits[0]);
  int i = 0;
  while (target > 0){
    digits[i] = target % 10;
    target = target / 10;
  }
  return ptr;
}


void task4_0(void *p){

}
void task4_1(void *p){

}
void task4_2(void *p){

}
void task5(void *p){

}