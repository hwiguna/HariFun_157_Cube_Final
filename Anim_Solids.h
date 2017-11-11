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
    for (int x= 0; x < 8; x++) {
      DrawPlane(which, x, c);
      FastLED.delay(rate);
      DrawPlane(which, x, bgColor);
    }

    for (int x = 7; x > 0; x--) {
      DrawPlane(which, x, c);
      FastLED.delay(rate);
      DrawPlane(which, x, bgColor);
    }
  }
}

void FillCube(byte which, byte nTimes, CRGB c, byte rate)
{
  for (int rep = 0; rep < nTimes; rep++)
  {
    for (int i= 0; i < 8; i++) {
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

