// Wireframe Animations
// FlipSlant(Point origin, int from, int to, CRGB c, int rate, Point rotations)
// FlipBottomToFront(CRGB c, int rate)
// FlipFrontToRight(CRGB c, int rate)
// FlipFrontToLeft(CRGB c, int rate)
// FlipLeftToBack(CRGB c, int rate)
// FlipBackToRight(CRGB c, int rate)
// FlipBackToBottom(CRGB c, int rate)
// GrowFromCenter(byte y, CRGB c, byte rate)
// ShrinkToCenter(byte y, CRGB c, byte rate)
// WaveAnim()
// StaticWaveYZ()
// StaticWaveXY()
// SineWave()
// FlashLineXAlongZ(int y, CRGB c)
// StaticHatXY() 
// StaticHatXYRainbow()

// SpinOnXAxis(CRGB c)
// SpinOnXAxis(CRGB c, int len)
// SpinOnZAxis(CRGB c)

void FlipSlant(Point origin, int from, int to, CRGB c, int rate, Point rotations)
{
  Point width = { 7, 7, 7 };
  int dir = (to > from ? 1 : -1);
  Point offset = { 0, 0, width.z };

  // Draw static horizontal line (bottom front)
  DrawLine(origin.x, origin.y, origin.z, origin.x + width.x, origin.y, origin.z, c);

  for (int i = from; i != to + dir; i += dir)
  {
    for (byte ci = 0; ci < 2; ci++) {
      CRGB kolor = (ci == 0) ? c : bgColor;

      // Draw opposite moving line
      DrawLine(origin.x, origin.y + i, origin.z + offset.z, origin.x + width.x, origin.y + i, origin.z + offset.z, kolor);

      // Draw connecting lines
      DrawLine(origin.x, origin.y, origin.z, origin.x, origin.y + i, origin.z + offset.z, kolor);
      DrawLine(origin.x + width.x, origin.y, origin.z, origin.x + width.x, origin.y + i, origin.z + offset.z, kolor);
      if (ci == 0) rDelay(rate);
    }
  }

  DrawLine(origin.x, origin.y, origin.z, origin.x + width.x, origin.y, origin.z, bgColor);
  FastLED.show();
}

void FlipBottomToFront(CRGB c, int rate)
{
  Point origin = { 0, 0, 0 };
  Point width = { 7, 7, 7 };
  Point offset = { width.x, width.y, width.z };

  // Draw static line
  DrawLine(origin.x, origin.y, origin.z, origin.x + width.x, origin.y, origin.z, c);

  // Bottom to top
  for (int i = 0; i < 8; i++)
  {
    Point points[4];
    points[0] = origin;
    points[1] = { origin.x,           origin.y + i, origin.z + offset.z };
    points[2] = { origin.x + width.x, origin.y + i, origin.z + offset.z };
    points[3] = { origin.x + width.x, origin.y,     origin.z };

    DrawPoly(points, c);
    rDelay(rate);
    DrawPoly(points, bgColor);
  }

  // Back to front (on top)
  for (int i = 6; i >= 0; i--)
  {
    Point points[4];
    points[0] = origin;
    points[1] = { origin.x,           origin.y + offset.y, origin.z + i };
    points[2] = { origin.x + width.x, origin.y + offset.y, origin.z + i };
    points[3] = { origin.x + width.x, origin.y,     origin.z };

    DrawPoly(points, c);
    rDelay(rate);
    if (i != 0) DrawPoly(points, bgColor);
  }
}

void FlipFrontToRight(CRGB c, int rate)
{
  Point origin = { 7, 0, 0 };
  Point width = { 7, 7, 7 };
  Point offset = { width.x, width.y, width.z };

  // Draw static vertical line (front right)
  DrawLine(origin.x, origin.y, origin.z, origin.x, origin.y + width.y, origin.z, c);

  // Front to back
  for (int i = 0; i < 8; i++)
  {
    Point points[4];
    points[0] = origin;
    points[1] = { origin.x - width.x, origin.y,          origin.z + i };
    points[2] = { origin.x - width.x, origin.y + offset.y, origin.z + i };
    points[3] = { origin.x,           origin.y + offset.y, origin.z };

    DrawPoly(points, c);
    rDelay(rate);
    DrawPoly(points, bgColor);
  }

  // left to right (on back)
  for (int i = 6; i >= 0; i--)
  {
    Point points[4];
    points[0] = origin;
    points[1] = { origin.x - i, origin.y,          origin.z + offset.z };
    points[2] = { origin.x - i, origin.y + offset.y, origin.z + offset.z };
    points[3] = { origin.x,     origin.y + offset.y, origin.z };

    DrawPoly(points, c);
    rDelay(rate);
    if (i != 0) DrawPoly(points, bgColor);
  }
}

void FlipFrontToLeft(CRGB c, int rate)
{
  Point origin = { 0, 0, 0 };
  Point width = { 7, 7, 7 };
  Point offset = { width.x, width.y, width.z };

  // Draw static vertical line (front left)
  DrawLine(origin.x, origin.y, origin.z, origin.x, origin.y + width.y, origin.z, c);

  // Front to back (on right side)
  for (int i = 0; i < 8; i++)
  {
    Point points[4];
    points[0] = origin;
    points[1] = { origin.x + width.x, origin.y,          origin.z + i };
    points[2] = { origin.x + width.x, origin.y + offset.y, origin.z + i };
    points[3] = { origin.x,           origin.y + offset.y, origin.z };

    DrawPoly(points, c);
    rDelay(rate);
    DrawPoly(points, bgColor);
  }

  // right to left (on back)
  for (int i = 6; i >= 0; i--)
  {
    Point points[4];
    points[0] = origin;
    points[1] = { origin.x + i, origin.y,          origin.z + offset.z };
    points[2] = { origin.x + i, origin.y + offset.y, origin.z + offset.z };
    points[3] = { origin.x,     origin.y + offset.y, origin.z };

    DrawPoly(points, c);
    rDelay(rate);
    if (i != 0) DrawPoly(points, bgColor);
  }
}

void FlipLeftToBack(CRGB c, int rate)
{
  Point origin = { 0, 0, 7 };
  Point width = { 7, 7, 7 };
  Point offset = { width.x, width.y, width.z };

  // Draw static vertical line (back left)
  DrawLine(origin.x, origin.y, origin.z, origin.x, origin.y + width.y, origin.z, c);

  // Left to right (on front)
  for (int i = 0; i < 8; i++)
  {
    Point points[4];
    points[0] = origin;
    points[1] = { origin.x + i, origin.y,          origin.z - width.z };
    points[2] = { origin.x + i, origin.y + offset.y, origin.z - width.z };
    points[3] = { origin.x,           origin.y + offset.y, origin.z };

    DrawPoly(points, c);
    rDelay(rate);
    DrawPoly(points, bgColor);
  }

  // front to back (on right)
  for (int i = 1; i < 8; i++)
  {
    Point points[4];
    points[0] = origin;
    points[1] = { origin.x + width.x, origin.y,          origin.z - width.z + i };
    points[2] = { origin.x + width.x, origin.y + offset.y, origin.z - width.z + i };
    points[3] = { origin.x,           origin.y + offset.y, origin.z };

    DrawPoly(points, c);
    rDelay(rate);
    if (i < 7) DrawPoly(points, bgColor);
  }
}

void FlipBackToRight(CRGB c, int rate)
{
  Point origin = { 7, 0, 7 };
  Point width = { 7, 7, 7 };
  Point offset = { width.x, width.y, width.z };

  // Draw static vertical line (back right)
  DrawLine(origin.x, origin.y, origin.z, origin.x, origin.y + width.y, origin.z, c);

  // back to front (on left)
  for (int i = 0; i < 8; i++)
  {
    Point points[4];
    points[0] = origin;
    points[1] = { origin.x - width.x, origin.y,          origin.z - i };
    points[2] = { origin.x - width.x, origin.y + offset.y, origin.z - i };
    points[3] = { origin.x,           origin.y + offset.y, origin.z };

    DrawPoly(points, c);
    rDelay(rate);
    DrawPoly(points, bgColor);
  }

  // left to right (on front)
  for (int i = 1; i < 8; i++)
  {
    Point points[4];
    points[0] = origin;
    points[1] = { origin.x - width.x + i, origin.y,          origin.z - width.z };
    points[2] = { origin.x - width.x + i, origin.y + offset.y, origin.z - width.z };
    points[3] = { origin.x,           origin.y + offset.y, origin.z };

    DrawPoly(points, c);
    rDelay(rate);
    if (i < 7) DrawPoly(points, bgColor);
  }
}

void FlipBackToBottom(CRGB c, int rate)
{
  Point origin = { 0, 0, 7 };
  Point width = { 7, 7, 7 };
  Point offset = { width.x, width.y, width.z };

  // Draw static horizontal line (bottom back)
  DrawLine(origin.x, origin.y, origin.z, origin.x + width.x, origin.y, origin.z, c);

  // Back to front (on top)
  for (int i = 7; i >= 0; i--)
  {
    Point points[4];
    points[0] = origin;
    points[1] = { origin.x,           origin.y + offset.y, origin.z - width.z + i };
    points[2] = { origin.x + width.x, origin.y + offset.y, origin.z - width.z + i };
    points[3] = { origin.x + width.x, origin.y,     origin.z };

    DrawPoly(points, c);
    rDelay(rate);
    DrawPoly(points, bgColor);
  }

  // top to bottom (in front)
  for (int i = 6; i >= 0; i--)
  {
    Point points[4];
    points[0] = origin;
    points[1] = { origin.x,           origin.y + i, origin.z - width.z };
    points[2] = { origin.x + width.x, origin.y + i, origin.z - width.z };
    points[3] = { origin.x + width.x, origin.y,     origin.z };

    DrawPoly(points, c);
    rDelay(rate);
    if (i != 0) DrawPoly(points, bgColor);
  }
}

void GrowFromCenter(byte y, CRGB c, byte rate)
{
  for (byte i = 0; i < 4; i++)
  {
    Point points[5];
    points[0] = { 3 - i, y, 3 - i }; // x-, z-
    points[1] = { 3 - i, y, 4 + i }; // x-, z+
    points[2] = { 4 + i, y, 4 + i }; // x+, z+
    points[3] = { 4 + i, y, 3 - i }; // x+, z-
    points[4] = { 3 - i, y, 3 - i }; // back to point 0

    DrawPoly(points, c, 5);
    rDelay(rate);
    if (i < 3) DrawPoly(points, bgColor, 5);  // Don't erase the last frame
  }
}

void ShrinkToCenter(byte y, CRGB c, byte rate)
{
  for (int i = 3; i >= 0; i--)
  {
    Point points[5];
    points[0] = { 3 - i, y, 3 - i }; // x-, z-
    points[1] = { 3 - i, y, 4 + i }; // x-, z+
    points[2] = { 4 + i, y, 4 + i }; // x+, z+
    points[3] = { 4 + i, y, 3 - i }; // x+, z-
    points[4] = { 3 - i, y, 3 - i }; // back to point 0

    DrawPoly(points, c, 5);
    rDelay(rate);
    DrawPoly(points, bgColor, 5);
  }
}

void WaveAnim() // This works pretty good at an angle
{
  float maxAmp = 2.0;

  for (float a0 = 0; a0 < 2 * PI; a0 += (PI / 8)) {
    for (int x = 0; x < 8; x++) {
      float a = a0 + (PI * x / 8);
      for (int z = 0; z < 8; z++) {
        float b = a0 + (PI * z / 8);
        int y = maxAmp + (sin(a) * maxAmp + sin(b) * maxAmp);
        SetPixel(x, y, z, CRGB::Blue);
      }
    }
    rDelay(animRate);
    SetAll(bgColor);
  }
}

void StaticWaveYZ()
{
  float maxAmp = 2.0;

  int x = 0;
  for (float a0 = 0; a0 < PI; a0 += (PI / 8))
  {
    for (int z = 0; z < 8; z++)
    {
      float a = a0 + (PI * z / 6);
      int y = maxAmp + (sin(a) * maxAmp);
      SetPixel(x, y, z, CRGB::Blue);
      SetPixel(z, y, x, CRGB::Blue);
      //DrawLine(x, y, z, x0+x, y, z + 7, CRGB::Blue);
    }
    rDelay(animRate);
    SetAll(bgColor);
  }
}

void StaticWaveXY()
{
  float maxAmp = 3.5;

  int z = 0;
  for (float a0 = 0; a0 < PI; a0 += (PI / 8))
  {
    for (int x = 0; x < 8; x++)
    {
      float a = a0 + (PI * x / 6);
      int y = maxAmp + (sin(a) * maxAmp);
      SetPixel(x, y, z, CRGB::Blue);
      //DrawLine(x, y, z, x0+x, y, z + 7, CRGB::Blue);
    }
    rDelay(animRate);
    SetAll(bgColor);
  }
}

void SineWave()
{
  int z = 0;
  float maxAmp = 3.5;
  for (int rep = 0; rep < 3; rep++) {
    // Amplitude -1 to 1
    for (float amp = -maxAmp; amp < maxAmp; amp += 1)
    {
      for (int x = 0; x < 8; x++)
      {
        float a = .25 * PI + PI * x / 8;
        int y = 3.5 + (sin(a) * amp);
        //SetPixel(z, y, x, CRGB::Blue);
        DrawLine(x, y, z, x, y, z + 7, CRGB::Blue);
      }
      rDelay(animRate);
      SetAll(bgColor);
    }

    // Amplitude 1 to -1
    for (float amp = +maxAmp; amp > -maxAmp; amp -= 1)
    {
      for (int x = 0; x < 8; x++)
      {
        float a = .25 * PI + PI * x / 8;
        int y = 3.5 + (sin(a) * amp);
        //SetPixel(z, y, x, CRGB::Blue);
        DrawLine(x, y, z, x, y, z + 7, CRGB::Blue);
      }
      rDelay(animRate);
      SetAll(bgColor);
    }
  }
}

void FlashLineXAlongZ(int y, CRGB c)
{
  for (int z = 1; z < 8; z++)
  {
    DrawXLine(y, z, c);
    rDelay(50);
  }
}

/* Failed attempts

  void StaticHatXYManual()
  {
    // https://www.gnu.org/software/octave/doc/v4.2.1/Three_002dDimensional-Plots.html
    float half = 4;
    float xMin = -half;
    float xMax = half;
    float yMin = -half;
    float yMax = half;

    float lastA = 0;
    unsigned long stopTime = millis() + 30000;
    while (millis() < stopTime)
    {
        float a = map(analogRead(A0), 0, 1023, 100, -100);
        if (a != lastA) {
            lastA = a;
            SetAll(bgColor);
            for (int x = 0; x < 8; x++)
            {
                float xf = xMin + (xMax - xMin) * x / 7;
                for (int y = 0; y < 8; y++)
                {
                    float yf = yMin + (yMax - yMin) * y / 7;
                    float r = sqrt(square(xf) + square(yf));
                    float z = a * (sin(r) / r) / 100;
                    float rez = 100;

                    int zi = map(z * rez, -1 * rez, 1 * rez, 0, 7);
                    SetPixel(x, zi, y, CRGB::Blue); // Flip y and z axes because horizontal plane is xy in math, but xz on my cube.
                }
            }
        }
        rDelay(animRate);
    }
  }

  void StaticHatXYAuto() // Auto
  {
    // https://www.gnu.org/software/octave/doc/v4.2.1/Three_002dDimensional-Plots.html
    float half = 4;
    float xMin = -half;
    float xMax = half;
    float yMin = -half;
    float yMax = half;

    unsigned long stopTime = millis() + 30000;
    int dir = 20;
    int a = 0;
    while (millis() < stopTime)
    {
        a += dir;
        if (a > 100) { a = 100; dir = -dir; }
        if (a <= -100) { a = -100; dir = -dir; }

        SetAll(bgColor);
        for (int x = 0; x < 8; x++)
        {
            float xf = xMin + (xMax - xMin) * x / 7;
            for (int y = 0; y < 8; y++)
            {
                float yf = yMin + (yMax - yMin) * y / 7;
                float r = sqrt(square(xf) + square(yf));
                float z = a * (sin(r) / r) / 100;
                float rez = 100;

                int zi = map(z * rez, -1 * rez, 1 * rez, 0, 7);
                SetPixel(x, zi, y, CRGB::Blue); // Flip y and z axes because horizontal plane is xy in math, but xz on my cube.
            }
        }
        rDelay(animRate);
    }
  }
*/

void StaticHatXY() // Auto
{
  int iterations = 2000;
  for (int i = 0; i < iterations; i++)
  {
    SetAll(bgColor);
    for (int x = 0; x < 8; x++)
    {
      for (int y = 0; y < 8; y++)
      {
        // Math from: https://www.instructables.com/id/Led-Cube-8x8x8/
        float distance = distance2d(3.5, 3.5, x, y) / 9.899495 * 8;
        float ripple_interval = 1.3;
        int height = 4 + sin(distance / ripple_interval + (float)i / 3) * 4;

        SetPixel(x, height, y, CRGB::Blue); // Flip y and z axes because horizontal plane is xy in math, but xz on my cube.
      }
    }
    rDelay(50);
  }
}

void StaticHatXYRainbow(int iterations) // Auto
{
  for (int i = 0; i < iterations; i++)
  {
    SetAll(bgColor);
    for (int x = 0; x < 8; x++)
    {
      for (int y = 0; y < 8; y++)
      {
        // Math from: https://www.instructables.com/id/Led-Cube-8x8x8/
        float distance = distance2d(3.5, 3.5, x, y) / 9.899495 * 8;
        float ripple_interval = 1.3;
        int height = 4 + sin(distance / ripple_interval + (float)i / 3) * 4;

        //CRGB color = Wheel((x + height * 8 + y * 16) & 255);
        //CRGB color = Wheel(255-((x + height * 16 + y ) & 255); // good
        CRGB color = Wheel((127+ x + height * 16 + y ) & 255); // better

        SetPixel(x, height, y, color); // Flip y and z axes because horizontal plane is xy in math, but xz on my cube.
      }
    }
    rDelay(50);
  }
}

//=============================================================

void Size8Wide(CRGB c)
{
  for (int i = 0; i < 8; i++) {
    SetAll(bgColor);
    DrawLine(0, 0, 0, 0, 7, 0, c); // Left
    DrawLine(0, 7, 0, i, 7, 0, c); // Middle top
    DrawLine(i, 7, 0, i, 0, 0, c); // Right
    DrawLine(i, 0, 0, 0, 0, 0, c); // Middle bottom
    rDelay(100);
  }
}
void Size8Tall(CRGB c)
{
  for (int i = 0; i < 8; i++) {
    SetAll(bgColor);
    DrawLine(0, 0, 0, 0, 0, 7, c); // Front
    DrawLine(0, 0, 7, 0, i, 7, c); // Middle top
    DrawLine(0, i, 7, 0, i, 0, c); // Back
    DrawLine(0, i, 0, 0, 0, 0, c); // Middle bottom
    rDelay(100);
  }
}
void Size8Deep(CRGB c)
{
  for (int i = 0; i < 8; i++) {
    SetAll(bgColor);
    DrawLine(0, 0, 0, 7, 0, 0, c); // Front
    DrawLine(7, 0, 0, 7, 0, i, c); // Middle right
    DrawLine(7, 0, i, 0, 0, i, c); // Back
    DrawLine(0, 0, i, 0, 0, 0, c); // Middle left
    rDelay(100);
  }
}
void SizeRaiseCube(CRGB c)
{
  for (int i = 0; i < 8; i++) {
    SetAll(bgColor);
    // Cube Top
    DrawLine(0, 0, 0, 7, 0, 0, c); // Front
    DrawLine(7, 0, 0, 7, 0, 7, c); // Middle top
    DrawLine(7, 0, 7, 0, i, 0, c); // Back
    DrawLine(0, i, 0, 0, 0, 0, c); // Middle bottom
    
    // Cube Bottom
    // Cube Sides
    
    rDelay(100);
  }
}


//DrawXLine(int y, int z, CRGB c)
//DrawYLine(int x, int z, CRGB c)
//DrawZLine(int x, int y, CRGB c)

void SpinOnXAxis(CRGB c) {
  //-- Front upwards, rear downward --
  for (int i = 0; i < 8; i++) {
    // front bottom
    int yUp = i;
    int yDown = 7-i;
    DrawLine(0, yUp, 0, 7, yUp, 0, c); // Front
    
    // diagonal front bottom to rear top
    DrawLine(0, yUp, 0, 0, yDown, 7, c); // diagonal left
    DrawLine(7, yUp, 0, 7, yDown, 7, c); // diagonal right

    // rear top
    DrawLine(0, yDown, 7, 7, yDown, 7, c); // Front
    rDelay(50);
    SetAll(bgColor);
  }

  //-- Top away, bottom towards --
  for (int i = 0+1; i < (8-1); i++) {
    // front bottom
    int zAway = i;
    int zTowards = 7-i;
    DrawLine(0, 7, zAway, 7, 7, zAway, c); // Top front
    
    // diagonal front bottom to rear top
    DrawLine(0, 7, zAway, 0, 0, zTowards, c); // diagonal left
    DrawLine(7, 7, zAway, 7, 0, zTowards, c); // diagonal right

    // rear top
    DrawLine(0, 0, zTowards, 7, 0, zTowards, c); // Bottom rear
    rDelay(50);
    SetAll(bgColor);
  }
}

void SpinOnXAxis(CRGB c, int len) {
  //-- Front upwards, rear downward --
  for (int i = 0; i < 8; i++) {
    
    // front bottom
    int yUp = i;
    int yDown = 7-i;
    
    for (int x=0; x<len; x++) {
      // diagonal front bottom to rear top
    DrawLine(x, yUp, 0, x, yDown, 7, c); // diagonal left
    
    }
    rDelay(50);
    SetAll(bgColor);
  }

  //-- Top away, bottom towards --
  for (int i = 0+1; i < (8-1); i++) {
    // front bottom
    int zAway = i;
    int zTowards = 7-i;

    for (int x=0; x<len; x++) {
      // diagonal front bottom to rear top
      DrawLine(x,7,zAway, x,0,zTowards, c); // diagonal left
    }
    
    rDelay(50);
    SetAll(bgColor);
  }
}

void SpinOnZAxis(CRGB c) {
  //-- Front rightwards, rear leftwards --
  for (int i = 0; i < 8; i++) {
    SetAll(bgColor);
    // front left
    int xUp = i;
    int xDown = 7-i;
    DrawLine(xUp,0,0, xUp,7,0, c);
    
    // diagonal front bottom to rear top
    DrawLine(xUp,0,0, xDown,0,7, c); // diagonal bottom
    DrawLine(xUp,7,0, xDown,7,7, c); // diagonal top

    // rear right
    DrawLine(xDown,0,7, xDown,7,7, c);
    rDelay(50);
  }

  //-- Right away, Left towards --
  for (int i = 0+1; i < (8-1); i++) {
    SetAll(bgColor);
    // Right moving away
    int zAway = i;
    int zTowards = 7-i;
    DrawLine(7,0,zAway, 7,7,zAway, c); // right
    
    // diagonal front bottom to rear top
    DrawLine(7,0,zAway, 0,0,zTowards, c); // diagonal bottom
    DrawLine(7,7,zAway, 0,7,zTowards, c); // diagonal top

    // Left coming towards
    DrawLine(0,0,zTowards, 0,7,zTowards, c);
    rDelay(50);
  }
}

