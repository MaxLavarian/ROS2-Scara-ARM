#include <Servo.h>

Servo myservo;  // create Servo object to control a servo

int pos = 10;    // variable to store the servo position
int initialpos = 43;
int mycurrpos;

void setup() {
  myservo.attach(pos);
  myservo.write(initialpos);
  mycurrpos = initialpos;
  
  Serial.begin(115200);
  while (!Serial);
  Serial.println(" Servo Initializate");
}


void servoSweep(uint8_t startAngle, uint8_t stopAngle, uint8_t stepAngle = 1, unsigned long stepTime = 15) {
   if (startAngle > 180) {
      Serial.print("ERROR: The startAngle value of ");
      Serial.print(startAngle);
      Serial.println(" is out of range.");
      return;
   }
   if (stopAngle > 180) {
      Serial.print("ERROR: The stopAngle value of ");
      Serial.print(stopAngle);
      Serial.println(" is out of range.");
      return;
   }
   if (stepAngle < 1 || stepAngle > abs(stopAngle - startAngle)) {
      Serial.print("ERROR: The stepAngle value of ");
      Serial.print(stepAngle);
      Serial.println(" is out of range.");
      return;
   }

   if (startAngle < stopAngle) {
      for (int angle = startAngle; angle <= stopAngle; angle += stepAngle) {
         myservo.write(angle);
         delay(stepTime);
      }
   } else {
      for (int angle = startAngle; angle >= stopAngle; angle -= stepAngle) {
         myservo.write(angle);
         delay(stepTime);
      }
   }
}

void userInputOperations() {
  
   if (Serial.available() > 0) {
     String cmd = Serial.readStringUntil('\n');
      int angle = cmd.toInt();
      if (angle < 0 || angle > 180) {
         Serial.print("ERROR: The angle value of ");
         Serial.print(angle);
         Serial.println(" is out of range.");
         return;
      }
       Serial.print("Setting angle to ");
       Serial.print(angle);
       Serial.println(" degrees.");

       servoSweep(mycurrpos, angle);
       mycurrpos = angle;
       
       //myservo.write(angle);
   }
}

void loop() {
  userInputOperations();
 // servoSweep(0, 180);
}
