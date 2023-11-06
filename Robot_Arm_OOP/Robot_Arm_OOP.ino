 #include "Joint.h"

const int dirPin_1 = 29;
const int stepPin_1 = 28;

const int dirPin_2 = 35;
const int stepPin_2 = 34;

const int dirPin_3 = 41;
const int stepPin_3 = 40;
#define motorInterfaceType 1

const int powerPin = 53;

Joint joint1(motorInterfaceType, stepPin_1, dirPin_1);
Joint joint2(motorInterfaceType, stepPin_2, dirPin_2);
Joint joint3(motorInterfaceType, stepPin_3, dirPin_3);

void setup() {
    Serial.begin(115200);

    pinMode(powerPin, OUTPUT);
    digitalWrite(powerPin, HIGH);

    joint1.setup();
    joint1.setSpeed(1000);
    joint2.setup();
    joint2.setSpeed(1000);
    joint3.setup();
    joint3.setSpeed(1000);
}

int desiredPos = 0;

void loop() {
    
    if (Serial.available()) {

      desiredPos = Serial.parseInt();
    }

    joint1.moveTo(desiredPos);
    joint2.moveTo(desiredPos);
    joint3.moveTo(desiredPos);
}