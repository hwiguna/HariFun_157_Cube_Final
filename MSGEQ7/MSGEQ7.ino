//-- Arduino pins connected to the MSGEQ7 chip --
const byte strobePin = 2; 
const byte resetPin = 4;
const byte dcInPin = A5;

//-- Arduino pins to control how sensitive the Arduino would be to the dc output of the MSGEQ7 --
const byte lowThresholdPin = A0;
const byte highThresholdPin = A1;

void setup(){
  Serial.begin(9600);

  pinMode(resetPin, OUTPUT);
  pinMode(strobePin, OUTPUT);
//  digitalWrite(resetPin, LOW);  // Are these necessary?!
//  digitalWrite(strobePin, HIGH);// Are these necessary?!
}

void SpectrumAnalyzer()
{
  int lowThreshold = analogRead(lowThresholdPin);
  int highThreshold = analogRead(highThresholdPin);
    Serial.print(lowThreshold);
    Serial.print("-");
    Serial.print(highThreshold);
    Serial.print(": ");

  //-- Get ready to get 7 analog readins corresponding to 7 bands: 63Hz, 160Hz, 400Hz, 1kHz, 2.5kHz, 6.25kHz and 16kHz. 
  digitalWrite(resetPin, HIGH);
  digitalWrite(resetPin, LOW);

  for (int i=0;i<7;i++){
    digitalWrite(strobePin, LOW); // Data will appear upon falling edge of strobe pin
    delay(30);
    int raw = analogRead(dcInPin); // Read analog data from MSGEQ7
    int constrainedValue = constrain(raw, lowThreshold, highThreshold); // Use pots to only pay attention to a subset of each band.
    int spectrumValue = map(constrainedValue, lowThreshold, highThreshold, 0,255); // Map the filtered data to the cube coordinate.
    Serial.print(spectrumValue);
    Serial.print(" ");
    
    //DrawLine(i,0,0, i,7,0, CRGB::Black);
    //DrawLine(i,0,0, i,spectrumValue,0, CRGB::Blue);
    
    digitalWrite(strobePin, HIGH); // Get ready for next strobe
  }
  //FastLED.show();
  Serial.println();
}

void loop(){
  SpectrumAnalyzer();
}

