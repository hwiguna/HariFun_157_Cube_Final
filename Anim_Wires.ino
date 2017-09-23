// Wireframe Animations

void FlipSlant(Point origin, int from, int to, CRGB c, int rate, Point rotations)
{
  Point width = {7, 7, 7};
  int dir = (to > from ? 1 : -1);
  Point offset = {0, 0, width.z};

  // Draw static horizontal line (bottom front)
  DrawLine(origin.x, origin.y, origin.z, origin.x + width.x, origin.y, origin.z, c);

  for (int i = from; i != to + dir; i += dir)
  {
    for (byte ci = 0; ci < 2; ci++) {
      CRGB kolor = (ci == 0) ? c : bgColor;

      // Draw opposite moving line
      DrawLine(origin.x, origin.y + i, origin.z + offset.z, origin.x + width.x, origin.y + i, origin.z + offset.z, kolor);

      // Draw connecting lines
      DrawLine(origin.x,         origin.y, origin.z,  origin.x,             origin.y + i, origin.z + offset.z, kolor);
      DrawLine(origin.x + width.x, origin.y, origin.z,  origin.x + width.x, origin.y + i, origin.z + offset.z, kolor);
      if (ci == 0) FastLED.delay(rate);
    }
  }

  DrawLine(origin.x, origin.y, origin.z, origin.x + width.x, origin.y, origin.z, bgColor);
  FastLED.show();
}

void FlipBottomToFront(CRGB c, int rate)
{
  Point origin = {0, 0, 0};
  Point width = {7, 7, 7};
  Point offset = {width.x, width.y, width.z};

  // Draw static line
  DrawLine(origin.x, origin.y, origin.z, origin.x + width.x, origin.y, origin.z, c);

  // Bottom to top
  for (int i = 0; i < 8; i++)
  {
    Point points[4];
    points[0] = origin;
    points[1] = {origin.x,           origin.y + i, origin.z + offset.z};
    points[2] = {origin.x + width.x, origin.y + i, origin.z + offset.z};
    points[3] = {origin.x + width.x, origin.y,     origin.z};

    DrawLines(points, c);
    FastLED.delay(rate);
    DrawLines(points, bgColor);
  }

  // Back to front (on top)
  for (int i=6; i>=0; i--)
  {
    Point points[4];
    points[0] = origin;
    points[1] = {origin.x,           origin.y + offset.y, origin.z + i};
    points[2] = {origin.x + width.x, origin.y + offset.y, origin.z + i};
    points[3] = {origin.x + width.x, origin.y,     origin.z};

    DrawLines(points, c);
    FastLED.delay(rate);
    if (i!=0) DrawLines(points, bgColor);
  }
}

void FlipFrontToRight(CRGB c, int rate)
{
  Point origin = {7, 0, 0};
  Point width = {7, 7, 7};
  Point offset = {width.x, width.y, width.z};

  // Draw static vertical line (front right)
  DrawLine(origin.x, origin.y, origin.z, origin.x, origin.y + width.y, origin.z, c);

  // Front to back
  for (int i = 0; i < 8; i++)
  {
    Point points[4];
    points[0] = origin;
    points[1] = {origin.x - width.x, origin.y,          origin.z + i};
    points[2] = {origin.x - width.x, origin.y+offset.y, origin.z + i};
    points[3] = {origin.x,           origin.y+offset.y, origin.z};

    DrawLines(points, c);
    FastLED.delay(rate);
    DrawLines(points, bgColor);
  }

  // left to right (on back)
  for (int i=6; i>=0; i--)
  {
    Point points[4];
    points[0] = origin;
    points[1] = {origin.x - i, origin.y,          origin.z + offset.z};
    points[2] = {origin.x - i, origin.y+offset.y, origin.z + offset.z};
    points[3] = {origin.x,     origin.y+offset.y, origin.z};

    DrawLines(points, c);
    FastLED.delay(rate);
    if (i!=0) DrawLines(points, bgColor);
  }
}

void FlipFrontToLeft(CRGB c, int rate)
{
  Point origin = {0, 0, 0};
  Point width = {7, 7, 7};
  Point offset = {width.x, width.y, width.z};

  // Draw static vertical line (front left)
  DrawLine(origin.x, origin.y, origin.z, origin.x, origin.y + width.y, origin.z, c);

  // Front to back (on right side)
  for (int i = 0; i < 8; i++)
  {
    Point points[4];
    points[0] = origin;
    points[1] = {origin.x + width.x, origin.y,          origin.z + i};
    points[2] = {origin.x + width.x, origin.y+offset.y, origin.z + i};
    points[3] = {origin.x,           origin.y+offset.y, origin.z};

    DrawLines(points, c);
    FastLED.delay(rate);
    DrawLines(points, bgColor);
  }

  // right to left (on back)
  for (int i=6; i>=0; i--)
  {
    Point points[4];
    points[0] = origin;
    points[1] = {origin.x + i, origin.y,          origin.z + offset.z};
    points[2] = {origin.x + i, origin.y+offset.y, origin.z + offset.z};
    points[3] = {origin.x,     origin.y+offset.y, origin.z};

    DrawLines(points, c);
    FastLED.delay(rate);
    if (i!=0) DrawLines(points, bgColor);
  }
}

void FlipLeftToBack(CRGB c, int rate)
{
  Point origin = {0, 0, 7};
  Point width = {7, 7, 7};
  Point offset = {width.x, width.y, width.z};

  // Draw static vertical line (back left)
  DrawLine(origin.x, origin.y, origin.z, origin.x, origin.y + width.y, origin.z, c);

  // Left to right (on front)
  for (int i = 0; i < 8; i++)
  {
    Point points[4];
    points[0] = origin;
    points[1] = {origin.x + i, origin.y,          origin.z - width.z};
    points[2] = {origin.x + i, origin.y+offset.y, origin.z - width.z};
    points[3] = {origin.x,           origin.y+offset.y, origin.z};

    DrawLines(points, c);
    FastLED.delay(rate);
    DrawLines(points, bgColor);
  }

  // front to back (on right)
  for (int i=1; i<8; i++)
  {
    Point points[4];
    points[0] = origin;
    points[1] = {origin.x + width.x, origin.y,          origin.z - width.z + i};
    points[2] = {origin.x + width.x, origin.y+offset.y, origin.z - width.z + i};
    points[3] = {origin.x,           origin.y+offset.y, origin.z};

    DrawLines(points, c);
    FastLED.delay(rate);
    if (i<7) DrawLines(points, bgColor);
  }
}

void FlipBackToRight(CRGB c, int rate)
{
  Point origin = {7, 0, 7};
  Point width = {7, 7, 7};
  Point offset = {width.x, width.y, width.z};

  // Draw static vertical line (back right)
  DrawLine(origin.x, origin.y, origin.z, origin.x, origin.y + width.y, origin.z, c);

  // back to front (on left)
  for (int i = 0; i < 8; i++)
  {
    Point points[4];
    points[0] = origin;
    points[1] = {origin.x - width.x, origin.y,          origin.z - i};
    points[2] = {origin.x - width.x, origin.y+offset.y, origin.z - i};
    points[3] = {origin.x,           origin.y+offset.y, origin.z};

    DrawLines(points, c);
    FastLED.delay(rate);
    DrawLines(points, bgColor);
  }

  // left to right (on front)
  for (int i=1; i<8; i++)
  {
    Point points[4];
    points[0] = origin;
    points[1] = {origin.x - width.x + i, origin.y,          origin.z - width.z};
    points[2] = {origin.x - width.x + i, origin.y+offset.y, origin.z - width.z};
    points[3] = {origin.x,           origin.y+offset.y, origin.z};

    DrawLines(points, c);
    FastLED.delay(rate);
    if (i<7) DrawLines(points, bgColor);
  }
}

void FlipBackToBottom(CRGB c, int rate)
{
  Point origin = {0, 0, 7};
  Point width = {7, 7, 7};
  Point offset = {width.x, width.y, width.z};

  // Draw static horizontal line (bottom back)
  DrawLine(origin.x, origin.y, origin.z, origin.x + width.x, origin.y, origin.z, c);

  // Back to front (on top)
  for (int i=7; i>=0; i--)
  {
    Point points[4];
    points[0] = origin;
    points[1] = {origin.x,           origin.y + offset.y, origin.z - width.z + i};
    points[2] = {origin.x + width.x, origin.y + offset.y, origin.z - width.z + i};
    points[3] = {origin.x + width.x, origin.y,     origin.z};

    DrawLines(points, c);
    FastLED.delay(rate);
    DrawLines(points, bgColor);
  }
  
  // top to bottom (in front)
  for (int i = 6; i >= 0; i--)
  {
    Point points[4];
    points[0] = origin;
    points[1] = {origin.x,           origin.y + i, origin.z - width.z};
    points[2] = {origin.x + width.x, origin.y + i, origin.z - width.z};
    points[3] = {origin.x + width.x, origin.y,     origin.z};

    DrawLines(points, c);
    FastLED.delay(rate);
    if (i!=0) DrawLines(points, bgColor);
  }

}
