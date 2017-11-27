void AnimWrapper1(void *pvParameters )
{
  for (;;) {
    OneAtATime();

    //    if (Pressed[0]) {
    //      Pressed[0] = false;
    //      SineWave();
    //    }
    //    else
    //      rDelay(150);
  }
}

void AnimWrapper2(void *pvParameters )
{
  for (;;) {
    
    if (effectIndex==0) {
            timeZero = millis();
            Serial.print('0');
            effectIndex++;
    }
    if (effectIndex==1 && (millis() - timeZero) >= (timeOffset+316) ) {
      effectIndex++;
      //Serial.print('1');
      Explode(CRGB::White, 200);
    }
    
    if ( effectIndex == 2 && (millis() - timeZero) >= (timeOffset+1274)) {
      effectIndex++;
      SetAll(CRGB::Black);
    }

    if ( effectIndex == 3 && (millis() - timeZero) >= (timeOffset+1757)) {
      effectIndex++;
      DrawXZPlane(0, CRGB::White);
    }
    
    if ( effectIndex == 4 && (millis() - timeZero) >= (timeOffset+1918)) {
      effectIndex++;
      DrawXZPlane(1, CRGB::White);
    }
    
    if ( effectIndex == 5 && (millis() - timeZero) >= (timeOffset+2079)) {
      effectIndex++;
      DrawXZPlane(2, CRGB::White);
    }
    
    if ( effectIndex == 6 && (millis() - timeZero) >= (timeOffset+2226)) {
      effectIndex++;
      DrawXZPlane(3, CRGB::White);
    }
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
//  xTaskCreate(
//    AnimWrapper1
//    ,  (const portCHAR *)"Task1"   // A name just for humans
//    ,  128  // This stack size can be checked & adjusted by reading the Stack Highwater
//    ,  NULL
//    ,  0  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
//    ,  NULL );

  xTaskCreate(
    AnimWrapper2
    ,  (const portCHAR *)"Task2"   // A name just for humans
    ,  128  // This stack size can be checked & adjusted by reading the Stack Highwater
    ,  NULL
    ,  0  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    ,  NULL );


  //  xTaskCreate(
  //    buttonWrapper
  //    ,  (const portCHAR *)"buttonWrapper"   // A name just for humans
  //    ,  128  // This stack size can be checked & adjusted by reading the Stack Highwater
  //    ,  NULL
  //    ,  0  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
  //    ,  NULL );
}

