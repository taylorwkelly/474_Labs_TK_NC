/* University of Washington
 * ECE/CSE 474,  06/09/2023
 *
 *   Noah Crouch
 *   Taylor Kelly
 *
 *   Lab 4: Final Project
 *   Tasks 1 and 2
 *
    Program that utilizes FreeRTOS in order to execute a variety of tasks,
    such as blinking an LED and playing a song.
 */

#include "4_2_Tasks.h"

// Initializing global variables like queues, handles, and FFT data
QueueHandle_t queue1;
QueueHandle_t queue2;

TaskHandle_t task_3_1_handle;
TaskHandle_t task_4_handle;

double data[samples];
double *dataPoint = data;

// Setup function
void setup() {

  queue1 = xQueueCreate(2, sizeof(double *));
  queue2 = xQueueCreate(2, sizeof(unsigned long));
  // put your setup code here, to run once:
  Serial.begin(19200);

  while (!Serial){
    ;
  }
  Serial.println();
  
  /*
  Task Creation
  Creates Tasks for:
  1. Blinking an offboard LED (Pin 12)
  2. Playing a song on a 8-ohm speaker (Pin 6)
  3_0. Generating random doubles, and starting task 3_1
  3_1. Sends FFT data to 4 and records the time taken to compute an FFT
    Handle: task_3_1_handle
  4. Computes an FFT given an array of doubles, then sends data about the time taken to task 3_1
    Handle: task_4_handle
  */

  xTaskCreate(
    offBoardLED_task, //Function for task
    "LED Offboard",   //Name of task
    100,              //Stack size
    NULL,             //Parameters
    1,                //Priority
    NULL);            //Handle

  xTaskCreate(
    bloodyStream_task, //Function for task
    "Bloody Stream",   //Name of task
    128,              //Stack size
    NULL,             //Parameters
    2,                //Priority
    NULL);            //Handle

   xTaskCreate(
    FFT_task_3_0, //Function for task
    "RT3pt0",   //Name of task
    128,              //Stack size
    NULL,             //Parameters
    1,                //Priority
    NULL);            //Handle


   xTaskCreate(
    FFT_task_3_1, //Function for task
    "RT3pt1",   //Name of task
    128,              //Stack size
    NULL,             //Parameters
    5,                //Priority
    &task_3_1_handle);            //Handle

   xTaskCreate(
    dataRead_FFT, //Function for task
    "RT4",   //Name of task
    3500,              //Stack size
    NULL,             //Parameters
    4,                //Priority
    &task_4_handle);            //Handle


  // Starts the scheduler
  delay(500);
  vTaskStartScheduler();

}

void loop() {
  /*
  Nothing in the loop area, as it all operates within the setup portion of Arduino

  */
}


/*
OffBoard LED
Blinks an off-board LED on for 100ms, then off for 200ms
*/
void offBoardLED_task(void *parameters){
  // Sets the output of the offboard LED
  pinMode(LED_OFFBOARD, OUTPUT);

  while(1){
    //On for 100ms
    digitalWrite(LED_OFFBOARD, HIGH);
    vTaskDelay(100/portTICK_PERIOD_MS);
    //Off for 200ms
    digitalWrite(LED_OFFBOARD, LOW);
    vTaskDelay(200/portTICK_PERIOD_MS);
  }

}

/*
Music Playing Task
Has a song play for it's entirety, then waits 1.5 seconds to repeat
Once the song has played 3 times, the task will suspend itself.
*/
void bloodyStream_task(void *parameters){
  // Timer Setup
  TIMER_4_TOP = 0;
  TIMER_4_CTRL_REG_A |= TIMER_4_CTRL_REG_A_MASK;
  TIMER_4_CTRL_REG_B |= TIMER_4_CTRL_REG_B_MASK;

  // Sets Pin 6 to be the output pin
  DATA_DIRECTION_REG_SPKR |= BIT3;
  TIMER_4_ALLOW_REG &= ~BIT3;
  songIndex = 0;
  songCount = 0;

  while(1){
    if(songIndex > 44){
      songIndex = 0;
      vTaskDelay(1500 /portTICK_PERIOD_MS );
      songCount++;
    }
    if(songCount >= 3){
      vTaskSuspend(NULL);
    }
    TIMER_4_TOP = stream[songIndex];
    vTaskDelay(time_array[songIndex] / portTICK_PERIOD_MS);
    songIndex++;
  }

}


/*
Setup Task for FFT
Computes *samples* number of doubles, which are loaded into an array
Once the array is fully loaded, will call Task 3_1 to start, and halt itself
*/
void FFT_task_3_0(void *parameters){
  vTaskDelay(200 / portTICK_PERIOD_MS);
  while(1){
    //array of N pseudo random doubles
    for(int i = 0; i < samples; i++){
      data[i] = 0.0 + ((double) rand()) / RAND_MAX;
    }
    // Calls FFT_task_3_1, and halts self
    vTaskResume(task_3_1_handle);
    vTaskSuspend(NULL);
  }
}

/*
Task 3_1
Sends a pointer of the random doubles array to Task 4, then waits for a response
Once a response is received, will receive the time taken to execute Task 4 from queue2
This repeats 5 times before the task suspends itself.
*/
void FFT_task_3_1(void *parameters){
  vTaskSuspend(NULL);
  while(1){
    // run loop 5 times
    for(int i = 0; i < 5; i++){
      unsigned long temp;
      // Send a pointer to the data to the queue
      xQueueSendToBack(queue1, &dataPoint, 1);
      // Wait for data to come from the 2nd queue to resume
      vTaskResume(task_4_handle);
      while(eTaskGetState(task_4_handle) != eSuspended){
        vTaskDelay(50 / portTICK_PERIOD_MS);
      }
      xQueueReceive(queue2, &temp, 0);
      Serial.println("Computation time:");
      Serial.println(temp);
    }
    vTaskSuspend(task_4_handle);
    vTaskSuspend(NULL);
  }
}

/*
Task 4: FFT computation
Reads in data from queue 1 about a array of doubles, then takes that array to compute the
Fast Fourier Transform of the data.
Records the time of how long the computation takes, and send the data to queue2 to be read
by Task 3_1
When the FFT has been computed, the task halts itself.
*/
void dataRead_FFT(void *parameters){
  double vReal[samples];
  double vImag[samples];
  double* fromData;
  arduinoFFT fft = arduinoFFT(); /* Create FFT object */
  //Serial.println(uxTaskGetStackHighWaterMark( NULL ));
  vTaskSuspend(NULL);
  while(1){
    xQueueReceive(queue2, &fromData, 1);
    // The queue system is currently not working
    for(int i = 0; i<samples; i++){
      vReal[i] = *(dataPoint+i);
      vImag[i] = 0.0;
    }
    // Now need to measure the wall clock time
    unsigned long start = millis();
    fft.Compute(vReal, vImag, samples, FFT_FORWARD);
    start = millis() - start;
    //Serial.println(uxTaskGetStackHighWaterMark( NULL ));
    xQueueSendToBack(queue2, &start, 0);
    //vTaskResume(task_3_1_handle);
    vTaskSuspend(NULL);
  }

}


