#include "Joint.h"

Joint::Joint(int motorInterfaceType, int stepPin, int dirPin) : stepper(motorInterfaceType, stepPin, dirPin) {}

void Joint::setup() {
    stepper.setMaxSpeed(1000);
    stepper.setAcceleration(500);
}

void Joint::setSpeed(int desiredSpeed){
    stepper.setSpeed(desiredSpeed);
}

void Joint::move(int desiredSteps) {
    if (stepper.distanceToGo() == 0) {
        stepper.move(desiredSteps);
        Serial.print("desiredSteps: ");
        Serial.println(desiredSteps);
    }
    stepper.run();
}

void Joint::moveTo(int desiredPos) {
    if (stepper.distanceToGo() == 0) {
        stepper.moveTo(desiredPos);
        Serial.print("desiredPos: ");
        Serial.println(desiredPos);
    }
    stepper.run();
}

void Joint::moveToSerial() {
    if (stepper.distanceToGo() == 0) {
        if (Serial.available()) {
            int desiredPos = Serial.parseInt();
            stepper.moveTo(desiredPos);
            Serial.print("desiredPos: ");
            Serial.println(desiredPos);
        }
    }
    stepper.run();
}
