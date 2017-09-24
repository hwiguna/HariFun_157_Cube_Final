// Animated Solid/Filled Shapes

void FlapBottomToFront(CRGB c, int rate)
{
  Point origin = {0, 0, 0};
  Point width = {7, 7, 7};
  Point offset = {width.x, width.y, width.z};
  byte n = 2*8;

  // Bottom to top
  for (int i = 0; i < 8; i++)
  {
    Point points[n];
    for (int x = 0; x < 8; x++)
    {
      points[x*2] =  {origin.x + x, origin.y, origin.z};
      points[x*2+1] = {origin.x + x, origin.y + i, origin.z + offset.z};
    }
  
    DrawPairs(points, c, n);
    FastLED.delay(rate);
    DrawPairs(points, bgColor, n);
  }

  // Back to front (on top)
  for (int i=6; i>=0; i--)
  {
    Point points[n];
    for (int x = 0; x < 8; x++)
    {
      points[x*2] =  {origin.x + x, origin.y, origin.z};
      points[x*2+1] = {origin.x + x, origin.y + offset.y, origin.z + i};
    }

    DrawPairs(points, c, n);
    FastLED.delay(rate);
    if (i!=0) DrawPairs(points, bgColor, n);
  }
}

