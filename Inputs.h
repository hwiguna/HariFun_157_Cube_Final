const byte button00 = 4;
const byte buttonMax = 53; // Yes, the Arduino mega has fifty digital i/o pins!

bool Pressed[ buttonMax - button00];
unsigned long lastButtonPress = 0;

void SetupInputs()
{
  for (byte pin = button00; pin <= buttonMax; pin++)
  {
    pinMode(pin, INPUT_PULLUP);
  }
}

void ReadButtons()
{
  unsigned long threshold = 100; // How fast before we consider the same button as pressed again?
  for (int pin = button00; pin <= buttonMax; pin++) {
    int index = pin - button00;
    if (digitalRead(pin) == LOW && !Pressed[ index ]) {
      unsigned long timeNow = millis();
      unsigned long timeSinceThatButtonWasPressed = timeNow - lastButtonPress;
      if (timeSinceThatButtonWasPressed >= threshold) {
        lastButtonPress = timeNow;
        Pressed[ index ] = true;
      }
    }
  }
}

