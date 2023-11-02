 #include "Joint.h"

const int dirPin_1 = 39;
const int stepPin_1 = 38;

const int dirPin_2 = 29;
const int stepPin_2 = 28;

const int dirPin_3 = 49;
const int stepPin_3 = 48;
#define motorInterfaceType 1

Joint joint1(motorInterfaceType, stepPin_1, dirPin_1);
Joint joint2(motorInterfaceType, stepPin_2, dirPin_2);
Joint joint3(motorInterfaceType, stepPin_3, dirPin_3);

void setup() {
    Serial.begin(115200);
    joint1.setup();
    joint1.setSpeed(200);
    joint2.setup();
    joint2.setSpeed(200);
    joint3.setup();
    joint3.setSpeed(200);
    //joint1.moveTo(2000);
    //joint1.move(-1800);
}

int desiredPos = 0;

void loop() {
    // joint1.moveToSerial();
    // joint2.moveToSerial(); // working
    // joint3.moveToSerial(); // working
    
    if (Serial.available()) {
      desiredPos = Serial.parseInt();
    }

    joint1.moveTo(desiredPos);
    joint2.moveTo(desiredPos);
    joint3.moveTo(desiredPos);
    
    // if (Serial.available()) {
    //   int desiredPos = Serial.parseInt();
    //     joint2.moveTo(desiredPos);
    //     joint3.moveTo(desiredPos);
    //     Serial.print("desiredPos: ");
    //     Serial.println(desiredPos);
    // }
}