void OneAtATime()
{
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[ i ] = CRGB::Blue;
    FastLED.delay(100);
    leds[ i ] = CRGB::Black;
  }
}

