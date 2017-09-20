// Wireframe Animations

void FlipSlant(Point origin, int from, int to, CRGB c, int rate, Point rotations)
{
  Point width = {7,7,7};
  int dir = (to > from ? 1 : -1);
  Point offset = {0, 0, width.z};

  // Draw static line
  DrawLine(origin.x, origin.y, origin.z, origin.x + width.x, origin.y, origin.z, c);

  for (int i = from; i <= to; i + dir)
  {
    // Draw opposite moving line
    DrawLine(origin.x, origin.y + i, origin.z + offset.z, origin.x + width.x, origin.y + i, origin.z + offset.z, c);

    // Draw connecting lines
    DrawLine(origin.x,         origin.y, origin.z,  origin.x,             origin.y + i, origin.z + offset.z, c);
    DrawLine(origin.x + width.x, origin.y, origin.z,  origin.x + width.x, origin.y + i, origin.z + offset.z, c);
  }
}

