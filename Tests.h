void OneAtATime()
{
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[ i ] = CRGB::Blue;
    FastLED.delay(100);
    leds[ i ] = CRGB::Black;
  }
}

void DrawDiagonal(CRGB c)
{
  DrawLine( 0,0,0, 7,7,7, c);
}

