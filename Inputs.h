const byte buttonPin00 = 4;
const byte buttonPinMax = 53; // Yes, the Arduino mega has fifty digital i/o pins!

bool Pressed[ buttonPinMax - buttonPin00];
unsigned long lastButtonPress = 0;

void SetupInputs()
{
  for (byte pin = buttonPin00; pin <= buttonPinMax; pin++)
  {
    pinMode(pin, INPUT_PULLUP);
  }
}

void ReadButtons()
{
  unsigned long threshold = 100; // How fast before we consider the same button as pressed again?
  for (int pin = buttonPin00; pin <= buttonPinMax; pin++) {
    int index = pin - buttonPin00;
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

