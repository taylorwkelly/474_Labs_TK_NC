#include "DataDriven.h";


TCB TCB_List[N_TASKS];
TCB Sleeping_Tasks[N_TASKS];
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

Task task_arr[7] = {t_task1, t_task2, t_task3, t_task4_0, t_task4_1, t_task4_2, t_task5};

void (*func_ptr_list[N_TASKS]) ();

void (*runningTasks[N_TASKS]) ();
void (*waitingTasks[N_TASKS]) ();
void (*deadTasks[N_TASKS]) ();



void setup() {
  t_task1 = {1, "LED Flash", 0, 0};
  t_task2 = {2, "Mario", 0, 0};
  t_task3 = {3, "7 Segment LED", 0, 0};
  t_task4_0 = {40, "7 Seg Countdown", 0, 0};
  t_task4_1 = {41, "Music Play", 0, 0};
  t_task4_2 = {42, "Music Freq", 0, 0};
  t_task5 = {5, "Supervisor", 0, 0};

  
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
  for(int i; i < 7; i++){
    TCB_List[i].task = task_arr[i];
    TCB_List[i].fn = func_ptr_list[i];
    TCB_List[i].arg_ptr = NULL;
    TCB_List[i].status = SLEEPING;
    TCB_List[i].delay = SLEEPING;
  }
  TCB_List[i].fn = NULL;

  /*
    TCB_List[i].task = task_arr[0];
    TCB_List[i].fn = task1;
    TCB_List[i].arg_ptr = NULL;
    TCB_List[i].status = SLEEPING;
    TCB_List[i].delay = SLEEPING;

    TCB_List[i].task = task_arr[1];
    TCB_List[i].fn = task2;
    TCB_List[i].arg_ptr = NULL;
    TCB_List[i].status = SLEEPING;
    TCB_List[i].delay = SLEEPING;

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
  if(TCB_List[current_running_task_index] == NULL && current_running_task_index != 0){
    current_running_task_index = 0;
  }
  if(TCB_List[current_running_task_index] == NULL && current_running_task_index == 0){
    // Means that there are no tasks to run, and theres nothing to do
  } else{
    // Runs the tasks that are active
    while(TCB_List[current_running_task_index] != NULL){
      switch(TCB_List[current_running_task_index].status){

        case(ACTIVE):
        run_task(TCB_List[current_running_task_index].fn);

        case(SLEEPING):
        TCB_List[current_running_task_index].delay -= 1;
        if(TCB_List[current_running_task_index].delay == 0){
          TCB_List[current_running_task_index].status = ACTIVE;
        }
        case(DEAD):
        //Should never get to this point
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
  TCB_List[current_running_task_index].state = SLEEPING;
}

void task_self_quit(){
  TCB_List[current_task_index].status = DEAD;
  Dead_Tasks[dead_task_index++] = TCB_List[current_task_index];
  TCB_List[current_task_index] = NULL;
  int i = current_task_index;
  while (TCB_List[i + 1] != NULL && i < N_TASKS){
    TCB_List[i] = TCB_List[i + 1];
    i++;
  }
  
}

void task_start(TCB *task){


}




void task1() {
    static int time;
    if (time < 250) {
        LEDPORT |= BIT4;
    } else if (time < 1000) {
        LEDPORT &= ~BIT4;
    } else{
      time = 0;
    }
    time++;
}

void task2() {
    // Plays the song, then sleeps for 4 seconds
    //Each note will be 100 ms
    static int time;
    static int songCount;
    // Goes to each note
    if (time == 100) {
        TIMER_4_TOP = song[songIndex++];
        time = 0;
    }
    if (songIndex > 21) {
        songIndex = 0;
        songCount++;
    } 
    if (songCount >= 2) {
      sleep_task(4000);
    }
}
void task3(){
  //Counts up by 1 every 100ms
  static int displayNumb;
  static int time;
  if(time == 100){
    displayNumb++;
    time = 0;
  }
  int* converted_numbs = int_to_7Seg(displayNumb);
  //Pin of the first digit, increases for each digit
  //Could probably put this into the if block, to make it not compute every time


  //Going to definetely need to change this part
  //For each digit on the display
  for(int j = 10; j < 14; j++){
    //For each part of the digit
    int conv_index;
    for(int pin = 2; pin < 10; pin++;){
      digitalWrite(pin, seven_seg_digits[*(converted_numbs + conv_index)][pin-2]);
      conv_index++;
    }

  }
  time++;
}
  /*
Ard.  7-Seg Pin
 2	  11 (A)
 3	  7 (B)
 4	  4 (C)
 5	  2 (D)
 6	  1 (E)
 7	  10 (F)
 8 	  5 (G)
 9 	  3 (Dot P)

 10   12 (Dig. 1)
 11   9 (Dig 2)
 12   8 (Dig 3)
 13   6 (Dig 4)
}
*/


int* int_to_7Seg(int target){
  int digits[4] = {0};
  int* ptr;
  ptr = &digits;
  int i = 0
  while(target > 0){
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