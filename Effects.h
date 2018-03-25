const byte FX_Clear = 1;
const byte FX_Explode = 2;
const byte FX_GradualUp = 3;
const byte FX_GradualSide = 4;
const byte FX_FlashLineXAlongZ = 5;

const byte FX_FlipBottomToFront = 6;
const byte FX_FlipFrontToLeft = 7;
const byte FX_FlipLeftToBack = 8;
const byte FX_FlipBackToBottom = 9;
const byte FX_SlidingCubes = 10;

const byte FX_Char1 = 11;
const byte FX_Char2 = 12;
const byte FX_Char3 = 13;

byte ButtonToEffect(byte buttonIndex)
{
  byte effect;
  switch (buttonIndex)
  {
    case 0: effect = FX_Char1; break;
    case 1: effect = FX_Char2; break;
    case 2: effect = FX_Char3; break;
    case 3: effect = FX_GradualUp; break;
    case 4: effect = FX_FlashLineXAlongZ; break;
    case 5: effect = FX_GradualSide ; break;
    case 6: effect = FX_FlipBottomToFront; break;
    case 7: effect = FX_FlipFrontToLeft; break;
    case 8: effect = FX_Explode; break;
    case 9: effect = FX_Clear; break;
  }

  return effect;
}

