const byte button00 = 4;
const byte buttonMax = 53; // Yes, the Arduino mega has fifty digital i/o pins!

bool Pressed[ buttonMax - button00];

void SetupInputs()
{
  for (byte pin = button00; pin <= buttonMax; pin++)
  {
    pinMode(pin, INPUT_PULLUP);
  }
}

void ReadButtons()
{
  for (;;)
    for (int pin = button00; pin <= buttonMax; pin++)
      if (digitalRead(pin) == LOW) {
        Pressed[ pin - button00 ] = true;
      }
}

