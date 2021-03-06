//=== F O N T ===
// Font courtesy of aspro648
// http://www.arduino.cc/cgi-bin/yabb2/YaBB.pl?num=1203747843/22
// May 2014 - I've added more characters so first character is space (ASCII 32).
// Note that some characters are still blank place holders.
const byte alphabets[][5] PROGMEM = {
  {0, 0, 0, 0, 0}, // Space
  {0, 0, 0, 0, 0}, // !
  {0, 0, 0, 0, 0}, // "
  {0, 0, 0, 0, 0}, // #, etc...
  {0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0},
  {62, 65, 65, 65, 62}, // 0
  {0, 33, 127, 1, 0},   // 1
  {39, 73, 73, 73, 49}, // 2
  {34, 65, 73, 73, 54}, // 3
  {120, 8, 8, 8, 127},  // 4
  {121, 73, 73, 73, 70},// 5
  {62, 73, 73, 73, 38}, // 6
  {96, 67, 76, 80, 96}, // 7
  {54, 73, 73, 73, 54}, // 8
  {50, 73, 73, 73, 62}, // 9
  {0, 0, 36, 0, 0}, // :
  {0, 0, 38, 0, 0}, // ;
  {8, 28, 54, 34, 0}, // <
  {0, 20, 20, 20, 0}, // =
  {34, 54, 28, 8, 0}, // >
  {32, 64, 69, 72, 48}, // ?
  {0, 0, 0, 0, 0}, // @
  {31, 36, 68, 36, 31},  // A
  {127, 73, 73, 73, 54}, // B
  {62, 65, 65, 65, 34}, // C, etc...
  {127, 65, 65, 34, 28},
  {127, 73, 73, 65, 65},
  {127, 72, 72, 72, 64},
  {62, 65, 65, 69, 38},
  {127, 8, 8, 8, 127},
  {0, 65, 127, 65, 0},
  {2, 1, 1, 1, 126},
  {127, 8, 20, 34, 65},
  {127, 1, 1, 1, 1},
  {127, 32, 16, 32, 127},
  {127, 32, 16, 8, 127},
  {62, 65, 65, 65, 62},
  {127, 72, 72, 72, 48},
  {62, 65, 69, 66, 61},
  {127, 72, 76, 74, 49},
  {50, 73, 73, 73, 38},
  {64, 64, 127, 64, 64},
  {126, 1, 1, 1, 126},
  {124, 2, 1, 2, 124},
  {126, 1, 6, 1, 126},
  {99, 20, 8, 20, 99},
  {96, 16, 15, 16, 96},
  {67, 69, 73, 81, 97},
};

void ShiftRightOnBackFace(byte row)
{
  // Shift everything one pixel right (on the back face)
  for (byte i = 7; i > 0; i--)
    leds[ ToIndex(i, row, 7) ] = leds[ ToIndex(i-1, row, 7) ];
}

void ShiftRightOnFrontFace(byte row)
{
  // Shift everything one pixel right (on the back face)
  for (byte i = 7; i > 0; i--)
    leds[ ToIndex(i, row, 0) ] = leds[ ToIndex(i-1, row, 0) ];
}

void ShiftBackOnLeftFace(byte row)
{
  // Shift everything one pixel towards the back
  for (byte i = 0; i < 7; i++)
    leds[ ToIndex(0, row, 7 - i) ] = leds[ ToIndex(0, row, 6 - i) ];
}

void ShiftLeftOnFrontFace(byte row)
{
  // Shift everything one pixel left
  for (byte i = 0; i < 7; i++)
    leds[ ToIndex(i, row, 0) ] = leds[ ToIndex(i + 1, row, 0) ];
}

void Recede()
{
  for (byte z = 0; z < 7; z++) {
  for (byte x = 0; x < 7; x++)
  for (byte y = 0; y < 7; y++)
    leds[ ToIndex(x, y, z+1) ] = leds[ ToIndex(x, y, z) ]; // copy to layer behind this one
    DrawXYPlane(z, CRGB::Black); // Erase this layer
    rDelay(100);
  }
}

void ComingTowards()
{
  for (byte z = 7; z > 0; z--) {
  for (byte x = 0; x < 7; x++)
  for (byte y = 0; y < 7; y++)
    leds[ ToIndex(x, y, z-1) ] = leds[ ToIndex(x, y, z) ]; // copy to layer behind this one
    DrawXYPlane(z, CRGB::Black); // Erase this layer
    rDelay(100);
  }
}

void DrawChar(int xOffset, int yOffset, int zOffset, char ch)
{
  int alphabetIndex = ch - ' ';
    if (alphabetIndex < 0) alphabetIndex = 0;

    //-- Draw one character of the message --
    // Each character is only 5 columns wide, but I loop two more times to create 2 pixel space betwen characters
    for (int col = 0; col < 7-xOffset; col++)
    {
      for (int row = 0; row < 8-yOffset; row++)
      {
        // Set the pixel to what the alphabet say for columns 0 thru 4, but always leave columns 5 and 6 blank.
        bool isOn = 0;
        byte myChar = pgm_read_byte(&(alphabets[alphabetIndex][col]));

        if (col < 5) isOn = bitRead( myChar, row ) == 1;
        SetPixel(xOffset+col, yOffset+row, zOffset, isOn ? fgColor : CRGB::Black); // We ALWAYS draw on the rightmost column, the shift loop below will scroll it leftward.
      }
      //rDelay(animRate);
    }
}

void DrawText(String msg)
{
  int numCols = 8;
  for (unsigned int charIndex = 0; charIndex < msg.length(); charIndex++)
  {
    int alphabetIndex = msg[charIndex] - ' ';
    if (alphabetIndex < 0) alphabetIndex = 0;

    //-- Draw one character of the message --
    // Each character is only 5 columns wide, but I loop two more times to create 2 pixel space betwen characters
    for (int col = 0; col < 7; col++)
    {
      for (int row = 0; row < 8; row++)
      {
        //-- Shift the bitmap one column to left --
        ShiftRightOnBackFace(row);
        ShiftBackOnLeftFace(row);
        ShiftLeftOnFrontFace(row);

        // Set the pixel to what the alphabet say for columns 0 thru 4, but always leave columns 5 and 6 blank.
        bool isOn = 0;
        byte myChar = pgm_read_byte(&(alphabets[alphabetIndex][col]));

        if (col < 5) isOn = bitRead( myChar, row ) == 1;
        SetPixel(numCols - 1, row, 0, isOn ? fgColor : CRGB::Black); // We ALWAYS draw on the rightmost column, the shift loop below will scroll it leftward.
      }
      FastLED.delay(100);
    }
  }
}
