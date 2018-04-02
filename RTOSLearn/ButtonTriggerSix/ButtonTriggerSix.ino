const byte firstLed = 2;
const byte lastLed = firstLed + 9;

const byte firstButton = 14;
const byte lastButton = firstButton + 5;

#include <Arduino_FreeRTOS.h>

//== SETUP ==

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

//== EFFECTS ==

void FirstToLast()
{
  for (byte i = firstLed; i <= lastLed; i++)
  {
    digitalWrite(i, HIGH); // turn the LED on (HIGH is the voltage level)
    vTaskDelay( 100 / portTICK_PERIOD_MS ); // wait for one tenth of a second
    digitalWrite(i, LOW);    // turn the LED off by making the voltage LOW
  }
}

void LastToFirst()
{
  for (byte i = lastLed; i >= firstLed; i--)
  {
    digitalWrite(i, HIGH); // turn the LED on (HIGH is the voltage level)
    vTaskDelay( 100 / portTICK_PERIOD_MS ); // wait for one tenth of a second
    digitalWrite(i, LOW);    // turn the LED off by making the voltage LOW
  }
}

void Marquee(int howManyTimes, int msDelay)
{
  for (byte n = 0; n < howManyTimes; n++)
  {
    for (byte c = 0; c < 3; c++)
    {
      for (byte i = firstLed; i <= lastLed; i++)
      {
        bool isOn = (i % 3) == c;
        digitalWrite(i, isOn ? HIGH : LOW); // turn the LED on (HIGH is the voltage level)
      }
      vTaskDelay( msDelay / portTICK_PERIOD_MS ); // wait for one tenth of a second
    }

    //-- Turn all off --
    for (byte i = firstLed; i <= lastLed; i++)
      digitalWrite(i, LOW);
  }
}

void MarqueeBackward(int howManyTimes, int msDelay)
{
  for (byte n = 0; n < howManyTimes; n++)
  {
    for (int c = 2; c >= 0; c--)
    {
      for (byte i = firstLed; i <= lastLed; i++)
      {
        bool isOn = (i % 3) == c;
        digitalWrite(i, isOn ? HIGH : LOW); // turn the LED on (HIGH is the voltage level)
      }
      vTaskDelay( msDelay / portTICK_PERIOD_MS ); // wait for one tenth of a second
    }

    //-- Turn all off --
    for (byte i = firstLed; i <= lastLed; i++)
      digitalWrite(i, LOW);
  }
}
  void EffectBlink(int ledPin)
  {
    for (byte n = 0; n < 3; n++)
    {
      digitalWrite(ledPin, HIGH); // turn the LED on (HIGH is the voltage level)
      vTaskDelay( 250 / portTICK_PERIOD_MS ); // wait for one tenth of a second
      digitalWrite(ledPin, LOW);    // turn the LED off by making the voltage LOW
      vTaskDelay( 250 / portTICK_PERIOD_MS ); // wait for one tenth of a second
    }
  }

  //== TASK HANDLERS ==

  void TaskButtonHandler1(void *pvParameters)
  {
    while (true) // This task never exits.  It's given slice of time by xTaskCreate()
    {
      if (digitalRead(firstButton) == LOW)
      {
        //EffectBlink(lastLed);
        Marquee(3, 150);
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
        //EffectBlink(lastLed - 1);
        MarqueeBackward(3,150);
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
        EffectBlink(lastLed - 2);
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
        EffectBlink(lastLed - 3);
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
        LastToFirst();
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
        FirstToLast();
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

