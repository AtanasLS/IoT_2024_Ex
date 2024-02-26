int sensorValue;
int digitalValue;


void setup() {
  Serial.begin(9600);
  pinMode(A0, OUTPUT);
  pinMode(26, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  sensorValue = analogRead(A0);
  digitalValue = digitalRead(26);

  if (sensorValue > 400)
  {
    digitalWrite(A0, HIGH);
  }
  else
    digitalWrite(26, LOW);
  Serial.println(sensorValue, DEC); // prints the value read
  Serial.println(digitalValue, DEC);
  delay(1000); // wait 100ms for next reading
}
