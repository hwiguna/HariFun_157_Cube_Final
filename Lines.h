//== Line Routines ===
//DrawLine(Point a, Point b, CRGB c)
//DrawXLine(int y, int z, CRGB c)
//DrawYLine(int x, int z, CRGB c)
//DrawZLine(int x, int y, CRGB c)
//DrawPoly(Point points[], CRGB c, byte numPoints = 4)
//DrawPairs(Point points[], CRGB c, byte numPoints = 4)

void Bresenham3D(int x1, int y1, int z1, int x2, int y2, int z2, CRGB c)
{
  // This routine is from:
  //https://gist.github.com/yamamushi/5823518
  // I only adapted it for my cube

  int i, dx, dy, dz, l, m, n, x_inc, y_inc, z_inc, err_1, err_2, dx2, dy2, dz2;
  int point[] = {x1, y1, z1};

  dx = x2 - x1;
  dy = y2 - y1;
  dz = z2 - z1;
  x_inc = (dx < 0) ? -1 : 1;
  l = abs(dx);
  y_inc = (dy < 0) ? -1 : 1;
  m = abs(dy);
  z_inc = (dz < 0) ? -1 : 1;
  n = abs(dz);
  dx2 = l << 1;
  dy2 = m << 1;
  dz2 = n << 1;

  if ((l >= m) && (l >= n)) {
    err_1 = dy2 - l;
    err_2 = dz2 - l;
    for (i = 0; i < l; i++) {
      SetPixel(point[0], point[1], point[2], c); 
      if (err_1 > 0) {
        point[1] += y_inc;
        err_1 -= dx2;
      }
      if (err_2 > 0) {
        point[2] += z_inc;
        err_2 -= dx2;
      }
      err_1 += dy2;
      err_2 += dz2;
      point[0] += x_inc;
    }
  } else if ((m >= l) && (m >= n)) {
    err_1 = dx2 - m;
    err_2 = dz2 - m;
    for (i = 0; i < m; i++) {
      SetPixel(point[0], point[1], point[2], c); 
      if (err_1 > 0) {
        point[0] += x_inc;
        err_1 -= dy2;
      }
      if (err_2 > 0) {
        point[2] += z_inc;
        err_2 -= dy2;
      }
      err_1 += dx2;
      err_2 += dz2;
      point[1] += y_inc;
    }
  } else {
    err_1 = dy2 - n;
    err_2 = dx2 - n;
    for (i = 0; i < n; i++) {
      SetPixel(point[0], point[1], point[2],c); 
      if (err_1 > 0) {
        point[1] += y_inc;
        err_1 -= dz2;
      }
      if (err_2 > 0) {
        point[0] += x_inc;
        err_2 -= dz2;
      }
      err_1 += dy2;
      err_2 += dx2;
      point[2] += z_inc;
    }
  }
  SetPixel(point[0], point[1], point[2], c); 
}

void DrawLine(int x1, int y1, int z1, int x2, int y2, int z2, CRGB c)
{
  Bresenham3D(x1, y1, z1, x2, y2, z2, c);
}

void DrawLine(Point a, Point b, CRGB c)
{
  Bresenham3D(a.x, a.y, a.z, b.x, b.y, b.z, c);
}

void DrawXLine(int y, int z, CRGB c)
{
  Point a = {0,y,z};
  Point b = {7,y,z};
  DrawLine(a,b,c);
}

void DrawYLine(int x, int z, CRGB c)
{
  Point a = {x,0,z};
  Point b = {x,7,z};
  DrawLine(a,b,c);
}

void DrawZLine(int x, int y, CRGB c)
{
  Point a = {x,y,0};
  Point b = {x,y,7};
  DrawLine(a,b,c);
}

void DrawPoly(Point points[], CRGB c, byte numPoints = 4)
{
  //int numPoints = sizeof(*points); // sizeof works most of the time except for FlipFrontToLeft(). Very odd...
  for (int i=1; i<numPoints; i++)
    DrawLine(points[i-1], points[i], c);
}

void DrawPairs(Point points[], CRGB c, byte numPoints = 4)
{
  //int numPoints = sizeof(*points); // sizeof works most of the time except for FlipFrontToLeft(). Very odd...
  for (int i=1; i<numPoints; i+=2)
    DrawLine(points[i-1], points[i], c);
}


