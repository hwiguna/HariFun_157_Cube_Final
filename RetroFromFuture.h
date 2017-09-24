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


void PrintRGB(CRGB c)
{
  Serial.print("(");
  Serial.print(c.red);
  Serial.print(",");
  Serial.print(c.green);
  Serial.print(",");
  Serial.print(c.blue);
  Serial.print(" ) ");
}

void Rain1()
{
  //-- Set random raindrop speed for all pixels on top XZ plane --
  for (int x = 0; x < 8; x++)
    for (int z = 0; z < 8; z++) {
      int randomRate = random(1, 4);
      CRGB t = leds[ ToIndex(x, 7, z) ];
      leds[ ToIndex(x, 7, z) ] = CRGB(t.red, randomRate, t.blue);
    }

  //  Serial.println();
  //  Serial.println("BEGIN");

  for (int rain = 0; rain < 8; rain++) {
    for (int a = 1; a < 4; a++) {
      //Serial.print("a="); Serial.print(a);
      for (int y = 0; y < 8; y++) {
        //Serial.print(" z="); Serial.println(z);
        for (int x = 0; x < 8; x++) {
          for (int z = 0; z < 8; z++) {
            int srcIndex =  ToIndex(x, y, z);
            CRGB t = leds[ srcIndex ];
            if (t.green <= a) {
              //              Serial.print("a match at (");
              //              Serial.print(x);
              //              Serial.print(",");
              //              Serial.print(y);
              //              Serial.print(",");
              //              Serial.print(z);
              //              Serial.print(" )  ");

              int dest = y - 1;
              if (dest >= 0) {

                int destIndex = ToIndex(x, dest, z);
                //                Serial.print("Copy ");
                //                Serial.print(z);
                //                Serial.print(" to ");
                //                Serial.print(dest);

                //                Serial.print(" red="); PrintRGB(CRGB::Red);
                //                Serial.print(" src="); PrintRGB(leds[ srcIndex ]);
                //                Serial.print(" dst="); PrintRGB(leds[ destIndex ]);

                leds[ destIndex ] = leds[ srcIndex ]; // Copy to the pixel below it
                //Serial.print(" DST="); PrintRGB(leds[ destIndex ]);
              }
              //Serial.println();
              leds[srcIndex] = CRGB::Black; // Erase the pixel at previous location
            } // if needs to move this pixel
          } // for z
        } // for x
      } // for y
      FastLED.delay(100);
    } // for a
  } // for rain
}

void Rain2()
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
    
    if (i<64) {
      leds[ ToIndex( seq[i] / 8, 7, seq[i] % 8) ].green = 1;
      i++;
    }
      
      for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
          for (int z = 0; z < 8; z++) {
            int srcIndex =  ToIndex(x, y, z);
            CRGB t = leds[ srcIndex ];
            if (t.green == 1) {

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
    FastLED.delay(100);
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
    FastLED.delay(animRate);
  }
}

void SlidingCubes()
{
  int animRate = 60;

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
  Rain2();

  delay(1000);

  FastLED.clear();
}


//void RetroFromFuture()
//{
//  SuperNova(500,500, CRGB::Red);
//}

