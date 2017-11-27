void DrawXYPlane(byte z, CRGB c)
{
  for (byte x = 0; x < 8; x++)
    for (byte y = 0; y < 8; y++)
      SetPixel(x, y, z, c);
}

void DrawYZPlane(byte x, CRGB c)
{
  for (byte y = 0; y < 8; y++)
    for (byte z = 0; z < 8; z++)
      SetPixel(x, y, z, c);
}

void DrawXZPlane(byte y, CRGB c)
{
  for (byte x = 0; x < 8; x++)
    for (byte z = 0; z < 8; z++)
      SetPixel(x, y, z, c);
}

void DrawXYRect(Point a, Point b, CRGB c)
{
  DrawLine(a.x, a.y, a.z, b.x, a.y, a.z, c); // bottom line
  DrawLine(a.x, b.y, a.z, b.x, b.y, a.z, c); // top line
  DrawLine(a.x, a.y, a.z, a.x, b.y, a.z, c); // left line
  DrawLine(b.x, a.y, a.z, b.x, b.y, a.z, c); // right line
}

void DrawYZRect(Point a, Point b, CRGB c)
{
  DrawLine(a.x, a.y, a.z, a.x, a.y, b.z, c); // bottom line
  DrawLine(a.x, b.y, a.z, a.x, b.y, b.z, c); // top line
  DrawLine(a.x, a.y, a.z, a.x, b.y, a.z, c); // left line
  DrawLine(a.x, a.y, b.z, a.x, b.y, b.z, c); // right line
}

void DrawBox(Point a, Point b, CRGB c) // Hollow
{
  Point a2 = {a.x, a.y, b.z}; // point A but on the back
  Point b2 = {b.x, b.y, a.z}; // point B but in front

  DrawXYRect(a, b2, c); // front
  DrawXYRect(a2, b, c); // back

  Point b3 = {a.x, b.y, b.z}; // point B but at A's X
  Point a3 = {b.x, a.y, a.z}; // point A but at B's X
  DrawYZRect(a, b3, c); // Left
  DrawYZRect(a3, b, c); // Right
}

void DrawCube(Point a, Point b, CRGB c)
{
  int x0 = min(a.x, b.x);
  int y0 = min(a.y, b.y);
  int z0 = min(a.z, b.z);

  int height = abs(a.y - b.y);
  int width = abs(a.x - b.x);;
  int depth = abs(a.z - b.z);;

  for (int x = 0; x <= width; x++)
    for (int y = 0; y <= height; y++)
      for (int z = 0; z <= depth; z++)
        if ( (x0 + x) < 8 && (y0 + y) < 8 && (z0 + z) < 8)
          leds[ ToIndex(x0 + x, y0 + y, z0 + z) ] = c;
}

