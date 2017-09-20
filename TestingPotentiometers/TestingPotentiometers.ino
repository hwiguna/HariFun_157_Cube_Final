void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
}

void loop() {
  Serial.print("A0 = ");
  Serial.print(analogRead(A0));

  Serial.print("  A1 = ");
  Serial.print(analogRead(A1));

  Serial.print("  A2 = ");
  Serial.print(analogRead(A2));

  Serial.print("  A3 = ");
  Serial.println(analogRead(A3));

  delay(100);
}
