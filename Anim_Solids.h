// Animated Solid/Filled Shapes
// FlapBottomToFront(CRGB c, int rate)
// DrawPlane(byte which, int offset, CRGB c)
// BouncePlane(byte which, byte nTimes, CRGB c, byte rate)
// FillCube(byte which, byte nTimes, CRGB c, byte rate)
// Explode(CRGB c, byte expandRate)
// CRGB Wheel(byte WheelPos)
// Rainbow(uint8_t wait)
// RainbowXZ(uint8_t wait)

void FlapBottomToFront(CRGB c, int rate) {
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
    rDelay(rate);
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
    rDelay(rate);
    if (i != 0) DrawPairs(points, bgColor, n);
  }
}

void DrawPlane(byte which, int offset, CRGB c) {
  switch (which) {
    case 1: DrawXYPlane(offset, c); break;
    case 2: DrawYZPlane(offset, c); break;
    case 3: DrawXZPlane(offset, c); break;
  }
}

void BouncePlane(byte which, byte nTimes, CRGB c, byte rate) {
  for (int rep = 0; rep < nTimes; rep++)
  {
    for (int x = 0; x < 8; x++) {
      DrawPlane(which, x, c);
      //rDelay(rate);
      rDelay(rate);
      DrawPlane(which, x, bgColor);
    }

    for (int x = 7; x > 0; x--) {
      DrawPlane(which, x, c);
      //rDelay(rate);
      rDelay(rate);
      DrawPlane(which, x, bgColor);
    }
  }
}

void FillCube(byte which, byte nTimes, CRGB c, byte rate) {
  for (int rep = 0; rep < nTimes; rep++)
  {
    for (int i = 0; i < 8; i++) {
      DrawPlane(which, i, c);
      rDelay(rate);
    }

    rDelay(1000);

    for (int i = 0; i < 8; i++) {
      DrawPlane(which, i, bgColor);
      rDelay(rate);
    }
  }
}

void Explode(CRGB c, byte expandRate) {
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

CRGB Wheel(byte WheelPos) {
  // Input a value 0 to 255 to get a color value.
  // The colours are a transition r - g - b - back to r.
  // Thanks to mattnupen: https://codebender.cc/sketch:80438#Neopixel%20Rainbow.ino

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
  uint16_t x, y, z;
  for (y = 0; y < 8; y++) {
    for (x = 0; x < 8; x++) {
      for (z = 0; z < 8; z++) {
        SetPixel(x, y, z, Wheel( (x + z * 8 + y * 64) & 255) );
      }
    }
  }
}

void ArrowOnXYPlane(int offset, CRGB c) {
  for (byte y=0; y<8; y++) {
    for (int x=0; x<8; x++) {
      //SetPixel(offset+x, y, 0, bitRead(arrowRight[7-y],7-x) ? c : CRGB::Black);
      DrawLine(offset+x, y, 0, offset+x, y, 7, bitRead(arrowRight[7-y],7-x) ? c : CRGB::Black);
    }
  }
}

void ArrowOnXYPlane_LeftToRight(CRGB c) {
  for (int x=-7; x<8+8; x++) {
      ArrowOnXYPlane(x, c);
      rDelay(50);
      ArrowOnXYPlane(x, CRGB::Black);
    }
}

void ArrowOnZYPlane(int offset, CRGB c) {
  for (byte y=0; y<8; y++) {
    for (int z=0; z<8; z++) {
      SetPixel(0, y, offset+7-z, bitRead(arrowRight[7-y],7-z) ? c : CRGB::Black);
      //DrawLine(offset+z, y, 0, offset+z, y, 7, bitRead(arrowRight[7-y],7-z) ? c : CRGB::Black);
    }
  }
}

void ArrowOnZYPlane_BackToFront(CRGB c) {
  for (int z=8+8; z>-8; z--) {
      ArrowOnZYPlane(z, c);
      rDelay(50);
      ArrowOnZYPlane(z, CRGB::Black);
    }
}

void ArrowUpOnZYPlane(int offset, CRGB c) {
  for (byte y=0; y<8; y++) {
    for (int z=0; z<8; z++) {
      SetPixel(0, offset+y, 7-z, bitRead(arrowUp[7-y],7-z) ? c : CRGB::Black);
      //DrawLine(offset+z, y, 0, offset+z, y, 7, bitRead(arrowRight[7-y],7-z) ? c : CRGB::Black);
    }
  }
}

void ArrowOnZYPlane_Upward(CRGB c) {
  for (int y=-8; y<8+8; y++) {
      ArrowUpOnZYPlane(y, c);
      rDelay(50);
      ArrowUpOnZYPlane(y, CRGB::Black);
    }
}

