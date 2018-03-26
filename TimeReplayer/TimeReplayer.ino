int led = 13;

unsigned long recording[][2] = 
{{8,55},
{1052,54},
{1561,49},
{1712,49},
{1869,49},
{2041,49},
{3037,51},
{3482,50},
{3640,50},
{3805,50},
{3981,50},
{5002,51},

};

void setup() {
  Serial.begin(9600);
  
  // initialize the digital pin as an output.
  for (byte p=0; p<10; p++)
  pinMode(2+p, OUTPUT);

  //delay(2000); // wait for Hari to start the Processing sketch that plays the mp3 when this sketch sends "0" via COM port.
  Serial.print('0');
  delay(300); // if Arduino is late, lower this number

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
    int whichLed = recording[index][1] - '0' + 2; // Subtract char relative to '0' on the PC keyboard, add 2 because first led starts at D2.
    //whichLed = 2;
    digitalWrite(whichLed, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(50);                 // wait for a bit
    digitalWrite(whichLed, LOW);    // turn the LED off by making the voltage LOW
  }
}

void loop() {
  // nothing to see here...
}
