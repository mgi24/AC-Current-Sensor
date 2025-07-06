const int voltagePin = A3; // Pin analog untuk membaca tegangan
const int relayPin = 3;

void setup() {
  Serial.begin(115200); // Mulai komunikasi serial
  pinMode(voltagePin, INPUT); // Set voltagePin sebagai input
  pinMode(relayPin, OUTPUT); // Set relayPin sebagai output
  digitalWrite(relayPin, HIGH); // Set relay ke HIGH
}

void loop() {
  int sensorValue = analogRead(voltagePin); // Baca nilai analog
  float voltage = sensorValue * (5.0 / 1023.0); // Konversi ke volt (asumsi 5V dan 10-bit ADC)
  Serial.print(voltage);
  Serial.println();
}
