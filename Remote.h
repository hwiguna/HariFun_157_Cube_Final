const int bluePin = 16;

void SetupRemote()
{
  pinMode(bluePin,INPUT);
}

void CheckRemote()
{
  if (digitalRead(bluePin))
    Serial.println("BLUE");
}

