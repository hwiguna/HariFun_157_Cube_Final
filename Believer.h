
void WaitFor(unsigned long timeToWaitFor)
{
  timeToWaitFor = timeToWaitFor + timeOffset;
  while ((millis() - timeZero) < timeToWaitFor) {};
}

void Believer()
{
  if (effectIndex == 0) {
    timeZero = millis();
    Serial.print('0');
    effectIndex++;
  }

  CRGB drumColor = CRGB::Red;

  WaitFor(316); Explode(CRGB::White, 200);
  WaitFor(1274); SetAll(CRGB::Black);

  WaitFor(1757); DrawXZPlane(0, drumColor); DrawXZPlane(1, drumColor);
  WaitFor(1918); DrawXZPlane(2, drumColor); DrawXZPlane(3, drumColor);
  WaitFor(2079); DrawXZPlane(4, drumColor); DrawXZPlane(5, drumColor);
  WaitFor(2226); DrawXZPlane(6, drumColor); DrawXZPlane(7, drumColor);

  WaitFor(3197); SetAll(CRGB::Black);

  WaitFor(3678); DrawXZPlane(0, drumColor); DrawXZPlane(1, drumColor);
  WaitFor(3836); DrawXZPlane(2, drumColor); DrawXZPlane(3, drumColor);
  WaitFor(3997); DrawXZPlane(4, drumColor); DrawXZPlane(5, drumColor);
  WaitFor(4145); DrawXZPlane(6, drumColor); DrawXZPlane(7, drumColor);

  WaitFor(5117); SetAll(CRGB::Black);

  WaitFor(5558); DrawXZPlane(0, drumColor); DrawXZPlane(1, drumColor);
  WaitFor(5759); DrawXZPlane(2, drumColor); DrawXZPlane(3, drumColor);
  WaitFor(5919); DrawXZPlane(4, drumColor); DrawXZPlane(5, drumColor);
  WaitFor(6070); DrawXZPlane(6, drumColor); DrawXZPlane(7, drumColor);

  WaitFor(7036); SetAll(CRGB::Black);

  //-- First things first...
  WaitFor(7927); DrawChar(1, 0, 7, '1');
  ComingTowards(); // Recede();

  //9430 I'm a say all the words inside my
  WaitFor(8940); FlashLineXAlongZ(0, drumColor);
  WaitFor(9430); DrawXLine(0, 6, drumColor); DrawXLine(0, 7, drumColor);
  WaitFor(9598); DrawXLine(0, 4, drumColor); DrawXLine(0, 5, drumColor);
  WaitFor(9756); DrawXLine(0, 2, drumColor); DrawXLine(0, 3, drumColor);
  WaitFor(9908); DrawXLine(0, 1, drumColor);

  // Head. I'm tired of and
  //WaitFor(8940); FlashLineXAlongZ(0, drumColor);
  WaitFor(11352); DrawZLine(1, 0, drumColor); DrawZLine(1, 1, drumColor);
  WaitFor(11517); DrawZLine(1, 2, drumColor); DrawZLine(1, 3, drumColor);
  WaitFor(11677); DrawZLine(1, 4, drumColor); DrawZLine(1, 5, drumColor);
  WaitFor(11837); DrawZLine(1, 6, drumColor); DrawZLine(1, 7, drumColor);

  // Tired of the way that things have been oh
  //WaitFor(8940); FlashLineXAlongZ(0, drumColor);
  WaitFor(13237); DrawZLine(2, 0, drumColor); DrawZLine(2, 1, drumColor);
  WaitFor(13436); DrawZLine(2, 2, drumColor); DrawZLine(2, 3, drumColor);
  WaitFor(13586); DrawZLine(2, 4, drumColor); DrawZLine(2, 5, drumColor);
  WaitFor(13748); DrawZLine(2, 6, drumColor); DrawZLine(2, 7, drumColor);

  // ooo
  //WaitFor(8940); FlashLineXAlongZ(0, drumColor);
  WaitFor(17110); DrawZLine(3, 0, drumColor); DrawZLine(3, 1, drumColor);
  WaitFor(17275); DrawZLine(3, 2, drumColor); DrawZLine(3, 3, drumColor);
  WaitFor(17435); DrawZLine(3, 4, drumColor); DrawZLine(3, 5, drumColor);
  WaitFor(17586); DrawZLine(3, 6, drumColor); DrawZLine(3, 7, drumColor);

  // The way that thing has been oh ooo
  //WaitFor(8940); FlashLineXAlongZ(0, drumColor);
  WaitFor(19036); DrawZLine(4, 0, drumColor); DrawZLine(4, 1, drumColor);
  WaitFor(19194); DrawZLine(4, 2, drumColor); DrawZLine(4, 3, drumColor);
  WaitFor(19331); DrawZLine(4, 4, drumColor); DrawZLine(4, 5, drumColor);
  WaitFor(19504); DrawZLine(4, 6, drumColor); DrawZLine(4, 7, drumColor);

  // ooo
  //WaitFor(8940); FlashLineXAlongZ(0, drumColor);
  WaitFor(20958); DrawZLine(5, 0, drumColor); DrawZLine(5, 1, drumColor);
  WaitFor(21120); DrawZLine(5, 2, drumColor); DrawZLine(5, 3, drumColor);
  WaitFor(21275); DrawZLine(5, 4, drumColor); DrawZLine(5, 5, drumColor);
  WaitFor(21428); DrawZLine(5, 6, drumColor); DrawZLine(5, 7, drumColor);

  // Second thing
  WaitFor(23147); SetAll(CRGB::Black); DrawChar(1, 0, 7, '2');
  ComingTowards(); // Recede();

  WaitFor(26000); SetAll(CRGB::Black);

  WaitFor(0xFFFFFF);
}
