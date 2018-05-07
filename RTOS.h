int button00 = 0;
int button01 = 1;
int button02 = 2;
int button03 = 3;
int button04 = 4;
int button05 = 5;
int button06 = 6;
int button07 = 7;
int button08 = 8;
int button09 = 9;

void _ExecuteX(void *pvParameters)
{
  int btnIndex = *(int *)pvParameters;
  while (1) {
    if (Pressed[btnIndex] ) {
      byte rate = 60;
      byte nTimes = 1;
      byte effect = ButtonToEffect(btnIndex);

      switch (effect)
      {
        case FX_Clear: SetAll(bgColor); break;
        case FX_Explode: Explode(CRGB::White, 200); break;
        case FX_GradualUp: BouncePlane(1, nTimes, fgColor, 100); SetAll(bgColor); break;
        case FX_GradualSide: BouncePlane(2, nTimes, fgColor, 100); SetAll(bgColor); break;
        case FX_Char1: DrawChar(1, 0, 7, '1'); ComingTowards(); break;
        case FX_Char2: DrawChar(1, 0, 7, '2'); ComingTowards(); break;
        case FX_Char3: DrawChar(1, 0, 7, '3'); ComingTowards(); break;
        case FX_FlipBottomToFront: FlipBottomToFront(fgColor, rate); break;
        case FX_FlipFrontToLeft: FlipFrontToLeft(fgColor, rate); break;
        case FX_FlipLeftToBack: FlipLeftToBack(fgColor, rate); break;
        case FX_FlipBackToBottom: FlipBackToBottom(fgColor, rate); break;
        case FX_FlashLineXAlongZ: FlashLineXAlongZ(0, fgColor); break;
        case FX_SlidingCubes: SlidingCubes(); break;
        default: break;
        //StaticHatXY();
        //GrowFromCenter(0, fgColor, rate); 
        //ShrinkToCenter(0, fgColor, rate); 
      }

      Pressed[btnIndex] = false;
    }
    rDelay(50);
  }
}

void _Believer(void *pvParameters)
{
  for (;;) {
    Believer();
  }
}

void _ReadButtons(void *pvParameters)
{
  for (;;) {
    ReadButtons();
    //rDelay(50); // Give other tasks a chance to run
  }
}

void SetupRTOS()
{
  xTaskCreate(_ReadButtons, NULL, 128, NULL, 0, NULL);
  
  xTaskCreate(_ExecuteX, NULL, 128, &button00, 1, NULL);
  xTaskCreate(_ExecuteX, NULL, 128, &button01, 1, NULL);
  xTaskCreate(_ExecuteX, NULL, 128, &button02, 1, NULL);
  xTaskCreate(_ExecuteX, NULL, 128, &button03, 1, NULL);
  xTaskCreate(_ExecuteX, NULL, 128, &button04, 1, NULL);
  xTaskCreate(_ExecuteX, NULL, 128, &button05, 1, NULL);
  xTaskCreate(_ExecuteX, NULL, 128, &button06, 1, NULL);
  xTaskCreate(_ExecuteX, NULL, 128, &button07, 1, NULL);
//  xTaskCreate(_ExecuteX, NULL, 128, &button08, 1, NULL);
//  xTaskCreate(_ExecuteX, NULL, 128, &button09, 1, NULL);

  //xTaskCreate(_Believer, NULL, 128, NULL, 1, NULL);
}

