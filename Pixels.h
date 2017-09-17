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
  FastLED.show();
}

