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
    vTaskDelay(1000/portTICK_PERIOD_MS);
  }

}
void bloodyStream_task(void *parameters){
  TIMER_4_TOP = 0;
  

  // SET the FAST PWM MODE as well as allow OC4A to override pin
  // Also prescale the clock to clk/256
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
      //vTaskSuspend()
      xQueueReceive(queue2, &temp, 0);
      Serial.println("Computation time:");
      Serial.println(temp);
    }
    
    vTaskSuspend(task_4_handle);
    vTaskSuspend(NULL);
  }
}

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


