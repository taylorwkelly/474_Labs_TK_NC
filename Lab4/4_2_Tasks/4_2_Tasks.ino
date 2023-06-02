#include <arduinoFFT.h>
#include <Arduino_FreeRTOS.h>
#include "4_2_Tasks.h"


void setup() {

  // put your setup code here, to run once:
  Serial.begin(19200);

  while (!Serial){
    ;
  }

  xTaskCreate(
    offBoardLED_task, //Function for task
    "LED Offboard",   //Name of task
    128,              //Stack size
    NULL,             //Parameters
    3,                //Priority
    NULL);            //Handle
/*
    vTaskCreate(
    offBoardLED_task, //Function for task
    "LED Offboard",   //Name of task
    128,              //Stack size
    NULL,             //Parameters
    3,                //Priority
    NULL);            //Handle

    vTaskCreate(
    offBoardLED_task, //Function for task
    "LED Offboard",   //Name of task
    128,              //Stack size
    NULL,             //Parameters
    3,                //Priority
    NULL);            //Handle

    */

  // Create the tasks needed here

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
      vTaskDelay(200 /portTICK_PERIOD_MS );
    }
    TIMER_4_TOP = stream[songIndex];
    vTaskDelay(time_array[songIndex] / portTICK_PERIOD_MS);
    songIndex++;
  }

}
void FFT_task(void *parameters){

}


