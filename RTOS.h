void AnimWrapper1(void *pvParameters )
{
  for (;;) {
    if (Pressed[0]) {
      Pressed[0] = false;
      SineWave();
    }
    else
      rDelay(150);
  }
}

void AnimWrapper2(void *pvParameters )
{
  
  for (;;) {
    if (Pressed[1]) {
      Pressed[1] = false;
      GrowFromCenter(0, CRGB::Red, animRate);
    }
    else
      rDelay(150);
  }
}


void buttonWrapper(void *pvParameters )
{
  
  for (;;) {
    ReadButtons();
    rDelay(10);
  }
}

void SetupRTOS()
{
  xTaskCreate(
    AnimWrapper1
    ,  (const portCHAR *)"Task1"   // A name just for humans
    ,  512  // This stack size can be checked & adjusted by reading the Stack Highwater
    ,  NULL
    ,  0  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    ,  NULL );

  xTaskCreate(
    AnimWrapper2
    ,  (const portCHAR *)"Task2"   // A name just for humans
    ,  128  // This stack size can be checked & adjusted by reading the Stack Highwater
    ,  NULL
    ,  0  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    ,  NULL );

    
  xTaskCreate(
    buttonWrapper
    ,  (const portCHAR *)"buttonWrapper"   // A name just for humans
    ,  128  // This stack size can be checked & adjusted by reading the Stack Highwater
    ,  NULL
    ,  0  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    ,  NULL );
}

