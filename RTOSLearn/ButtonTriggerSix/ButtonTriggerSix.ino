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

void Effect6()
{
  for (byte i = lastLed; i >= firstLed; i--)
  {
    digitalWrite(i, HIGH); // turn the LED on (HIGH is the voltage level)
    vTaskDelay( 100 / portTICK_PERIOD_MS ); // wait for one tenth of a second
    digitalWrite(i, LOW);    // turn the LED off by making the voltage LOW
  }
}

void EffectBlink(int ledPin)
{
  for (byte n = 0; n < 3; n++)
  {
    digitalWrite(ledPin, HIGH); // turn the LED on (HIGH is the voltage level)
    vTaskDelay( 100 / portTICK_PERIOD_MS ); // wait for one tenth of a second
    digitalWrite(ledPin, LOW);    // turn the LED off by making the voltage LOW
    vTaskDelay( 100 / portTICK_PERIOD_MS ); // wait for one tenth of a second
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
    if (digitalRead(firstButton + 1) == LOW)
    {
      EffectBlink(firstLed + 1);
    }
    vTaskDelay(1);  // one tick delay (15ms) in between reads for stability
  }
}

void TaskButtonHandler3(void *pvParameters)
{
  while (true) // This task never exits.  It's given slice of time by xTaskCreate()
  {
    if (digitalRead(firstButton + 2) == LOW)
    {
      EffectBlink(firstLed + 2);
    }
    vTaskDelay(1);  // one tick delay (15ms) in between reads for stability
  }
}

void TaskButtonHandler4(void *pvParameters)
{
  while (true) // This task never exits.  It's given slice of time by xTaskCreate()
  {
    if (digitalRead(firstButton + 3) == LOW)
    {
      EffectBlink(firstLed + 3);
    }
    vTaskDelay(1);  // one tick delay (15ms) in between reads for stability
  }
}

void TaskButtonHandler5(void *pvParameters)
{
  while (true) // This task never exits.  It's given slice of time by xTaskCreate()
  {
    if (digitalRead(firstButton + 4) == LOW)
    {
      EffectBlink(firstLed + 4);
    }
    vTaskDelay(1);  // one tick delay (15ms) in between reads for stability
  }
}

void TaskButtonHandler6(void *pvParameters)
{
  while (true) // This task never exits.  It's given slice of time by xTaskCreate()
  {
    if (digitalRead(lastButton) == LOW)
    {
      Effect6();
    }
    vTaskDelay(1);  // one tick delay (15ms) in between reads for stability
  }
}


void TaskBlink(void *pvParameters)
{
  while (true) // This task never exits.  It's given slice of time by xTaskCreate()
  {
    digitalWrite(firstLed + 4, HIGH); // turn the LED on (HIGH is the voltage level)
    vTaskDelay( 20 / portTICK_PERIOD_MS ); // wait for one tenth of a second
    digitalWrite(firstLed + 4, LOW);    // turn the LED off by making the voltage LOW
    vTaskDelay(1000 / portTICK_PERIOD_MS);  // one tick delay (15ms) in between reads for stability
  }
}

void SetupRTOS()
{
  //-- Setup Tasks 1 --
  xTaskCreate(TaskButtonHandler1, NULL, 128, NULL, 2, NULL); // name, Stack size, param, Priority, handle
  xTaskCreate(TaskButtonHandler2, NULL, 128, NULL, 2, NULL);
  xTaskCreate(TaskButtonHandler3, NULL, 128, NULL, 2, NULL);
  xTaskCreate(TaskButtonHandler4, NULL, 128, NULL, 2, NULL);
  xTaskCreate(TaskButtonHandler5, NULL, 128, NULL, 2, NULL);
  xTaskCreate(TaskButtonHandler6, NULL, 128, NULL, 2, NULL);

  //xTaskCreate(TaskBlink, NULL, 128, NULL, 1, NULL); // Setup blink
}

void setup() {
  SetupIOPorts();
  SetupRTOS();
}

void loop() {}

