String inputString = "";         // a String to hold incoming data
boolean stringComplete = false;  // whether the string is complete

byte StringToEffect(String string)
{
  byte effect = 0;

  if (string == "FX_Clear") effect = FX_Clear;
  if (string == "FX_Explode") effect = FX_Explode;
  if (string == "FX_GradualUp") effect = FX_Clear;
  if (string == "FX_GradualSide") effect = FX_GradualSide;
  if (string == "FX_FlashLineXAlongZ") effect = FX_FlashLineXAlongZ;
  
  if (string == "FX_FlipBottomToFront") effect = FX_FlipBottomToFront;
  if (string == "FX_FlipFrontToLeft") effect = FX_FlipFrontToLeft;
  if (string == "FX_FlipLeftToBack") effect = FX_FlipLeftToBack;
  if (string == "FX_FlipBackToBottom") effect = FX_FlipBackToBottom;
  if (string == "FX_SlidingCubes") effect = FX_SlidingCubes;

  if (string == "FX_Hat") effect = FX_Hat;
  if (string == "FX_HatRainbow") effect = FX_HatRainbow;

  Serial.print("effect=");Serial.println(effect);
  return effect;
}

CRGB StringToColor(String string)
{
  CRGB color = CRGB::Black;
  if (string == "Blue" ) color = CRGB::Blue;
  if (string == "Red" ) color = CRGB::Red;

  return color;
}

/*
  SerialEvent occurs whenever a new data comes in the hardware serial RX. This
  routine is run between each time loop() runs, so using delay inside loop can
  delay response. Multiple bytes of data may be available.
*/
void serialEvent1() {
  while (Serial1.available()) {
    // get the new byte:
    char inChar = (char)Serial1.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}

void ExecuteSerialCommand() {

  if (stringComplete) {
    inputString += " ";
    Serial.println(inputString);

    byte rate = 60;
    byte nTimes = 1;
    String param0 = inputString;
    String param1;
    int pos0 = param0.indexOf(' ');
    if (pos0 != -1)  {
      param0 = inputString.substring(0,pos0);
      int pos1 = inputString.indexOf(' ', pos0+1);
      {
        if (pos1 != -1)  {
          param1 = inputString.substring(pos0+1,pos1);
        }
      }
    }
    Serial.print("param0='");Serial.print(param0);Serial.println("'");
    Serial.print("param1='");Serial.print(param1);Serial.println("'");
    
    byte effect = StringToEffect(param0);
    CRGB color = StringToColor(param1);
    Serial.print("effect='");Serial.print(effect);Serial.println("'");
    Serial.print("color='");Serial.print(color);Serial.println("'");

    switch (effect)
    {
      case FX_Clear: SetAll(bgColor); break;
      case FX_Explode: Explode(StringToColor(param1), 200); break;
      case FX_GradualUp: BouncePlane(1, nTimes, fgColor, 100); SetAll(bgColor); break;
      case FX_GradualSide: BouncePlane(2, nTimes, fgColor, 100); SetAll(bgColor); break;
      case FX_Char1: DrawChar(1, 0, 7, '1'); ComingTowards(); break;
      case FX_Char2: DrawChar(1, 0, 7, '2'); ComingTowards(); break;
      case FX_Char3: DrawChar(1, 0, 7, '3'); ComingTowards(); break;
      case FX_FlipBottomToFront: FlipBottomToFront(fgColor, rate); break;
      case FX_FlipFrontToLeft: FlipFrontToLeft(fgColor, rate); break;
      case FX_FlipLeftToBack: FlipLeftToBack(fgColor, rate); break;
      case FX_FlipBackToBottom: FlipBackToBottom(fgColor, rate); break;
      case FX_SlidingCubes: SlidingCubes(); break;
      case FX_Hat: StaticHatXY(); break;
      case FX_HatRainbow: StaticHatXYRainbow(); break;
      default: break;
        //StaticHatXY();
        //GrowFromCenter(0, fgColor, rate);
        //ShrinkToCenter(0, fgColor, rate);
    }

    // clear the string:
    inputString = "";
    stringComplete = false;
  }
}


