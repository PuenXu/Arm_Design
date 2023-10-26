 #include "Joint.h"

const int dirPin = 39;
const int stepPin = 38;
#define motorInterfaceType 1

Joint joint1(motorInterfaceType, stepPin, dirPin);

void setup() {
    Serial.begin(115200);
    joint1.setup();
    joint1.setSpeed(500);
    //joint1.moveTo(2000);
    //joint1.move(-1800);
}

void loop() {
    joint1.moveToSerial();
}