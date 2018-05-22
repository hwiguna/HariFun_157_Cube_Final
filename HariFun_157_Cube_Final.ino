// 8 x 8 x 8 Neopixel Cube
//
// By Hari Wiguna, 2017
//
// WIRING:
// Connect DATA IN pin of first pixel via a 470 ohm resistor to Arduino DATA_PIN D3
// I put a 470uF Electrolytic capacitor at the base of each of the four modules.
//
// Coordinate system:
// Front bottom left of the cube is 0,0,0
// Left to right is positive X
// Bottom to top is positive Y
// Front to back is positive Z
//
// Neopixels are wired such that first pixel is at 0,0,0 and last one is at 7,0,7.
// This is how the first 64 pixels (front vertical face at Z=0) are wired:
// 7 > 8    23 > 24   39 > 40   55 > 56
// 6   9    22   25   38   41   54   57
// 5   10   21   26   37   42   53   58
// 4   11   20   27   36   43   52   59
// 3   12   19   28   35   44   51   60
// 2   13   18   29   34   45   50   61
// 1   14   17   30   33   46   49   62
// 0   15 > 16   31 > 32   47 > 48   63
// All subsequent Z planes are in the same order as the first Z, starting at bottom left, ending up at bottom right.

// Neopixels are driven by FastLED library by Daniel Garcia
#include "FastLED.h"
#define DATA_PIN 3

// State of the cube is represented by the leds[] array.
#define NUM_LEDS 512
CRGB leds[NUM_LEDS];

CRGB bgColor = CRGB::Black; // {0,0,64};
CRGB fgColor = CRGB::White;

// https://github.com/feilipu/Arduino_FreeRTOS_Library
//#include <Arduino_FreeRTOS.h>

int animRate = 100; //50;
int refreshRate = 5;

unsigned long timeZero;
unsigned long timeOffset = 500;
int effectIndex;

#include "Debug.h"
#include "Inputs.h"
#include "Pixels.h"
#include "Point.h"
#include "Lines.h"
#include "Shapes.h"
#include "Text.h"
#include "Bitmaps.h"
#include "Anim_Solids.h"
#include "Anim_Wires.h"
#include "SpectrumAnalyzer.h"
#include "RetroFromFuture.h"
#include "Effects.h"
#include "Believer.h"
#include "Tests.h"

#ifdef INC_ARDUINO_FREERTOS_H
#include "RTOS.h"
#endif

#include "Serial1.h"
//#include "Remote.h"

void setup() {
  Serial.begin(9600);
  Serial1.begin(115200);
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  SetAll(bgColor);
  FastLED.show();
  SetupInputs();
  //setupSpectrumAnalyzer();

#ifdef INC_ARDUINO_FREERTOS_H
  SetupRTOS();
#endif
  // SetupRemote();
  
}

void loop() {
  //loopSpectrumAnalyzer();
  
#ifdef INC_ARDUINO_FREERTOS_H
  FastLED.delay(refreshRate); // This should be the ONLY FastLED.delay() All others should be just RTOS delays.
#else
  ExecuteSerialCommand();
  ExecuteButtons();
#endif

//ArrowOnXYPlane_LeftToRight(CRGB::Red);
//ArrowOnZYPlane_BackToFront(CRGB::Blue);
//delay(1500);
}

void ExecuteButtons()
{
  ReadButtons();
  if (Pressed[ 0 ]) SetAll(bgColor);
  if (Pressed[ 1 ]) ArrowOnZYPlane_BackToFront(CRGB::Red); // Size8Wide(CRGB::Red);
  if (Pressed[ 2 ]) ArrowOnZYPlane_Upward(CRGB::Green); // Size8Tall(CRGB::Green);
  if (Pressed[ 3 ]) ArrowOnXYPlane_LeftToRight(CRGB::Blue); //Size8Deep(CRGB::Blue);

  if (Pressed[ 4 ]) for (byte n=0;n<3; n++) SpinOnXAxis(CRGB::Blue);
  if (Pressed[ 5 ]) for (byte n=1;n<=8; n++) SpinOnXAxis(CRGB::Blue, n);
  if (Pressed[ 6 ]) StaticHatXYRainbow();

  rDelay(50); // Force FastLED to refresh
  for (byte i=0; i<10; i++) Pressed[i] = false;
}

