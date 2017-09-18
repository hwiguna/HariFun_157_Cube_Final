//void SuperNova(int expandRate, int collapseRate, CRGB c)
//{
//  //-- Expand --
//  for (byte i=0; i<4; i++)
//  {
//    Point a = {3-i, 3-i, 3-i};
//    Point b = {3+i, 3+i, 3+i};
//    DrawBox( a,b, CRGB::Red);
//    FastLED.delay(expandRate);
//  }
//}

bool HasCloud()
{
  bool hasCloud = false;
//  for (int x = 0; x < 8; x++)
//    for (int z = 0; z < 8; z++) {
//      if (leds[ ToIndex(x, 7, z) ] != CRGB::Black ) {
//        hasCloud = true;
//        break;
//      }
//    }
  return hasCloud;
}

void Rain()
{
  while (HasCloud())
  {

  }

}
void LiftUp(int animRate)
{
  for (int i = 0; i <= 6; i++)
  {
    for (int x = 0; x < 8; x++)
      for (int z = 0; z < 8; z++) {
        if ( (4+i)<=7)
          leds[ ToIndex(x, 4 + i, z) ] = leds[ ToIndex(x, 3 + i, z) ];
        leds[ ToIndex(x, i, z) ] = CRGB::Black;
      }
    FastLED.delay(animRate);
  }
}

void SlidingCubes()
{
  int animRate = 100;

  // Red drop from top
  for (int i = 7; i >= 0; i--) {
    Point a1 = {0, i, 0};
    Point b1 = {3, i + 3, 3};
    DrawCube(a1, b1, CRGB::Red);
    FastLED.delay(animRate);
    if (i > 0) DrawCube(a1, b1, CRGB::Black);
  }

  // Front-Left
  for (int i = 0; i < 5; i++) {
    Point a1 = {i, 0, 0};
    Point b1 = {i + 3, 0 + 3, 0 + 3};
    DrawCube(a1, b1, CRGB::Red);
    FastLED.delay(animRate);
    if (i < 4) DrawCube(a1, b1, CRGB::Black);
  }

  // Blue drop from top
  for (int i = 7; i >= 0; i--) {
    Point a1 = {0, i, 4};
    Point b1 = {3, i + 3, 7};
    DrawCube(a1, b1, CRGB::Blue);
    FastLED.delay(animRate);
    if (i > 0) DrawCube(a1, b1, CRGB::Black);
  }

  // Back-Left
  for (int i = 0; i < 5; i++) {
    Point a2 = {0, 0, 4 - i};
    Point b2 = {3, 3, 4 - i + 3};
    DrawCube(a2, b2, CRGB::Blue);
    FastLED.delay(animRate);
    if (i < 4) DrawCube(a2, b2, CRGB::Black);
  }

  // Blue drop from top
  for (int i = 7; i >= 0; i--) {
    Point a1 = {0, i, 4};
    Point b1 = {3, i + 3, 7};
    DrawCube(a1, b1, CRGB::Blue);
    FastLED.delay(animRate);
    if (i > 0) DrawCube(a1, b1, CRGB::Black);
  }

  // Back-Left
  for (int i = 0; i < 5; i++) {
    Point a1 = {i, 0, 4};
    Point b1 = {i + 3, 0 + 3, 7};
    DrawCube(a1, b1, CRGB::Blue);
    FastLED.delay(animRate);
    if (i < 4) DrawCube(a1, b1, CRGB::Black);
  }


  // Red drop from top
  for (int i = 7; i >= 0; i--) {
    Point a1 = {0, i, 4};
    Point b1 = {3, i + 3, 7};
    DrawCube(a1, b1, CRGB::Red);
    FastLED.delay(animRate);
    if (i > 0) DrawCube(a1, b1, CRGB::Black);
  }

  delay(1000);

  LiftUp(animRate * 2);
  Rain();

  delay(1000);

  FastLED.clear();
}

//void RetroFromFuture()
//{
//  SuperNova(500,500, CRGB::Red);
//}

