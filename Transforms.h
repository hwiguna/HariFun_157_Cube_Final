// Transform the content of the led array in place!

void FlipVertically()
{
  CRGB t;
  for (int i = 0; i < 4; i++)
    for (int x = 0; x < 8; x++)
      for (int z = 0; z < 8; z++)
      {
        t = leds[x, y, i];
        leds[x, y, i] = leds[x, y, 7 - i];
        leds[x, y, 7 - i] = t;
      }
}

