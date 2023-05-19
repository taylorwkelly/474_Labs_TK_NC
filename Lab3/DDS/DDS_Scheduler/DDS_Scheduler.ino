#include "DataDriven.h";


TCB TCB_List[N_TASKS];

Task t_task1;
Task t_task2;
Task t_task3;
Task t_task4_0; // Countdown
Task t_task4_1; // Music play
Task t_task4_2; // Music freq
Task t_task5;

Task *t_ptr;

Task task_arr[7] = {t_task1, t_task2, t_task3, t_task4_0, t_task4_1, t_task4_2, t_task5};

void (*func_ptr_list[N_TASKS]) (void *arg);
void (*runningTasks[N_TASKS]) (void *arg);


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

  //Need to set up specific values



}

void loop() {
  // put your main code here, to run repeatedly:

}


void task_self_quit(){

}
void task_start(TCB *task){

}
void task1(void *p){

}
void task2(void *p){

}
void task3(void *p){
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

}

int* int_to_7Seg(int target){

}
void task4_0(void *p){

}
void task4_1(void *p){

}
void task4_2(void *p){

}
void task5(void *p){

}