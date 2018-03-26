const byte firstLed = 2;
const byte lastLed = 9;

#include <Arduino_FreeRTOS.h>

void SetupIOPorts()
{
  for (byte i = firstLed; i <= lastLed; i++)
    pinMode(i, OUTPUT);
}

void Effect()
{
  for (byte i = 0; i < (lastLed - firstLed); i++)
    {
      digitalWrite(firstLed + i, HIGH); // turn the LED on (HIGH is the voltage level)
      vTaskDelay( 100 / portTICK_PERIOD_MS ); // wait for one tenth of a second
      digitalWrite(firstLed + i, LOW);    // turn the LED off by making the voltage LOW
    }
}

void TaskOncePerSecond(void *pvParameters)
{
  for (;;) // This task never exits.  It's given slice of time by xTaskCreate()
  {
    Effect();
    vTaskDelay(1000 / portTICK_PERIOD_MS);  // one tick delay (15ms) in between reads for stability
  }
}


void TaskBlink(void *pvParameters)
{
  for (;;) // This task never exits.  It's given slice of time by xTaskCreate()
  {
    digitalWrite(firstLed + 3, HIGH); // turn the LED on (HIGH is the voltage level)
      vTaskDelay( 50 / portTICK_PERIOD_MS ); // wait for one tenth of a second
      digitalWrite(firstLed + 3, LOW);    // turn the LED off by making the voltage LOW
    vTaskDelay(500 / portTICK_PERIOD_MS);  // one tick delay (15ms) in between reads for stability
  }
}

void SetupRTOS()
{
  //-- Setup running light --
  xTaskCreate(
    TaskOncePerSecond
    ,  NULL
    ,  128  // Stack size
    ,  NULL
    ,  2 // Priority
    ,  NULL );

  //-- Setup blink --
  xTaskCreate(
    TaskBlink
    ,  NULL
    ,  128  // Stack size
    ,  NULL
    ,  2 // Priority
    ,  NULL );
}

void setup() {
  SetupIOPorts();
  SetupRTOS();
}

void loop() {}

