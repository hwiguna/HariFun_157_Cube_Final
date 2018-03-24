int led = 13;

unsigned long recording[][2] =
{
{5398,105},
{6206,105},
{6944,112},
{7119,112},
{7288,112},
{7506,112},
{7678,112},
{8435,105},
{9274,105},
{10058,105},
{10841,112},
{11016,112},
{11191,112},
{11381,112},
{11567,112},
{12325,105},
{13105,105},
{13842,105},
{14633,112},
{14806,112},
{14984,112},
{15168,112},
{15364,112},
};

void setup() {
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);

  unsigned long beginningOfTime;
  for (int index = 0; index < sizeof(recording) / sizeof(unsigned int) / 2; index++)
  {
    if (index==0)
    {
      // We start time upon first note.
      beginningOfTime = millis();
    }
    else
    {
      //-- Wait till recording[i] time or after --
      while ( (millis() - beginningOfTime) < recording[index][0] ) delay(100);
    }

    //-- Play the char --
    digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(50);                 // wait for a bit
    digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
  }
}

void loop() {
  // nothing to see here...
}
