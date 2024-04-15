const int sensorMinValue = 0; // Minimum analog reading from the sensor during calibration
const int sensorMaxValue = 1680; // Maximum analog reading from the sensor during calibration
const int dbMinValue = 30; // Minimum sound level in dB (corresponding to sensorMinValue)
const int dbMaxValue = 130; // Maximum sound level in dB (corresponding to sensorMaxValue)

void setup() {
  pinMode(A0, INPUT); // Set the sound sensor pin as input
  pinMode(3, OUTPUT);                             
  pinMode(4, OUTPUT);                                           
  pinMode(5, OUTPUT);
                    
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);

  Serial.begin(9600);
}

void loop() {
  unsigned int sample;
  unsigned long startMillis = millis();
  unsigned int signalMax = 0;
  unsigned int signalMin = 1024;

  // Collect data for 50 mS
  while (millis() - startMillis < 50) {
    sample = analogRead(A0); // Get reading from sound sensor
    if (sample < 1024) { // Discard spurious readings
      if (sample > signalMax) {
        signalMax = sample; // Save max level
      } else if (sample < signalMin) {
        signalMin = sample; // Save min level
      }
    }
  }

  // Calculate peak-to-peak amplitude
  float peakToPeak = signalMax - signalMin;

  // Map peak-to-peak amplitude to dB using calibration data
  int db = map(peakToPeak, sensorMinValue, sensorMaxValue, dbMinValue, dbMaxValue);

  Serial.print("Loudness: ");
  Serial.print(db);
  Serial.println(" dB");

  // Output level indication based on sound level
  if (db <= 60) {
    Serial.println("Level: Quiet");
    digitalWrite(3, HIGH);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
  } else if (db > 60 && db < 85) {
    Serial.println("Level: Moderate");
    digitalWrite(3, LOW);
    digitalWrite(4, HIGH);
    digitalWrite(5, LOW);
  } else if (db >= 85) {
    Serial.println("Level: High");
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, HIGH);
  }

  delay(200);
}