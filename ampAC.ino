const int analogPin = A3;
const int relayPin = 3;

void setup() {
  pinMode(analogPin, INPUT);
  pinMode(relayPin, OUTPUT);
  Serial.begin(115200);
  digitalWrite(relayPin, HIGH);  //ON
}
float tresh = 0.3;         // 15mV
float normalpeak = 2.515;    // 2.515V positive peak
float normalvalley = 2.475;  // 2.475V negative peak
bool tripped = false;

void loop() {

  int analogValue = analogRead(analogPin);
  float voltage = analogValue * (5.0 / 1023.0);
  static unsigned long lastMillis = 0;

  static int faultCount = 0;
  if (!tripped && (voltage > normalpeak + tresh || voltage < normalvalley - tresh)) {
    faultCount++;
    Serial.print("Trip voltage: ");
    Serial.println(voltage, 3);
    
    if (faultCount >= 2) {
      Serial.println("TRIPPED!");
      digitalWrite(relayPin, LOW);  // OFF
      tripped = true;
    }
  } else {
    if (faultCount>0){
      Serial.print("Noise count");
      Serial.println(faultCount);
      faultCount = 0;
    }
    
  }
  static int count = 0;
  static float sum = 0;
  static float minVal = 100.0;
  static float maxVal = 0.0;
  if (!tripped) {
    

    sum += voltage;
    if (voltage < minVal) minVal = voltage;
    if (voltage > maxVal) maxVal = voltage;
    count++;

    if (millis() - lastMillis >= 40) {
      float avg = sum / count;
      // Serial.print("avg:");
      // Serial.print(avg, 3);
      // Serial.print(",max:");
      // Serial.print(maxVal, 3);
      // Serial.println(",min:");
      // Serial.println(minVal, 3);

      // Serial.print("Loops per second: ");
      // Serial.println(count);
      lastMillis = millis();
      count = 0;
      sum = 0;
      minVal = 100.0;
      maxVal = 0.0;
      
    }

  }
}
