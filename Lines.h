//== Line Routines ===

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

