//void SuperNova(int expandRate, int collapseRate, CRGB c)
//{
//  //-- Expand --
//  for (byte i=0; i<4; i++)
//  {
//    Point a = {3-i, 3-i, 3-i};
//    Point b = {3+i, 3+i, 3+i};
//    DrawBox( a,b, CRGB::Red);
//    rDelay(expandRate);
//  }
//}

bool HasOn()
{
  bool hasOn = false;
  for (int x = 0; x < 8; x++)
    for (int y = 0; y < 8; y++)
      for (int z = 0; z < 8; z++) {
        CRGB c = leds[ ToIndex(x, y, z) ];
        if ( c.red || c.green || c.blue ) {
          hasOn = true;
          break;
        }
      }
  return hasOn;
}

void Rain()
{
  //-- Create random list of top XY plane pixels --
  byte seq[64];

  for (byte i = 0; i < 64; i++)
    seq[i] = i;

  for (byte i = 0; i < 64; i++) {
    byte randomIndex = random(0, 64);
    byte t = seq[i];
    seq[i] = seq[ randomIndex];
    seq[randomIndex] = t;
  }

  byte i = 0;
  while (HasOn()) {      
      for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
          for (int z = 0; z < 8; z++) {
            int srcIndex =  ToIndex(x, y, z);
            if (y!=7 || (x == seq[i] % 8 && z==seq[i] / 8)) {
              int dest = y - 1;
              if (dest >= 0) {
                int destIndex = ToIndex(x, dest, z);
                leds[ destIndex ] = leds[ srcIndex ]; // Copy to the pixel below it
              }
              leds[srcIndex] = CRGB::Black; // Erase the pixel at previous location
            } // if needs to move this pixel
          } // for z
        } // for x
      } // for y
      
    rDelay(100);
    if (i<64) i++;

  } // while HasOn
}

void LiftUp(int animRate)
{
  for (int i = 0; i <= 6; i++)
  {
    for (int x = 0; x < 8; x++)
      for (int z = 0; z < 8; z++) {
        if ( (4 + i) <= 7)
          leds[ ToIndex(x, 4 + i, z) ] = leds[ ToIndex(x, 3 + i, z) ];
        leds[ ToIndex(x, i, z) ] = CRGB::Black;
      }
    rDelay(animRate);
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
    rDelay(animRate);
    if (i > 0) DrawCube(a1, b1, CRGB::Black);
  }

  // Front-Left
  for (int i = 0; i < 5; i++) {
    Point a1 = {i, 0, 0};
    Point b1 = {i + 3, 0 + 3, 0 + 3};
    DrawCube(a1, b1, CRGB::Red);
    rDelay(animRate);
    if (i < 4) DrawCube(a1, b1, CRGB::Black);
  }

  // Blue drop from top
  for (int i = 7; i >= 0; i--) {
    Point a1 = {0, i, 4};
    Point b1 = {3, i + 3, 7};
    DrawCube(a1, b1, CRGB::Blue);
    rDelay(animRate);
    if (i > 0) DrawCube(a1, b1, CRGB::Black);
  }

  // Back-Left
  for (int i = 0; i < 5; i++) {
    Point a2 = {0, 0, 4 - i};
    Point b2 = {3, 3, 4 - i + 3};
    DrawCube(a2, b2, CRGB::Blue);
    rDelay(animRate);
    if (i < 4) DrawCube(a2, b2, CRGB::Black);
  }

  // Blue drop from top
  for (int i = 7; i >= 0; i--) {
    Point a1 = {0, i, 4};
    Point b1 = {3, i + 3, 7};
    DrawCube(a1, b1, CRGB::Blue);
    rDelay(animRate);
    if (i > 0) DrawCube(a1, b1, CRGB::Black);
  }

  // Back-Left
  for (int i = 0; i < 5; i++) {
    Point a1 = {i, 0, 4};
    Point b1 = {i + 3, 0 + 3, 7};
    DrawCube(a1, b1, CRGB::Blue);
    rDelay(animRate);
    if (i < 4) DrawCube(a1, b1, CRGB::Black);
  }


  // Red drop from top
  for (int i = 7; i >= 0; i--) {
    Point a1 = {0, i, 4};
    Point b1 = {3, i + 3, 7};
    DrawCube(a1, b1, CRGB::Red);
    rDelay(animRate);
    if (i > 0) DrawCube(a1, b1, CRGB::Black);
  }
}

void SayHello()
{
  byte rate = 60;
  DrawText(F("HELLO MAKESHIFT   "));
  rDelay(1000);
}

void RetroFromFuture()
{
  byte rate = 60;
//  DrawText(F("HI MAKESHIFT   "));
//  rDelay(1000);

  GrowFromCenter(0, fgColor, rate);
  rDelay(500);

  FlipBottomToFront(fgColor, rate);
  FlipFrontToLeft(fgColor, rate);
  FlipLeftToBack(fgColor, rate);
  FlipBackToBottom(fgColor, rate);

  ShrinkToCenter(0, fgColor, rate);
  rDelay(1000);

  SlidingCubes();
  rDelay(500);
  LiftUp(rate * 2);

  Rain();
  rDelay(1000);
}
