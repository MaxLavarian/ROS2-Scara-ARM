void setup() {
  Serial.begin(115200);
  pinMode(13, OUTPUT); // LED built-in
  digitalWrite(13, LOW);
}

void loop() {
  if (Serial.available()) {
    char input = Serial.read();
    if (input == '1') {
      Serial.println("Led ON");
      digitalWrite(13, HIGH);
    } else if (input == '0') {
      Serial.println("Led OFF");
      digitalWrite(13, LOW);
    }
  }
}
