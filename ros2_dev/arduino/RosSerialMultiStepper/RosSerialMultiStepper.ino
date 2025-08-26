#include <AccelStepper.h>
#include <MultiStepper.h>

AccelStepper stepper1(1, 2, 5); // STEP, DIR
AccelStepper stepper2(1, 3, 6);
AccelStepper stepper3(1, 4, 7);

const byte enablePin = 8;
MultiStepper steppers;

long targetPositions[3]; // posizioni di destinazione

void setup() {
  pinMode(enablePin, OUTPUT);
  digitalWrite(enablePin,LOW);
  Serial.begin(115200);
  Serial.println("Initialize OK");

  stepper1.setMaxSpeed(1000.0);
  stepper2.setMaxSpeed(1000.0);
  stepper3.setMaxSpeed(1000.0);

  steppers.addStepper(stepper1);
  steppers.addStepper(stepper2);
  steppers.addStepper(stepper3);
}

void loop() {
  if (Serial.available()) {
    String input = Serial.readStringUntil('\n');  // es. "100 200 -50"
    Serial.println("elaboro"  + input);

    int space1 = input.indexOf(' ');
    int space2 = input.indexOf(' ', space1 + 1);

    long val1 = input.substring(0, space1).toInt();
    long val2 = input.substring(space1 + 1, space2).toInt();
    long val3 = input.substring(space2 + 1).toInt();

    targetPositions[0] = val1;
    targetPositions[1] = val2;
    targetPositions[2] = val3;

    steppers.moveTo(targetPositions);
    steppers.runSpeedToPosition();  // Bloccante fino al completamento
  }
}
