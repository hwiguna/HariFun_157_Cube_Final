//=== Pixel Routines ===

int ToIndex(int x, int y, int z)
{
  return (x % 2) ? (x * 8) + (7 - y) + z * 64 : (x * 8) + y + z * 64;
}

void SetAll(CRGB c)
{
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[ i ] = c;
  }
}

void SetPixel(int x, int y, int z, CRGB c)
{
  if (x>=0 && x<8 &&
      y>=0 && y<8 &&
      z>=0 && z<8)
  leds[ ToIndex(x,y,z) ] = c;
}
