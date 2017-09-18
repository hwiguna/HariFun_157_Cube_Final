// 8 x 8 x 8 Neopixel Cube
//
// By Hari Wiguna, 2017
//
// Coordinate system:
// Front bottom left of the cube is 0,0,0
// Left to right is positive X
// Bottom to top is positive Y
// Front to back is positive Z

// WIRING:
// Connect first pixel via a 470 ohm resistor to DATA_PIN D3
// Neopixels are wired such that first pixel is at 0,0,0
// Then it goes up to 0,7,0
// Right to next X 1,7,0 and down to 1,0,0
// Right again to 2,0,0 and up to 2,7,0, etc until rightmost 7,0,0
// Then we start over at next Z 0,0,1
// up as before 0,7,1 to 1,7,1 to 1,0,1, etc all the way to the back

// Neopixels are driven by FastLED library by Daniel Garcia
#include "FastLED.h"

// State of the cube is represented by the leds[] array.
#define NUM_LEDS 512
CRGB leds[NUM_LEDS];
#define DATA_PIN 3

#include "Pixels.h"
#include "Point.h"
#include "Lines.h"
#include "Shapes.h"
#include "Tests.h"
#include "RetroFromFuture.h"

void setup() {
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  SetAll(CRGB::Black);
}

void loop() {
  //OneAtATime();
  //DrawXYRects();
  //EtchSketch();
  SlidingCubes();
  //RetroFromFuture();
}
