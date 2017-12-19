// Animated Solid/Filled Shapes

void FlapBottomToFront(CRGB c, int rate)
{
  Point origin = {0, 0, 0};
  Point width = {7, 7, 7};
  Point offset = {width.x, width.y, width.z};
  byte n = 2 * 8;

  // Bottom to top
  for (int i = 0; i < 8; i++)
  {
    Point points[n];
    for (int x = 0; x < 8; x++)
    {
      points[x * 2] =  {origin.x + x, origin.y, origin.z};
      points[x * 2 + 1] = {origin.x + x, origin.y + i, origin.z + offset.z};
    }

    DrawPairs(points, c, n);
    FastLED.delay(rate);
    DrawPairs(points, bgColor, n);
  }

  // Back to front (on top)
  for (int i = 6; i >= 0; i--)
  {
    Point points[n];
    for (int x = 0; x < 8; x++)
    {
      points[x * 2] =  {origin.x + x, origin.y, origin.z};
      points[x * 2 + 1] = {origin.x + x, origin.y + offset.y, origin.z + i};
    }

    DrawPairs(points, c, n);
    FastLED.delay(rate);
    if (i != 0) DrawPairs(points, bgColor, n);
  }
}

//void BounceXYPlane(byte nTimes, CRGB c, byte rate)
//{
//  for (int rep = 0; rep < nTimes; rep++)
//  {
//    for (int z = 0; z < 8; z++) {
//      DrawXYPlane(z, c);
//      FastLED.delay(rate);
//      DrawXYPlane(z, bgColor);
//    }
//
//    for (int z = 7; z > 0; z--) {
//      DrawXYPlane(z, c);
//      FastLED.delay(rate);
//      DrawXYPlane(z, bgColor);
//    }
//  }
//}

void DrawPlane(byte which, int offset, CRGB c)
{
  switch (which) {
    case 1: DrawXYPlane(offset, c); break;
    case 2: DrawYZPlane(offset, c); break;
    case 3: DrawXZPlane(offset, c); break;
  }
}

void BouncePlane(byte which, byte nTimes, CRGB c, byte rate)
{
  for (int rep = 0; rep < nTimes; rep++)
  {
    for (int x = 0; x < 8; x++) {
      DrawPlane(which, x, c);
      //FastLED.delay(rate);
      rDelay(rate);
      DrawPlane(which, x, bgColor);
    }

    for (int x = 7; x > 0; x--) {
      DrawPlane(which, x, c);
      //FastLED.delay(rate);
      rDelay(rate);
      DrawPlane(which, x, bgColor);
    }
  }
}

void FillCube(byte which, byte nTimes, CRGB c, byte rate)
{
  for (int rep = 0; rep < nTimes; rep++)
  {
    for (int i = 0; i < 8; i++) {
      DrawPlane(which, i, c);
      FastLED.delay(rate);
    }

    FastLED.delay(1000);

    for (int i = 0; i < 8; i++) {
      DrawPlane(which, i, bgColor);
      FastLED.delay(rate);
    }
  }
}

void Explode(CRGB c, byte expandRate)
{
  for (byte i = 0; i < 4; i++) {
    Point a = {3 - i, 3 - i, 3 - i};
    Point b = {4 + i, 4 + i, 4 + i};
    DrawCube(a, b, c);
    //    for (byte j=0; j<4; j++) {
    //      DrawXYPlane(3-j, c);
    //      DrawXYPlane(4+j, c);
    //    }
    rDelay(expandRate);
  }
}



// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
// Thanks to mattnupen: https://codebender.cc/sketch:80438#Neopixel%20Rainbow.ino
CRGB Wheel(byte WheelPos) {
  if (WheelPos < 85) {
    return  CRGB(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
  else if (WheelPos < 170) {
    WheelPos -= 85;
    return CRGB(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  else {
    WheelPos -= 170;
    return CRGB(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}




void Rainbow(uint8_t wait) {
  uint16_t i, j;

  for (j = 0; j < 256; j++) {
    for (i = 0; i < 512; i++) {
      leds[ i ] =  Wheel((i * 1 + j) & 255);
    }
    rDelay(wait);
  }
}

void RainbowXZ(uint8_t wait) {
  uint16_t i, j, x, y, z;

  for (j = 0; j < 256; j++) {
    for (y = 0; y < 8; y++) {
      for (x = 0; x < 8; x++) {
        for (z = 0; z < 8; z++) {
          SetPixel(x, y, z, Wheel( (x+z*8+y*64) & 255) );
        }
      }
    }
    rDelay(wait);
  }
}

