const byte firstLed = 2;
const byte lastLed = firstLed + 9;

const byte firstButton = 14;
const byte lastButton = firstButton + 5;

#include <Arduino_FreeRTOS.h>

void SetupIOPorts()
{
  for (byte i = firstLed; i <= lastLed; i++)
    pinMode(i, OUTPUT);

  for (byte i = firstButton; i <= lastButton; i++) {
    pinMode(i, INPUT);
    digitalWrite(i, HIGH);  // set pullup on analog pin
  }
  //pinMode(button12, INPUT_PULLUP);
}

void Effect1()
{
  for (byte i = firstLed; i <= lastLed; i++)
  {
    digitalWrite(i, HIGH); // turn the LED on (HIGH is the voltage level)
    vTaskDelay( 100 / portTICK_PERIOD_MS ); // wait for one tenth of a second
    digitalWrite(i, LOW);    // turn the LED off by making the voltage LOW
  }
}

void Effect2()
{
  for (byte i = lastLed; i >= firstLed; i--)
  {
    digitalWrite(i, HIGH); // turn the LED on (HIGH is the voltage level)
    vTaskDelay( 100 / portTICK_PERIOD_MS ); // wait for one tenth of a second
    digitalWrite(i, LOW);    // turn the LED off by making the voltage LOW
  }
}

void TaskButtonHandler1(void *pvParameters)
{
  while (true) // This task never exits.  It's given slice of time by xTaskCreate()
  {
    if (digitalRead(firstButton) == LOW)
    {
      Effect1();
    }
    vTaskDelay(1);  // one tick delay (15ms) in between reads for stability
  }
}

void TaskButtonHandler2(void *pvParameters)
{
  while (true) // This task never exits.  It's given slice of time by xTaskCreate()
  {
    if (digitalRead(lastButton) == LOW)
    {
      Effect2();
    }
    vTaskDelay(1);  // one tick delay (15ms) in between reads for stability
  }
}


void TaskBlink(void *pvParameters)
{
  while (true) // This task never exits.  It's given slice of time by xTaskCreate()
  {
    digitalWrite(firstLed + 3, HIGH); // turn the LED on (HIGH is the voltage level)
    vTaskDelay( 50 / portTICK_PERIOD_MS ); // wait for one tenth of a second
    digitalWrite(firstLed + 3, LOW);    // turn the LED off by making the voltage LOW
    vTaskDelay(500 / portTICK_PERIOD_MS);  // one tick delay (15ms) in between reads for stability
  }
}

void SetupRTOS()
{
  //-- Setup Tasks 1 --
  xTaskCreate(
    TaskButtonHandler1
    ,  NULL
    ,  128  // Stack size
    ,  NULL
    ,  2 // Priority
    ,  NULL );


  //-- Setup Tasks 2 --
  xTaskCreate(
    TaskButtonHandler2
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
    ,  1 // Priority
    ,  NULL );
}

void setup() {
  SetupIOPorts();
  SetupRTOS();
}

void loop() {}

