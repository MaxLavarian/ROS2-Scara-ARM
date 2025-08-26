#include <AccelStepper.h>
#include <MultiStepper.h>
#include <Servo.h>

AccelStepper stepper1(1, 2, 5); // STEP, DIR
AccelStepper stepper2(1, 3, 6);
AccelStepper stepper3(1, 4, 7);

const byte enablePin = 8;
const int servoGripperPin = 11;
const int  servoTwistPin = 10;    
Servo mygripper;
Servo myTwist;  

const int myGripperPosInitial = 60;
const int myGripperPosOpen = 60;
const int myGripperPosClose= 120;

const int myTwistPosInitial = 70;
const int myTwistPosOpen = 70;
const int myTwistPosClose= 160;

int myGripperPosCurrent;
int myTwistPosCurrent;;

MultiStepper steppers;

long targetPositions[3]; // posizioni di destinazione

void setup() {
  mygripper.attach(servoGripperPin);
  mygripper.write(myGripperPosInitial);
  myGripperPosCurrent = myGripperPosInitial;

  myTwist.attach(servoTwistPin);
  myTwist.write(myTwistPosInitial);
  myTwistPosCurrent = myTwistPosInitial;

  pinMode(enablePin, OUTPUT);
  digitalWrite(enablePin,LOW);
  stepper1.setMaxSpeed(2500.0);
  stepper2.setMaxSpeed(2500.0);
  stepper3.setMaxSpeed(2500.0);

  steppers.addStepper(stepper1);
  steppers.addStepper(stepper2);
  steppers.addStepper(stepper3);

  Serial.begin(115200);
  while (!Serial);
  Serial.println("Initialize OK");
}

void moveMultiSteppers(long x, long y, long z)  {
   if (x > 3500) { targetPositions[0] =3500; } else { targetPositions[0] =x; }
   if (x < -3500) { targetPositions[0] =-3500; } else { targetPositions[0] =x; }

   if (y > 3500) { targetPositions[1] =3500; } else { targetPositions[1] =y; }
   if (y < -3500) { targetPositions[1] =-3500; } else { targetPositions[1] =y; }

   if (z > 15000) { targetPositions[2] =15000; } else { targetPositions[2] =z; }
   if (z < -15000) { targetPositions[2] =-15000; } else { targetPositions[2] =z; }

    steppers.moveTo(targetPositions);
    steppers.runSpeedToPosition();  // Bloccante fino al completamento

    Serial.println("Move x= " +String( x) + " y= " + String(y) + " z= " + String(z)  );
}

void servoSweep(Servo myservo, uint8_t startAngle, uint8_t stopAngle, uint8_t stepAngle = 1, unsigned long stepTime = 15) {
   if (startAngle > 180) {
  //    Serial.print("ERROR: The startAngle value of ");
  //    Serial.print(startAngle);
  //    Serial.println(" is out of range.");
      return;
   }
   if (stopAngle > 180) {
   //   Serial.print("ERROR: The stopAngle value of ");
   //   Serial.print(stopAngle);
   //   Serial.println(" is out of range.");
      return;
   }
   if (stepAngle < 1 || stepAngle > abs(stopAngle - startAngle)) {
   //   Serial.print("ERROR: The stepAngle value of ");
   //   Serial.print(stepAngle);
   //   Serial.println(" is out of range.");
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

void loop() {
  if (Serial.available()) {
    String input = Serial.readStringUntil('\n');  // es. "100 200 -50"
    Serial.println("elaboro: "  + input);

    int space1 = input.indexOf(' ');
    int space2 = input.indexOf(' ', space1 + 1);
    int space3 = input.indexOf(' ', space2 + 1);
    int space4 = input.indexOf(' ', space3 + 1);

    
    long val1 = input.substring(0, space1).toInt();
    long val2 = input.substring(space1 + 1, space2).toInt();
    long val3 = input.substring(space2 + 1, space3).toInt();
    int val4= input.substring(space3 + 1, space4).toInt();
    int val5= input.substring(space4 + 1).toInt();
    
   moveMultiSteppers ( val1, val2, val3);

    if (val4 == 0) { 
      Serial.println("gripper open " + String(myGripperPosCurrent));  
       servoSweep( mygripper, myGripperPosCurrent, myGripperPosOpen);
       myGripperPosCurrent = myGripperPosOpen;
    } else {   
      Serial.println("gripper close" + String(myGripperPosCurrent));   
       servoSweep(mygripper, myGripperPosCurrent, myGripperPosClose );
       myGripperPosCurrent = myGripperPosClose;
    } 

      if (val5== 0) { 
      Serial.println("twist open " + String (  myTwistPosCurrent)  );  
       servoSweep(myTwist, myTwistPosCurrent, myTwistPosOpen);
       myTwistPosCurrent = myTwistPosOpen;
    } else {   
      Serial.println("twist close " + String (  myTwistPosCurrent) );   
      Serial.println(  myTwistPosCurrent); 
       servoSweep(myTwist, myTwistPosCurrent, myTwistPosClose );
       myTwistPosCurrent = myTwistPosClose;
    } 

    
  }
}
