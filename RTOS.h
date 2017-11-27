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


void WaitFor(unsigned long timeToWaitFor)
{
  timeToWaitFor = timeToWaitFor + timeOffset;
  while ((millis() - timeZero) < timeToWaitFor) {};
}

void AnimWrapper2(void *pvParameters )
{
  for (;;) {
    
    if (effectIndex==0) {
      timeZero = millis();
      Serial.print('0');
      effectIndex++;
    }

    CRGB drumColor = CRGB::Red;
    
    WaitFor(316); Explode(CRGB::White, 200);
    WaitFor(1274); SetAll(CRGB::Black);
    
    WaitFor(1757); DrawXZPlane(0, drumColor); DrawXZPlane(1, drumColor);
    WaitFor(1918); DrawXZPlane(2, drumColor); DrawXZPlane(3, drumColor);
    WaitFor(2079); DrawXZPlane(4, drumColor); DrawXZPlane(5, drumColor);
    WaitFor(2226); DrawXZPlane(6, drumColor); DrawXZPlane(7, drumColor);

    WaitFor(3197); SetAll(CRGB::Black);

    WaitFor(3678); DrawXZPlane(0, drumColor); DrawXZPlane(1, drumColor);
    WaitFor(3836); DrawXZPlane(2, drumColor); DrawXZPlane(3, drumColor);
    WaitFor(3997); DrawXZPlane(4, drumColor); DrawXZPlane(5, drumColor);
    WaitFor(4145); DrawXZPlane(6, drumColor); DrawXZPlane(7, drumColor);
    
    WaitFor(5117); SetAll(CRGB::Black);

    WaitFor(5558); DrawXZPlane(0, drumColor); DrawXZPlane(1, drumColor);
    WaitFor(5759); DrawXZPlane(2, drumColor); DrawXZPlane(3, drumColor);
    WaitFor(5919); DrawXZPlane(4, drumColor); DrawXZPlane(5, drumColor);
    WaitFor(6070); DrawXZPlane(6, drumColor); DrawXZPlane(7, drumColor);
    
    WaitFor(7036); SetAll(CRGB::Black);

    //-- First things first...
    WaitFor(7927); DrawChar(1,0,7, '1');
    ComingTowards(); // Recede();

    WaitFor(11352); DrawZLine(0,0, drumColor); DrawZLine(0,1, drumColor); 
    WaitFor(11517); DrawZLine(0,2, drumColor); DrawZLine(0,3, drumColor); 
    WaitFor(11667); DrawZLine(0,4, drumColor); DrawZLine(0,5, drumColor);  
    WaitFor(11837); DrawZLine(0,6, drumColor); DrawZLine(0,7, drumColor); 

    // Second thing
    WaitFor(23147); SetAll(CRGB::Black); DrawChar(1,0,7, '2');
    ComingTowards(); // Recede();

    WaitFor(26000); SetAll(CRGB::Red);
    
    WaitFor(0xFFFFFF);
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

