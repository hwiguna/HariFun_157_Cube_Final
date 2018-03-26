const byte firstLed = 2;
const byte lastLed = 9;

#include <Arduino_FreeRTOS.h>

void TaskBlinkOnceThenDie(void *pvParameters)  // This is a task.
{
  for (byte i = 0; i < (lastLed - firstLed); i++)
  {
    digitalWrite(firstLed + i, HIGH); // turn the LED on (HIGH is the voltage level)
    vTaskDelay( 100 / portTICK_PERIOD_MS ); // wait for one tenth of a second
    digitalWrite(firstLed + i, LOW);    // turn the LED off by making the voltage LOW
  }
  vTaskDelete( NULL );
}

void TaskBlinkRepeatedly(void *pvParameters)  // This is a task.
{
  for (;;)
  {
    for (byte i = 0; i < (lastLed - firstLed); i++)
    {
      digitalWrite(firstLed + i, HIGH); // turn the LED on (HIGH is the voltage level)
      vTaskDelay( 100 / portTICK_PERIOD_MS ); // wait for one tenth of a second
      digitalWrite(firstLed + i, LOW);    // turn the LED off by making the voltage LOW
    }
    vTaskDelay(1000 / portTICK_PERIOD_MS);  // one tick delay (15ms) in between reads for stability
  }
}


void TaskOncePerSecond(void *pvParameters)  // This is a task.
{
  for (;;)
  {
//    for (byte i = 0; i < (lastLed - firstLed); i++)
//    {
//      digitalWrite(firstLed + i, HIGH); // turn the LED on (HIGH is the voltage level)
//      vTaskDelay( 100 / portTICK_PERIOD_MS ); // wait for one tenth of a second
//      digitalWrite(firstLed + i, LOW);    // turn the LED off by making the voltage LOW
//    }
  TaskHandle_t xHandle = NULL;
  xTaskCreate(
        TaskBlinkOnceThenDie
        ,  NULL
        ,  128  // Stack size
        ,  NULL
        ,  1  // Priority
        ,  &xHandle );
        
    vTaskDelay(1000 / portTICK_PERIOD_MS);  // one tick delay (15ms) in between reads for stability
  }
}

void TaskReadButtons(void *pvParameters)  // This is a task.
{
  for (;;)
  {
    if (digitalRead(10) == 0)
    {
      xTaskCreate(
        TaskBlinkOnceThenDie
        ,  NULL
        ,  128  // Stack size
        ,  NULL
        ,  1  // Priority
        ,  NULL );

      //      for (byte i = 0; i < (lastLed - firstLed); i++)
      //      {
      //        digitalWrite(firstLed + i, HIGH); // turn the LED on (HIGH is the voltage level)
      //        vTaskDelay( 100 / portTICK_PERIOD_MS ); // wait for one tenth of a second
      //        digitalWrite(firstLed + i, LOW);    // turn the LED off by making the voltage LOW
      //      }

    }
    vTaskDelay(1000 / portTICK_PERIOD_MS);  // one tick delay (15ms) in between reads for stability
  }
}





// the setup function runs once when you press reset or power the board
void setup() {

  // initialize serial communication at 9600 bits per second:
//  Serial.begin(9600);
//
//  while (!Serial) {
//    ; // wait for serial port to connect. Needed for native USB, on LEONARDO, MICRO, YUN, and other 32u4 based boards.
//  }


  // initialize ports
  for (byte i = firstLed; i <= lastLed; i++)
    pinMode(i, OUTPUT);

  pinMode(10, INPUT_PULLUP);
  pinMode(11, INPUT_PULLUP);

  // Now set up two tasks to run independently.
//      xTaskCreate(
//        TaskBlink
//        ,  (const portCHAR *)"Blink"   // A name just for humans
//        ,  128  // This stack size can be checked & adjusted by reading the Stack Highwater
//        ,  NULL
//        ,  2  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
//        ,  NULL );

  //  xTaskCreate(
  //    TaskReadButtons
  //    ,  NULL
  //    ,  128  // Stack size
  //    ,  NULL
  //    ,  2 // Priority
  //    ,  NULL );


  //-- This by itself works --
//  xTaskCreate(
//    TaskBlinkRepeatedly
//    ,  NULL
//    ,  128  // Stack size
//    ,  NULL
//    ,  2 // Priority
//    ,  NULL );


  //-- Call blink repeatedly
  
  TaskHandle_t xHandle1 = NULL;
    xTaskCreate(
      TaskOncePerSecond
      ,  NULL
      ,  128  // Stack size
      ,  NULL
      ,  2 // Priority
      ,  &xHandle1 );

  // Now the task scheduler, which takes over control of scheduling individual tasks, is automatically started.
}

void loop()
{

}

